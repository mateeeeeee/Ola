#include "LLVMVisitor.h"
#include "Frontend/AST/AST.h"
#include "Frontend/AST/Decl.h"
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/DataLayout.h"


namespace ola
{
	LLVMVisitor::LLVMVisitor(llvm::LLVMContext& context, llvm::Module& module)
		: context(context), module(module), builder(context)
	{
		data_layout = std::make_unique<llvm::DataLayout>(&module);
		void_type = llvm::Type::getVoidTy(context);
		bool_type = llvm::Type::getInt1Ty(context);
		char_type = llvm::Type::getInt8Ty(context);
		int_type = llvm::Type::getInt64Ty(context);
		float_type = llvm::Type::getDoubleTy(context);
	}

	void LLVMVisitor::VisitAST(AST const* ast)
	{
		ast->translation_unit->Accept(*this);
	}

	void LLVMVisitor::Visit(ASTNode const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(TranslationUnit const& translation_unit, uint32)
	{
		for (auto&& decl : translation_unit.GetDecls()) decl->Accept(*this);
	}

	void LLVMVisitor::Visit(Decl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(FunctionDecl const& function_decl, uint32)
	{
		FuncType const& type = function_decl.GetFuncType();
		llvm::FunctionType* function_type = llvm::cast<llvm::FunctionType>(ConvertToLLVMType(type));
		llvm::Function::LinkageTypes linkage = function_decl.IsPublic() || function_decl.IsExtern() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
		llvm::Function* llvm_function = llvm::Function::Create(function_type, linkage, function_decl.GetName(), module);

		llvm::Argument* param_arg = llvm_function->arg_begin();
		if (IsClassType(type.GetReturnType()))
		{
			llvm::Value* sret_value = &(*param_arg);
			++param_arg;
			return_value = sret_value;
		}
		for (auto& param : function_decl.GetParamDecls())
		{
			llvm::Value* llvm_param = &*param_arg;
			llvm_param->setName(param->GetName());
			llvm_value_map[param.get()] = llvm_param;
			++param_arg;
		}

		if (!function_decl.HasDefinition()) return;

		if(function_decl.HasFuncAttribute(FuncAttribute_Inline)) llvm_function->addFnAttr(llvm::Attribute::AlwaysInline);
		else if(function_decl.HasFuncAttribute(FuncAttribute_NoInline)) llvm_function->addFnAttr(llvm::Attribute::NoInline);
		VisitFunctionDeclCommon(function_decl, llvm_function);
	}

	void LLVMVisitor::Visit(MethodDecl const& method_decl, uint32)
	{
		ClassDecl const* class_decl = method_decl.GetParentDecl();
		llvm::Type* class_type = ConvertToLLVMType(ClassType(class_decl));

		FuncType const& function_type = method_decl.GetFuncType();

		auto MemberTypeToLLVM = [&](FuncType const& type)
			{
				std::span<QualType const> function_params = type.GetParams();

				llvm::Type* return_type = ConvertToLLVMType(type.GetReturnType());
				bool return_type_struct = return_type->isStructTy();

				std::vector<llvm::Type*> param_types; param_types.reserve(function_params.size());
				if (return_type_struct) param_types.push_back(return_type->getPointerTo());

				param_types.push_back(class_type->getPointerTo());
				for (auto const& func_param_type : function_params)
				{
					llvm::Type* param_type = ConvertToLLVMType(func_param_type);
					param_types.push_back(param_type);
				}
				return llvm::FunctionType::get(return_type_struct ? void_type : return_type, param_types, false);
			};
		
		llvm::FunctionType* llvm_function_type = MemberTypeToLLVM(function_type);

		llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage;
		std::string name(class_decl->GetName()); name += "::"; name += method_decl.GetName();
		llvm::Function* llvm_function = llvm::Function::Create(llvm_function_type, linkage, name, module);

		this_struct_type = class_type;

		llvm::Argument* param_arg = llvm_function->arg_begin();
		if (IsClassType(function_type.GetReturnType()))
		{
			llvm::Value* sret_value = &*param_arg;
			++param_arg;
			return_value = sret_value;
		}
		llvm::Value* llvm_param = &*param_arg;
		llvm_param->setName("this");
		this_value = llvm_param;
		++param_arg;
		for (auto& param : method_decl.GetParamDecls())
		{
			llvm::Value* llvm_param = &*param_arg;
			llvm_param->setName(param->GetName());
			llvm_value_map[param.get()] = llvm_param;
			++param_arg;
		}

		if (!method_decl.HasDefinition())
		{
			this_value = nullptr;
			this_struct_type = nullptr;
			return;
		}

		VisitFunctionDeclCommon(method_decl, llvm_function);

		this_value = nullptr;
		this_struct_type = nullptr;
	}

	void LLVMVisitor::Visit(VarDecl const& var_decl, uint32)
	{
		QualType const& var_type = var_decl.GetType();
		llvm::Type* llvm_type = ConvertToLLVMType(var_type);
		bool const is_array = var_type->Is(TypeKind::Array);
		bool const is_class = var_type->Is(TypeKind::Class);
		bool const is_ref   = var_type->Is(TypeKind::Ref);

		if (var_decl.IsGlobal())
		{
			if (var_decl.IsExtern())
			{
				llvm::GlobalVariable* global_var = new llvm::GlobalVariable(module, llvm_type, var_type.IsConst(), llvm::GlobalValue::ExternalLinkage, nullptr, var_decl.GetName());
				llvm_value_map[&var_decl] = global_var;
			}
			else if(Expr const* init_expr = var_decl.GetInitExpr())
			{
				if (is_array)
				{
					ArrayType const& array_type = type_cast<ArrayType>(var_type);
					llvm::Type* llvm_element_type = ConvertToLLVMType(array_type.GetBaseType());

					if (InitializerListExpr const* init_list_expr = dyn_cast<InitializerListExpr>(init_expr))
					{
						OLA_ASSERT(init_list_expr->IsConstexpr());
						init_list_expr->Accept(*this);
						
						llvm::GlobalValue::LinkageTypes linkage = var_decl.IsPublic() || var_decl.IsExtern() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
						llvm::GlobalVariable* global_array = new llvm::GlobalVariable(module, llvm_type, var_type.IsConst(), linkage, cast<llvm::Constant>(llvm_value_map[init_list_expr]), var_decl.GetName());
						llvm_value_map[&var_decl] = global_array;
					}
					else if (ConstantString const* string = dyn_cast<ConstantString>(init_expr))
					{
						llvm::Constant* constant = llvm::ConstantDataArray::getString(context, string->GetString());

						llvm::GlobalValue::LinkageTypes linkage = var_decl.IsPublic() || var_decl.IsExtern() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
						llvm::GlobalVariable* global_string = new llvm::GlobalVariable(module, llvm_type, var_type.IsConst(), linkage, constant, var_decl.GetName());
						llvm_value_map[&var_decl] = global_string;
					}
					else OLA_ASSERT(false);
				}
				else
				{
					OLA_ASSERT(init_expr->IsConstexpr());
					init_expr->Accept(*this);
					llvm::Value* init_value = llvm_value_map[init_expr];
					llvm::Constant* constant_init_value = llvm::dyn_cast<llvm::Constant>(init_value);
					OLA_ASSERT(constant_init_value);

					llvm::GlobalValue::LinkageTypes linkage = var_decl.IsPublic() || var_decl.IsExtern() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
					llvm::GlobalVariable* global_var = new llvm::GlobalVariable(module, llvm_type, var_type.IsConst(), linkage, constant_init_value, var_decl.GetName());
					llvm_value_map[&var_decl] = global_var;
				}
			}
			else if (is_class)
			{
				ClassType const& class_type = type_cast<ClassType>(var_type);
				ClassDecl const* class_decl = class_type.GetClassDecl();

				UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
				std::vector<llvm::Constant*> initializers;
				ClassDecl const* curr_class_decl = class_decl;
				while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
				{
					for (auto const& base_field : base_class_decl->GetFields())
					{
						initializers.push_back(cast<llvm::Constant>(llvm_value_map[base_field.get()]));
					}
					curr_class_decl = base_class_decl;
				}
				for (uint64 i = 0; i < fields.size(); ++i)
				{
					initializers.push_back(cast<llvm::Constant>(llvm_value_map[fields[i].get()]));
				}

				llvm::StructType* llvm_struct_type = cast<llvm::StructType>(llvm_type);
				llvm::GlobalVariable* global_var = new llvm::GlobalVariable(module, llvm_type, false, llvm::GlobalValue::ExternalLinkage, 
																		 llvm::ConstantStruct::get(llvm_struct_type, initializers), var_decl.GetName());
				llvm_value_map[&var_decl] = global_var;
			}
			else if (is_ref)
			{
				OLA_ASSERT_MSG(false, "todo");
			}
			else
			{
				llvm::Constant* constant_init_value = llvm::Constant::getNullValue(llvm_type);
				llvm::GlobalValue::LinkageTypes linkage = var_decl.IsPublic() || var_decl.IsExtern() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
				llvm::GlobalVariable* global_var = new llvm::GlobalVariable(module, llvm_type, var_type.IsConst(), linkage, constant_init_value, var_decl.GetName());
				llvm_value_map[&var_decl] = global_var;
			}
		}
		else
		{
			if (Expr const* init_expr = var_decl.GetInitExpr())
			{
				init_expr->Accept(*this);
				if (is_array)
				{
					ArrayType const& array_type = type_cast<ArrayType>(var_type);
					llvm::Type* llvm_element_type = ConvertToLLVMType(array_type.GetBaseType());
					llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(64, 0, true));
					if (InitializerListExpr const* init_list_expr = dyn_cast<InitializerListExpr>(init_expr))
					{
						llvm::AllocaInst* alloc = builder.CreateAlloca(llvm_type, nullptr);
						UniqueExprPtrList const& init_list = init_list_expr->GetInitList();

						for (uint64 i = 0; i < init_list.size(); ++i)
						{
							llvm::ConstantInt* index = llvm::ConstantInt::get(context, llvm::APInt(64, i, true));
							llvm::Value* ptr = builder.CreateGEP(llvm_type, alloc, { zero, index });
							Store(llvm_value_map[init_list[i].get()], ptr);
						}
						for (uint64 i = init_list.size(); i < array_type.GetArraySize(); ++i)
						{
							llvm::ConstantInt* index = llvm::ConstantInt::get(context, llvm::APInt(64, i, true));
							llvm::Value* ptr = builder.CreateGEP(llvm_type, alloc, { zero, index });
							Store(llvm::Constant::getNullValue(llvm_element_type), ptr);
						}
						llvm_value_map[&var_decl] = alloc;
					}
					else if (ConstantString const* string = dyn_cast<ConstantString>(init_expr))
					{
						llvm::AllocaInst* alloc = builder.CreateAlloca(llvm_type, nullptr);
						std::string_view str = string->GetString();
						for (uint64 i = 0; i < str.size(); ++i)
						{
							llvm::ConstantInt* index = llvm::ConstantInt::get(context, llvm::APInt(64, i, true));
							llvm::Value* ptr = builder.CreateGEP(llvm_type, alloc, { zero, index });
							Store(llvm::ConstantInt::get(char_type, str[i], true), ptr);
						}
						llvm::ConstantInt* index = llvm::ConstantInt::get(context, llvm::APInt(64, str.size(), true));
						llvm::Value* ptr = builder.CreateGEP(llvm_type, alloc, { zero, index });
						Store(llvm::ConstantInt::get(char_type, '\0', true), ptr);
						llvm_value_map[&var_decl] = alloc;
					}
					else if (isoneof<DeclRefExpr, ArrayAccessExpr>(init_expr))
					{
						OLA_ASSERT(IsArrayType(init_expr->GetType()));
						llvm::Type* init_expr_type = ConvertToLLVMType(init_expr->GetType());
						llvm::AllocaInst* alloc = builder.CreateAlloca(GetPointerType(llvm_element_type), nullptr);
						llvm::Value* ptr = nullptr;
						if (init_expr_type->isArrayTy()) ptr = builder.CreateInBoundsGEP(init_expr_type, llvm_value_map[init_expr], { zero, zero });
						else ptr = builder.CreateLoad(init_expr_type, llvm_value_map[init_expr]);
						builder.CreateStore(ptr, alloc);
						llvm_value_map[&var_decl] = alloc;
					}
					else if (isoneof<CallExpr, MemberCallExpr>(init_expr))
					{
						OLA_ASSERT(IsArrayType(init_expr->GetType()));
						llvm::AllocaInst* alloc = builder.CreateAlloca(GetPointerType(llvm_element_type), nullptr);
						builder.CreateStore(llvm_value_map[init_expr], alloc);
						llvm_value_map[&var_decl] = alloc;
					}
				}
				else if (is_class)
				{
					QualType const& var_type = var_decl.GetType();
					ClassType const& class_type = type_cast<ClassType>(var_type);
					ClassDecl const* class_decl = class_type.GetClassDecl();

					llvm::AllocaInst* struct_alloc = builder.CreateAlloca(llvm_type, nullptr);
					llvm::TypeSize struct_size = data_layout->getTypeAllocSize(llvm_type);

					llvm::Value* init_value = llvm_value_map[init_expr];
					
					builder.CreateMemCpy(struct_alloc, llvm::MaybeAlign(), init_value, llvm::MaybeAlign(), llvm::ConstantInt::get(int_type, struct_size));
					llvm_value_map[&var_decl] = struct_alloc;
				}
				else if (is_ref)
				{
					llvm::AllocaInst* alloc = builder.CreateAlloca(llvm_type, nullptr);
					llvm::Value* init_value = llvm_value_map[init_expr];
					builder.CreateStore(init_value, alloc);
					llvm::Value* arg_ref = builder.CreateLoad(llvm_type, alloc);
					llvm_value_map[&var_decl] = arg_ref;
				}
				else
				{
					llvm::AllocaInst* alloc = builder.CreateAlloca(llvm_type, nullptr);
					llvm::Value* init_value = llvm_value_map[init_expr];
					Store(init_value, alloc);
					llvm_value_map[&var_decl] = alloc;
				}
			}
			else
			{
				if (is_class)
				{
					QualType const& var_type = var_decl.GetType();
					ClassType const& class_type = type_cast<ClassType>(var_type);
					ClassDecl const* class_decl = class_type.GetClassDecl();

					llvm::AllocaInst* struct_alloc = builder.CreateAlloca(llvm_type, nullptr);
					llvm_value_map[&var_decl] = struct_alloc;

					ClassDecl const* curr_class_decl = class_decl;
					while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
					{
						UniqueFieldDeclPtrList const& base_fields = base_class_decl->GetFields();
						for (auto const& base_field : base_fields)
						{
							llvm::Value* field_ptr = builder.CreateStructGEP(llvm_type, struct_alloc, base_field->GetFieldIndex());
							Store(llvm_value_map[base_field.get()], field_ptr);
						}
						curr_class_decl = base_class_decl;
					}
					UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
					for (auto const& field : fields)
					{
						llvm::Value* field_ptr = builder.CreateStructGEP(llvm_type, struct_alloc, field->GetFieldIndex());
						Store(llvm_value_map[field.get()], field_ptr);
					}
				}
				else
				{
					llvm::AllocaInst* alloc = builder.CreateAlloca(llvm_type, nullptr);
					llvm_value_map[&var_decl] = alloc;
				}
			}
		}
	}

	void LLVMVisitor::Visit(FieldDecl const& member_var, uint32)
	{
		QualType const& var_type = member_var.GetType();
		llvm::Type* llvm_type = ConvertToLLVMType(var_type);

		if (Expr const* init_expr = member_var.GetInitExpr())
		{
			init_expr->Accept(*this);
			llvm::Value* init_value = llvm_value_map[init_expr];
			OLA_ASSERT(isa<llvm::Constant>(init_value));
			llvm_value_map[&member_var] = cast<llvm::Constant>(init_value);
		}
		else
		{
			llvm_value_map[&member_var] = llvm::Constant::getNullValue(llvm_type);
		}
	}

	void LLVMVisitor::Visit(ParamVarDecl const& param_var, uint32)
	{
	}

	void LLVMVisitor::Visit(TagDecl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(EnumDecl const& enum_decl, uint32)
	{
		for (auto const& enum_member : enum_decl.GetEnumMembers()) enum_member->Accept(*this);
	}

	void LLVMVisitor::Visit(EnumMemberDecl const& enum_member, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(int_type, enum_member.GetValue());
		llvm_value_map[&enum_member] = constant;
	}

	void LLVMVisitor::Visit(AliasDecl const&, uint32)
	{
		//alias declaration doesn't generate any code
	}

	void LLVMVisitor::Visit(ClassDecl const& class_decl, uint32)
	{
		for (auto& field  : class_decl.GetFields()) field->Accept(*this);
		for (auto& method : class_decl.GetMethods()) method->Accept(*this);
	}

	void LLVMVisitor::Visit(Stmt const& stmt, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(CompoundStmt const& compound_stmt, uint32)
	{
		for (auto const& stmt : compound_stmt.GetStmts()) stmt->Accept(*this);
	}

	void LLVMVisitor::Visit(DeclStmt const& decl_stmt, uint32)
	{
		for(auto const& decl : decl_stmt.GetDecls())  decl->Accept(*this);
	}

	void LLVMVisitor::Visit(ExprStmt const& expr_stmt, uint32)
	{
		if (expr_stmt.GetExpr()) expr_stmt.GetExpr()->Accept(*this);
	}

	void LLVMVisitor::Visit(NullStmt const& null_stmt, uint32) {}

	void LLVMVisitor::Visit(ReturnStmt const& return_stmt, uint32)
	{
		llvm::BasicBlock* current_block = builder.GetInsertBlock();
		llvm::Function* current_function = current_block->getParent();
		if (Expr const* return_expr = return_stmt.GetExprStmt()->GetExpr()) 
		{
			return_expr->Accept(*this);
			llvm::Value* return_expr_value = llvm_value_map[return_expr];
			OLA_ASSERT(return_expr_value);

			if (current_function->getReturnType()->isPointerTy()) builder.CreateStore(return_expr_value, return_value);
			else llvm_value_map[&return_stmt] = Store(return_expr_value, return_value);
		}
		builder.CreateBr(exit_block);
		llvm::BasicBlock* return_block = llvm::BasicBlock::Create(context, "return", current_function, current_block->getNextNode());
		builder.SetInsertPoint(return_block);
	}

	void LLVMVisitor::Visit(IfStmt const& if_stmt, uint32)
	{
		Expr const* cond_expr = if_stmt.GetCondExpr();
		Stmt const* then_stmt = if_stmt.GetThenStmt();
		Stmt const* else_stmt = if_stmt.GetElseStmt();

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* then_block = llvm::BasicBlock::Create(context, "if.then", function, exit_block);
		llvm::BasicBlock* else_block = llvm::BasicBlock::Create(context, "if.else", function, exit_block);
		llvm::BasicBlock* end_block  = llvm::BasicBlock::Create(context, "if.end", function, exit_block);

		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, then_block, else_stmt ? else_block : end_block);

		builder.SetInsertPoint(then_block);
		then_stmt->Accept(*this);
		if(!then_block->getTerminator()) builder.CreateBr(end_block);

		if (else_stmt)
		{
			builder.SetInsertPoint(else_block);
			else_stmt->Accept(*this);
			if (!else_block->getTerminator()) builder.CreateBr(end_block);
		}
		builder.SetInsertPoint(end_block);
	}

	void LLVMVisitor::Visit(BreakStmt const&, uint32)
	{
		OLA_ASSERT(!break_blocks.empty());
		builder.CreateBr(break_blocks.back());
		llvm::BasicBlock* break_block = llvm::BasicBlock::Create(context, "break", builder.GetInsertBlock()->getParent(), exit_block);
		builder.SetInsertPoint(break_block);
	}

	void LLVMVisitor::Visit(ContinueStmt const&, uint32)
	{
		OLA_ASSERT(!continue_blocks.empty());
		builder.CreateBr(continue_blocks.back());
		llvm::BasicBlock* continue_block = llvm::BasicBlock::Create(context, "continue", builder.GetInsertBlock()->getParent(), exit_block);
		builder.SetInsertPoint(continue_block);
	}

	void LLVMVisitor::Visit(ForStmt const& for_stmt, uint32)
	{
		Stmt const* init_stmt = for_stmt.GetInitStmt();
		Expr const* cond_expr = for_stmt.GetCondExpr();
		Expr const* iter_expr = for_stmt.GetIterExpr();
		Stmt const* body_stmt = for_stmt.GetBodyStmt();

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* body_block = llvm::BasicBlock::Create(context, "for.body", function, exit_block);
		llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(context, "for.cond", function, exit_block);
		llvm::BasicBlock* iter_block = llvm::BasicBlock::Create(context, "for.iter", function, exit_block);
		llvm::BasicBlock* end_block  = llvm::BasicBlock::Create(context, "for.end", function, exit_block);


		if (init_stmt) init_stmt->Accept(*this);
		builder.CreateBr(cond_block);

		builder.SetInsertPoint(cond_block);
		if (cond_expr)
		{
			cond_expr->Accept(*this);
			llvm::Value* condition_value = llvm_value_map[cond_expr];
			OLA_ASSERT(condition_value);
			ConditionalBranch(condition_value, body_block, end_block);
		}
		else
		{
			builder.CreateBr(body_block);
		}

		builder.SetInsertPoint(body_block);

		continue_blocks.push_back(iter_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();

		builder.CreateBr(iter_block);

		builder.SetInsertPoint(iter_block);
		if (iter_expr) iter_expr->Accept(*this);
		builder.CreateBr(cond_block);

		builder.SetInsertPoint(end_block);
	}

	void LLVMVisitor::Visit(WhileStmt const& while_stmt, uint32)
	{
		Expr const* cond_expr = while_stmt.GetCondExpr();
		Stmt const* body_stmt = while_stmt.GetBodyStmt();

		llvm::Function* function	 = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(context, "while.cond", function, exit_block);
		llvm::BasicBlock* body_block = llvm::BasicBlock::Create(context, "while.body", function, exit_block);
		llvm::BasicBlock* end_block  = llvm::BasicBlock::Create(context, "while.end",  function, exit_block);

		builder.CreateBr(cond_block);
		builder.SetInsertPoint(cond_block);
		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, body_block, end_block);

		builder.SetInsertPoint(body_block);

		continue_blocks.push_back(cond_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();

		builder.CreateBr(cond_block);

		builder.SetInsertPoint(end_block);
	}

	void LLVMVisitor::Visit(DoWhileStmt const& do_while_stmt, uint32)
	{
		Expr const* cond_expr = do_while_stmt.GetCondExpr();
		Stmt const* body_stmt = do_while_stmt.GetBodyStmt();

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* body_block = llvm::BasicBlock::Create(context, "dowhile.body", function, exit_block);
		llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(context, "dowhile.cond", function, exit_block);
		llvm::BasicBlock* end_block  = llvm::BasicBlock::Create(context, "dowhile.end", function, exit_block);

		builder.CreateBr(body_block);
		builder.SetInsertPoint(body_block);

		continue_blocks.push_back(cond_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();

		builder.CreateBr(cond_block);

		builder.SetInsertPoint(cond_block);
		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, body_block, end_block);

		builder.SetInsertPoint(end_block);
	}

	void LLVMVisitor::Visit(CaseStmt const& case_stmt, uint32)
	{
		OLA_ASSERT(!switch_instructions.empty());
		llvm::SwitchInst* switch_inst = switch_instructions.back();
		if (case_stmt.IsDefault())
		{
			builder.SetInsertPoint(switch_inst->getDefaultDest());
		}
		else
		{
			int64 case_value = case_stmt.GetValue();
			llvm::ConstantInt* llvm_case_value = llvm::ConstantInt::get(int_type, case_value);

			llvm::Function* function = builder.GetInsertBlock()->getParent();
			std::string block_name = "switch.case"; block_name += std::to_string(case_value);
			llvm::BasicBlock* case_block = llvm::BasicBlock::Create(context, block_name, function, exit_block);
			switch_inst->addCase(llvm_case_value, case_block);
			builder.SetInsertPoint(case_block);
		}
	}

	void LLVMVisitor::Visit(SwitchStmt const& switch_stmt, uint32)
	{
		Expr const* cond_expr = switch_stmt.GetCondExpr();
		Stmt const* body_stmt = switch_stmt.GetBodyStmt();

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* header_block = llvm::BasicBlock::Create(context, "switch.header", function, exit_block);
		llvm::BasicBlock* default_block = llvm::BasicBlock::Create(context, "switch.default", function, exit_block);
		llvm::BasicBlock* end_block = llvm::BasicBlock::Create(context, "switch.end", function, exit_block);

		builder.CreateBr(header_block);
		builder.SetInsertPoint(header_block);

		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		OLA_ASSERT(condition_value);
		llvm::Value* condition = Load(int_type, condition_value);
		llvm::SwitchInst* switch_inst = builder.CreateSwitch(condition, default_block);

		switch_instructions.push_back(switch_inst);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		switch_instructions.pop_back();

		std::vector<llvm::BasicBlock*> case_blocks;
		for (auto& case_stmt : switch_inst->cases()) case_blocks.push_back(case_stmt.getCaseSuccessor());
		for (uint32 i = 0; i < case_blocks.size(); ++i)
		{
			llvm::BasicBlock* case_block = case_blocks[i];
			if (!case_block->getTerminator())
			{
				llvm::BasicBlock* dest_block = i < case_blocks.size() - 1 ? case_blocks[i + 1] : default_block;
				builder.SetInsertPoint(case_block);
				builder.CreateBr(dest_block);
			}
		}
		builder.SetInsertPoint(end_block);
	}

	void LLVMVisitor::Visit(GotoStmt const& goto_stmt, uint32)
	{
		std::string label_name = "label."; label_name += goto_stmt.GetLabelName();
		builder.CreateBr(label_blocks[label_name]);

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* goto_block = llvm::BasicBlock::Create(context, "goto", function, exit_block);
		builder.SetInsertPoint(goto_block);
	}

	void LLVMVisitor::Visit(LabelStmt const& label_stmt, uint32)
	{
		std::string block_name = "label."; block_name += label_stmt.GetName();
		llvm::BasicBlock* label_block = label_blocks[block_name];
		builder.CreateBr(label_block);
		builder.SetInsertPoint(label_block);
	}

	void LLVMVisitor::Visit(Expr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(UnaryExpr const& unary_expr, uint32)
	{
		Expr const* operand_expr = unary_expr.GetOperand();
		operand_expr->Accept(*this);
		llvm::Value* operand_value = llvm_value_map[operand_expr];
		OLA_ASSERT(operand_value);
		llvm::Value* operand = Load(operand_expr->GetType(), operand_value);

		bool const is_float_expr = IsFloatType(operand_expr->GetType());
		llvm::Value* result = nullptr;
		switch (unary_expr.GetUnaryKind())
		{
		case UnaryExprKind::PreIncrement:
		{
			llvm::Value* incremented_value = is_float_expr ? builder.CreateFAdd(operand, llvm::ConstantFP::get(operand->getType(), 1.0)) :
															 builder.CreateAdd(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(incremented_value, operand_value);
			result = incremented_value;
		}
		break;
		case UnaryExprKind::PreDecrement:
		{
			llvm::Value* decremented_value = is_float_expr ? builder.CreateFSub(operand, llvm::ConstantFP::get(operand->getType(), 1.0)) :
															 builder.CreateSub(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(decremented_value, operand_value);
			result = decremented_value;
		}
		break;
		case UnaryExprKind::PostIncrement:
		{
			result = builder.CreateAlloca(operand_value->getType());
			Store(operand_value, result);
			llvm::Value* incremented_value = is_float_expr ? builder.CreateFAdd(operand, llvm::ConstantFP::get(operand->getType(), 1.0)) :
															 builder.CreateAdd(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder.CreateAlloca(operand_value->getType());
			Store(operand_value, result);
			llvm::Value* decremented_value = is_float_expr ? builder.CreateFSub(operand, llvm::ConstantFP::get(operand->getType(), 1.0)) :
															 builder.CreateSub(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(decremented_value, operand_value);
		}
		break;
		case UnaryExprKind::Plus:
		{
			result = operand_value;
		}
		break;
		case UnaryExprKind::Minus:
		{
			result = is_float_expr ? builder.CreateFNeg(operand) : builder.CreateNeg(operand);
		}
		break;
		case UnaryExprKind::BitNot:
		{
			result = builder.CreateNot(operand);
		}
		break;
		case UnaryExprKind::LogicalNot:
		{
			result = is_float_expr ? builder.CreateFCmpUEQ(operand, llvm::ConstantFP::get(operand->getType(), 0.0)):
			                         builder.CreateICmpEQ(operand, llvm::ConstantInt::get(operand->getType(), 0));
		}
		break;
		default:
			OLA_ASSERT(false);
		}
		OLA_ASSERT(result);
		llvm_value_map[&unary_expr] = result;
	}

	void LLVMVisitor::Visit(BinaryExpr const& binary_expr, uint32)
	{
		Expr const* lhs_expr = binary_expr.GetLHS();
		lhs_expr->Accept(*this);
		llvm::Value* lhs_value = llvm_value_map[lhs_expr];
		Expr const* rhs_expr = binary_expr.GetRHS();
		rhs_expr->Accept(*this);
		llvm::Value* rhs_value = llvm_value_map[rhs_expr];
		OLA_ASSERT(lhs_value && rhs_value);

		llvm::Value* lhs = Load(lhs_expr->GetType(), lhs_value);
		llvm::Value* rhs = Load(rhs_expr->GetType(), rhs_value);
		bool const is_float_expr = IsFloatType(lhs_expr->GetType()) || IsFloatType(rhs_expr->GetType());

		llvm::Value* result = nullptr;
		switch (binary_expr.GetBinaryKind())
		{
		case BinaryExprKind::Assign:
		{
			result = Store(rhs_value, lhs_value);
		}
		break;
		case BinaryExprKind::Add:
		{

			result = is_float_expr ? builder.CreateFAdd(lhs, rhs) : builder.CreateAdd(lhs, rhs);
		}
		break;
		case BinaryExprKind::Subtract:
		{
			result = is_float_expr ? builder.CreateFSub(lhs, rhs) : builder.CreateSub(lhs, rhs);
		}
		break;
		case BinaryExprKind::Multiply:
		{
			result = is_float_expr ? builder.CreateFMul(lhs, rhs) : builder.CreateMul(lhs, rhs);
		}
		break;
		case BinaryExprKind::Divide:
		{
			result = is_float_expr ? builder.CreateFDiv(lhs, rhs) : builder.CreateSDiv(lhs, rhs);
		}
		break;
		case BinaryExprKind::Modulo:
		{
			OLA_ASSERT(!is_float_expr);
			result = builder.CreateSRem(lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftLeft:
		{
			result = builder.CreateShl(lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftRight:
		{
			result = builder.CreateAShr(lhs, rhs);
		}
		break;
		case BinaryExprKind::BitAnd:
		{
			result = builder.CreateAnd(lhs, rhs);
		}
		break;
		case BinaryExprKind::BitOr:
		{
			result = builder.CreateOr(lhs, rhs);
		}
		break;
		case BinaryExprKind::BitXor:
		{
			result = builder.CreateXor(lhs, rhs);
		}
		break;
		case BinaryExprKind::LogicalAnd:
		{
			llvm::Value* tmp = builder.CreateAnd(lhs, rhs);
			result = builder.CreateICmpNE(tmp, llvm::ConstantInt::get(tmp->getType(), 0));
		}
		break;
		case BinaryExprKind::LogicalOr:
		{
			llvm::Value* tmp = builder.CreateOr(lhs, rhs);
			result = builder.CreateICmpNE(tmp, llvm::ConstantInt::get(tmp->getType(), 0));
		}
		break;
		case BinaryExprKind::Equal:
		{
			result = is_float_expr ? builder.CreateFCmpOEQ(lhs, rhs) : builder.CreateICmpEQ(lhs, rhs);
		}
		break;
		case BinaryExprKind::NotEqual:
		{
			result = is_float_expr ? builder.CreateFCmpONE(lhs, rhs) : builder.CreateICmpNE(lhs, rhs);
		}
		break;
		case BinaryExprKind::Less:
		{
			result = is_float_expr ? builder.CreateFCmpOLT(lhs, rhs) : builder.CreateICmpSLT(lhs, rhs);
		}
		break;
		case BinaryExprKind::Greater:
		{
			result = is_float_expr ? builder.CreateFCmpOGT(lhs, rhs) : builder.CreateICmpSGT(lhs, rhs);
		}
		break;
		case BinaryExprKind::LessEqual:
		{
			result = is_float_expr ? builder.CreateFCmpOLE(lhs, rhs) : builder.CreateICmpSLE(lhs, rhs);
		}
		break;
		case BinaryExprKind::GreaterEqual:
		{
			result = is_float_expr ? builder.CreateFCmpOGE(lhs, rhs) : builder.CreateICmpSGE(lhs, rhs);
		}
		break;
		case BinaryExprKind::Comma:
		{
			result = rhs;
		}
		break;
		case BinaryExprKind::Invalid:
		default:
			OLA_ASSERT(false);
		}
		OLA_ASSERT(result);
		llvm_value_map[&binary_expr] = result;
	}

	void LLVMVisitor::Visit(TernaryExpr const& ternary_expr, uint32)
	{
		Expr const* cond_expr = ternary_expr.GetCondExpr();
		Expr const* true_expr = ternary_expr.GetTrueExpr();
		Expr const* false_expr = ternary_expr.GetFalseExpr();

		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		OLA_ASSERT(condition_value);
		condition_value = Load(bool_type, condition_value);

		true_expr->Accept(*this);
		llvm::Value* true_value = llvm_value_map[true_expr];
		OLA_ASSERT(true_value);
		true_value = Load(true_expr->GetType(), true_value);

		false_expr->Accept(*this);
		llvm::Value* false_value = llvm_value_map[false_expr];
		OLA_ASSERT(false_value);
		false_value = Load(false_expr->GetType(), false_value);

		if (condition_value->getType() != llvm::Type::getInt1Ty(context)) OLA_ASSERT(false);

		llvm_value_map[&ternary_expr] = builder.CreateSelect(condition_value, true_value, false_value);
	}

	void LLVMVisitor::Visit(IdentifierExpr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(DeclRefExpr const& decl_ref, uint32)
	{
		llvm::Value* value = llvm_value_map[decl_ref.GetDecl()];
		OLA_ASSERT(value);
		llvm_value_map[&decl_ref] = value;
	}

	void LLVMVisitor::Visit(ConstantInt const& int_constant, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(int_type, int_constant.GetValue());
		llvm_value_map[&int_constant] = constant;
	}

	void LLVMVisitor::Visit(ConstantChar const& char_constant, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(char_type, char_constant.GetChar(), true);
		llvm_value_map[&char_constant] = constant;
	}

	void LLVMVisitor::Visit(ConstantString const& string_constant, uint32)
	{
		llvm::Constant* constant = llvm::ConstantDataArray::getString(context, string_constant.GetString());
		
		static uint32 counter = 0;
		std::string name = "__StringLiteral"; name += std::to_string(counter++);

		llvm::GlobalValue::LinkageTypes linkage = llvm::Function::InternalLinkage;
		llvm::GlobalVariable* global_string = new llvm::GlobalVariable(module, ConvertToLLVMType(string_constant.GetType()), true, linkage, constant, name);
		llvm_value_map[&string_constant] = global_string;
	}

	void LLVMVisitor::Visit(ConstantBool const& bool_constant, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(bool_type, bool_constant.GetValue());
		llvm_value_map[&bool_constant] = constant;
	}

	void LLVMVisitor::Visit(ConstantFloat const& float_constant, uint32)
	{
		llvm::Constant* constant = llvm::ConstantFP::get(float_type, float_constant.GetValue());
		llvm_value_map[&float_constant] = constant;
	}

	void LLVMVisitor::Visit(ImplicitCastExpr const& cast_expr, uint32)
	{
		Expr const* cast_operand_expr = cast_expr.GetOperand();
		cast_operand_expr->Accept(*this);
		llvm::Value* cast_operand_value = llvm_value_map[cast_operand_expr];
		OLA_ASSERT(cast_operand_value);

		llvm::Type* cast_type = ConvertToLLVMType(cast_expr.GetType());
		llvm::Type* cast_operand_type = ConvertToLLVMType(cast_operand_expr->GetType());

		llvm::Value* cast_operand = Load(cast_operand_type, cast_operand_value);
		if (IsInteger(cast_type))
		{
			if (IsBoolean(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateZExt(cast_operand, int_type);
			}
			else if (IsFloat(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateFPToSI(cast_operand, int_type);
			}
			else if (IsRef(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateLoad(int_type, cast_operand_value);
			}
			else OLA_ASSERT(false);
		}
		else if (IsBoolean(cast_type))
		{
			if (IsInteger(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateICmpNE(cast_operand, llvm::ConstantInt::get(context, llvm::APInt(64, 0)));
			}
			else if (IsFloat(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateFPToUI(cast_operand, bool_type);
			}
			else if (IsRef(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateLoad(bool_type, cast_operand);
			}
			else OLA_ASSERT(false);
		}
		else if (IsFloat(cast_type))
		{
			if (IsBoolean(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateUIToFP(cast_operand, float_type);
			}
			else if (IsInteger(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateSIToFP(cast_operand, float_type);
			}
			else if (IsRef(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = builder.CreateLoad(float_type, cast_operand);
			}
			else OLA_ASSERT(false);
		}
		else if (IsStruct(cast_type))
		{
			if (IsRef(cast_operand_type))
			{
				llvm_value_map[&cast_expr] = cast_operand_value;
			}
			else if (IsStruct(cast_operand_type))
			{
				llvm::Value* bitcast_value = builder.CreateBitCast(cast_operand_value, GetPointerType(cast_type));
				llvm_value_map[&cast_expr] = builder.CreateStructGEP(cast_type, bitcast_value, 0);
			}
			else OLA_ASSERT(false);
		}
		else if (IsRef(cast_type))
		{
			llvm_value_map[&cast_expr] = cast_operand_value;
		}
		else OLA_ASSERT(llvm_value_map[&cast_expr] != nullptr);
	}

	void LLVMVisitor::Visit(CallExpr const& call_expr, uint32)
	{
		llvm::Function* called_function = module.getFunction(call_expr.GetFunctionName());
		OLA_ASSERT(called_function);

		std::vector<llvm::Value*> args;
		uint32 arg_index = 0;
		bool return_struct = IsClassType(call_expr.GetCalleeType().GetReturnType());
		llvm::AllocaInst* return_alloc = nullptr;
		if (return_struct)
		{
			return_alloc = builder.CreateAlloca(called_function->getArg(arg_index)->getType());
			args.push_back(return_alloc);
			++arg_index;
		}
		for (auto const& arg_expr : call_expr.GetArgs())
		{
			arg_expr->Accept(*this);
			llvm::Value* arg_value = llvm_value_map[arg_expr.get()];
			OLA_ASSERT(arg_value);

			llvm::Type* arg_type = called_function->getArg(arg_index)->getType();
			if (arg_type->isPointerTy()) args.push_back(arg_value);
			else args.push_back(Load(arg_type, arg_value));
			
			arg_index++;
		}

		llvm::Value* call_result = builder.CreateCall(called_function, args);
		llvm_value_map[&call_expr] = return_alloc ? return_alloc : call_result;
	}

	void LLVMVisitor::Visit(InitializerListExpr const& initializer_list, uint32)
	{
		UniqueExprPtrList const& init_expr_list = initializer_list.GetInitList();
		for (auto const& element_expr : init_expr_list) element_expr->Accept(*this);
		if (initializer_list.IsConstexpr())
		{
			ArrayType const& array_type = type_cast<ArrayType>(initializer_list.GetType());
			llvm::Type* llvm_element_type = ConvertToLLVMType(array_type.GetBaseType());
			llvm::Type* llvm_array_type = ConvertToLLVMType(array_type);

			std::vector<llvm::Constant*> array_init_list(array_type.GetArraySize());
			for (uint64 i = 0; i < array_type.GetArraySize(); ++i)
			{
				if (i < init_expr_list.size())  array_init_list[i] = llvm::dyn_cast<llvm::Constant>(llvm_value_map[init_expr_list[i].get()]);
				else array_init_list[i] = llvm::Constant::getNullValue(llvm_element_type);
			}
			llvm::Constant* constant_array = llvm::ConstantArray::get(llvm::dyn_cast<llvm::ArrayType>(llvm_array_type), array_init_list);
			llvm_value_map[&initializer_list] = constant_array;
		}
		
	}

	void LLVMVisitor::Visit(ArrayAccessExpr const& array_access, uint32)
	{
		Expr const* array_expr = array_access.GetArrayExpr();
		Expr const* index_expr = array_access.GetIndexExpr();

		array_expr->Accept(*this);
		index_expr->Accept(*this);

		llvm::Value* array_value = llvm_value_map[array_expr];
		llvm::Value* index_value = llvm_value_map[index_expr];
		index_value = Load(int_type, index_value);

		llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(64, 0, true));
		if (llvm::AllocaInst* alloc = dyn_cast<llvm::AllocaInst>(array_value))
		{
			llvm::Type* alloc_type = alloc->getAllocatedType();
			if (alloc_type->isArrayTy())
			{
				llvm::Value* ptr = builder.CreateGEP(alloc_type, alloc, { zero, index_value });
				llvm_value_map[&array_access] = ptr;
			}
			else if (alloc_type->isPointerTy())
			{
				llvm::Value* ptr = builder.CreateInBoundsGEP(alloc_type, Load(alloc_type, alloc), index_value);
				llvm_value_map[&array_access] = ptr;
			}
			else OLA_ASSERT(false);
		}
		else 
		{
			QualType const& array_expr_type = array_expr->GetType();
			OLA_ASSERT(IsArrayType(array_expr_type));
			ArrayType const& array_type = type_cast<ArrayType>(array_expr_type);
			if (IsArrayType(array_type.GetBaseType()))
			{
				uint32 array_size = array_type.GetArraySize();
				index_value = builder.CreateMul(index_value, llvm::ConstantInt::get(int_type, array_size));
			}
			llvm::Value* ptr = builder.CreateInBoundsGEP(array_value->getType(), array_value, index_value);
			llvm_value_map[&array_access] = ptr;
		}
	}

	void LLVMVisitor::Visit(MemberExpr const& member_expr, uint32)
	{
		Expr const* class_expr = member_expr.GetClassExpr();
		Decl const* member_decl = member_expr.GetMemberDecl();
		class_expr->Accept(*this);
		if (isa<FieldDecl>(member_decl))
		{
			FieldDecl const* field_decl = cast<FieldDecl>(member_decl);
			llvm::Value* field_value = nullptr;
			if (!this_value)
			{
				llvm::Value* struct_value = llvm_value_map[class_expr];

				auto GetStructType = [this](QualType const& class_expr_type) -> llvm::Type*
					{
						if (IsClassType(class_expr_type))
						{
							return ConvertToLLVMType(class_expr_type);
						}
						else if (IsRefType(class_expr_type))
						{
							RefType const& ref_type = type_cast<RefType>(class_expr_type);
							if (IsClassType(ref_type.GetReferredType()))
							{
								return ConvertToLLVMType(ref_type.GetReferredType());
							}
							else return nullptr;
						}
						else return nullptr;
					};

				field_value = builder.CreateStructGEP(GetStructType(class_expr->GetType()), struct_value, field_decl->GetFieldIndex());
				llvm_value_map[&member_expr] = field_value;
			}
			else
			{
				FieldDecl const* field_decl = cast<FieldDecl>(member_decl);
				field_value = builder.CreateStructGEP(this_struct_type, this_value, field_decl->GetFieldIndex());
			}
			llvm_value_map[&member_expr] = field_value;
		}
		else if (isa<MethodDecl>(member_decl))
		{
			MethodDecl const* field_decl = cast<MethodDecl>(member_decl);
			OLA_ASSERT(false);
		}
		else OLA_ASSERT(false);
	}

	void LLVMVisitor::Visit(MemberCallExpr const& member_call_expr, uint32)
	{
		Expr const* expr = member_call_expr.GetCallee();
		OLA_ASSERT(isa<MemberExpr>(expr));
		MemberExpr const* member_expr = cast<MemberExpr>(expr);

		Decl const* decl = member_expr->GetMemberDecl();
		OLA_ASSERT(isa<MethodDecl>(decl));
		MethodDecl const* method_decl = cast<MethodDecl>(decl);
		ClassDecl const* class_decl = method_decl->GetParentDecl();
		std::string name(class_decl->GetName());
		name += "::";
		name += member_call_expr.GetFunctionName();

		llvm::Function* called_function = module.getFunction(name);
		OLA_ASSERT(called_function);

		std::vector<llvm::Value*> args;
		uint32 arg_index = 0;

		bool return_struct = IsClassType(member_call_expr.GetCalleeType().GetReturnType());
		llvm::AllocaInst* return_alloc = nullptr;
		if (return_struct)
		{
			return_alloc = builder.CreateAlloca(called_function->getArg(arg_index)->getType());
			args.push_back(return_alloc);
			++arg_index;
		}

		member_expr->GetClassExpr()->Accept(*this);
		llvm::Value* this_value = llvm_value_map[member_expr->GetClassExpr()];
		args.push_back(this_value);
		for (auto const& arg_expr : member_call_expr.GetArgs())
		{
			arg_expr->Accept(*this);
			llvm::Value* arg_value = llvm_value_map[arg_expr.get()];
			OLA_ASSERT(arg_value);
			args.push_back(Load(called_function->getArg(arg_index++)->getType(), arg_value));
		}

		llvm::Value* call_result = builder.CreateCall(called_function, args);
		llvm_value_map[&member_call_expr] = return_alloc ? return_alloc : call_result;
	}

	void LLVMVisitor::Visit(ThisExpr const& this_expr, uint32)
	{
		llvm_value_map[&this_expr] = this_value;
	}

	void LLVMVisitor::Visit(SuperExpr const& super_expr, uint32)
	{
		llvm_value_map[&super_expr] = this_value;
	}

	void LLVMVisitor::VisitFunctionDeclCommon(FunctionDecl const& func_decl, llvm::Function* func)
	{
		llvm::BasicBlock* entry_block = llvm::BasicBlock::Create(context, "entry", func);
		builder.SetInsertPoint(entry_block);

		for (auto& param : func_decl.GetParamDecls())
		{
			llvm::Value* arg_value = llvm_value_map[param.get()];
			llvm::AllocaInst* arg_alloc = builder.CreateAlloca(arg_value->getType(), nullptr);
			builder.CreateStore(arg_value, arg_alloc);
			if (IsRefType(param->GetType()))
			{
				llvm::Value* arg_ref = builder.CreateLoad(arg_value->getType(), arg_alloc);
				llvm_value_map[param.get()] = arg_ref;
			}
			else
			{
				llvm_value_map[param.get()] = arg_alloc;
			}
		}

		if (!func->getReturnType()->isVoidTy()) return_value = builder.CreateAlloca(func->getReturnType(), nullptr);
		exit_block = llvm::BasicBlock::Create(context, "exit", func);

		ConstLabelStmtPtrList labels = func_decl.GetLabels();
		for (LabelStmt const* label : labels)
		{
			std::string block_name = "label."; block_name += label->GetName();
			llvm::BasicBlock* label_block = llvm::BasicBlock::Create(context, block_name, func, exit_block);
			label_blocks[block_name] = label_block;
		}

		func_decl.GetBodyStmt()->Accept(*this);

		builder.SetInsertPoint(exit_block);
		if (!func->getReturnType()->isVoidTy()) builder.CreateRet(Load(func->getReturnType(), return_value));
		else builder.CreateRetVoid();

		std::vector<llvm::BasicBlock*> unreachable_blocks{};
		for (auto&& block : *func) if (block.hasNPredecessors(0) && &block != entry_block) unreachable_blocks.push_back(&block);

		std::vector<llvm::BasicBlock*> empty_blocks{};
		for (auto&& block : *func) if (block.empty()) empty_blocks.push_back(&block);

		for (auto empty_block : empty_blocks)
		{
			builder.SetInsertPoint(empty_block);
			builder.CreateAlloca(llvm::IntegerType::get(context, 1), nullptr, "nop");
			builder.CreateBr(exit_block);
		}

		for (auto&& block : *func)
		{
			if (block.getTerminator() == nullptr)
			{
				builder.SetInsertPoint(&block);
				builder.CreateBr(exit_block);
			}
		}

		label_blocks.clear();

		exit_block = nullptr;
		return_value = nullptr;

		llvm_value_map[&func_decl] = func;
	}

	void LLVMVisitor::ConditionalBranch(llvm::Value* condition_value, llvm::BasicBlock* true_block, llvm::BasicBlock* false_block)
	{
		if (IsPointer(condition_value->getType()))
		{
			if (isa<llvm::AllocaInst>(condition_value))
			{
				llvm::AllocaInst* alloca_inst = cast<llvm::AllocaInst>(condition_value);
				condition_value = builder.CreateLoad(alloca_inst->getAllocatedType(), condition_value);
			}
			else if (isa<llvm::GlobalVariable>(condition_value))
			{
				llvm::GlobalVariable* global_var_alloc = cast<llvm::GlobalVariable>(condition_value);
				condition_value = builder.CreateLoad(global_var_alloc->getValueType(), condition_value);
			}
		}

		if (IsBoolean(condition_value->getType()))
		{
			builder.CreateCondBr(condition_value, true_block, false_block);
		}
		else if (IsInteger(condition_value->getType()))
		{
			llvm::Value* condition = Load(int_type, condition_value);
			llvm::Value* boolean_cond = builder.CreateICmpNE(condition, llvm::ConstantInt::get(context, llvm::APInt(64, 0)));
			builder.CreateCondBr(boolean_cond, true_block, false_block);
		}
		else if (IsFloat(condition_value->getType()))
		{
			llvm::Value* condition = Load(float_type, condition_value);
			llvm::Value* boolean_cond = builder.CreateFCmpONE(condition, llvm::ConstantFP::get(context, llvm::APFloat(0.0)));
			builder.CreateCondBr(boolean_cond, true_block, false_block);
		}
		else OLA_ASSERT(false);
	}

	llvm::Type* LLVMVisitor::ConvertToLLVMType(QualType const& type)
	{
		switch (type->GetKind())
		{
		case TypeKind::Void:
			return void_type;
		case TypeKind::Bool:
			return bool_type;
		case TypeKind::Char:
			return char_type;
		case TypeKind::Int:
			return int_type;
		case TypeKind::Float:
			return float_type;
		case TypeKind::Array:
		{
			ArrayType const& array_type = type_cast<ArrayType>(type);
			if (array_type.GetArraySize() > 0) return llvm::ArrayType::get(ConvertToLLVMType(array_type.GetBaseType()), array_type.GetArraySize());
			else return GetPointerType(ConvertToLLVMType(array_type.GetBaseType()));
		}
		case TypeKind::Function:
		{
			FuncType const& function_type = type_cast<FuncType>(type);
			std::span<QualType const> function_params = function_type.GetParams();

			llvm::Type* return_type = ConvertToLLVMType(function_type.GetReturnType());
			bool return_type_struct = return_type->isStructTy();

			std::vector<llvm::Type*> param_types; param_types.reserve(function_params.size());
			if (return_type_struct) param_types.push_back(return_type->getPointerTo());

			for (auto const& func_param_type : function_params)
			{
				llvm::Type* param_type = ConvertToLLVMType(func_param_type);
				param_types.push_back(param_type);
			}
			return llvm::FunctionType::get(return_type_struct ? void_type : return_type, param_types, false);
		}
		case TypeKind::Class:
		{
			ClassType const& class_type = type_cast<ClassType>(type);
			ClassDecl const* class_decl = class_type.GetClassDecl();
			if (class_decl == nullptr) return nullptr;

			using LLVMStructTypeMap = std::unordered_map<ClassDecl const*, llvm::StructType*, VoidPointerHash>;
			static LLVMStructTypeMap struct_type_map;
			if (struct_type_map.contains(class_decl)) return struct_type_map[class_decl];

			llvm::StructType* llvm_class_type = llvm::StructType::create(context, class_decl->GetName());

			UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
			std::vector<llvm::Type*> llvm_member_types; llvm_member_types.reserve(fields.size());

			ClassDecl const* curr_class_decl = class_decl;
			while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
			{
				for (auto const& field : base_class_decl->GetFields()) llvm_member_types.push_back(ConvertToLLVMType(field->GetType()));
				curr_class_decl = base_class_decl;
			}
			for (auto const& field : fields) llvm_member_types.push_back(ConvertToLLVMType(field->GetType()));
			llvm_class_type->setBody(llvm_member_types, false);
			struct_type_map[class_decl] = llvm_class_type;
			return llvm_class_type;
		}
		case TypeKind::Ref:
		{
			RefType const& ref_type = type_cast<RefType>(type);
			return llvm::PointerType::get(ConvertToLLVMType(ref_type.GetReferredType()), 0);
		}
		default:
			OLA_UNREACHABLE();
		}
		return nullptr;
	}

	llvm::Type* LLVMVisitor::GetPointerType(llvm::Type* type)
	{
		return llvm::PointerType::get(type, 0);
	}

	llvm::Value* LLVMVisitor::Load(QualType const& type, llvm::Value* ptr)
	{
		llvm::Type* llvm_type = nullptr;
		if (RefType const* ref_type = dyn_type_cast<RefType>(type))
			 llvm_type = ConvertToLLVMType(ref_type->GetReferredType());
		else llvm_type = ConvertToLLVMType(type);
		return Load(llvm_type, ptr);
	}

	llvm::Value* LLVMVisitor::Load(llvm::Type* llvm_type, llvm::Value* ptr)
	{
		//#todo: refactor this
		if (IsPointer(ptr->getType()))
		{
			if (isa<llvm::AllocaInst>(ptr))
			{
				llvm::AllocaInst* alloc = cast<llvm::AllocaInst>(ptr);
				if (alloc->getAllocatedType()->isArrayTy())
				{
					llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(64, 0, true));
					llvm::ArrayType* array_type = cast<llvm::ArrayType>(alloc->getAllocatedType());
					return builder.CreateInBoundsGEP(array_type, ptr, { zero, zero });
				}
			}
			else if (IsPointer(llvm_type) && isa<llvm::GlobalVariable>(ptr))
			{
				return ptr;
			}
			return builder.CreateLoad(llvm_type, ptr);
		}
		return ptr;
	}

	llvm::Value* LLVMVisitor::Store(llvm::Value* value, llvm::Value* ptr)
	{
		if (!IsPointer(value->getType())) return builder.CreateStore(value, ptr);
		llvm::Value* load = Load(value->getType(), value);
		return builder.CreateStore(load, ptr);
	}

	bool LLVMVisitor::IsPointer(llvm::Type* type)
	{
		return type->isPointerTy();
	}

	bool LLVMVisitor::IsBoolean(llvm::Type* type)
	{
		return type->isIntegerTy() && type->getIntegerBitWidth() == 1;
	}

	bool LLVMVisitor::IsInteger(llvm::Type* type)
	{
		return type->isIntegerTy() && type->getIntegerBitWidth() == 64;
	}

	bool LLVMVisitor::IsFloat(llvm::Type* type)
	{
		return type->isDoubleTy();
	}

	bool LLVMVisitor::IsStruct(llvm::Type* type)
	{
		return type->isStructTy();
	}

	bool LLVMVisitor::IsRef(llvm::Type* type)
	{
		return type->isPointerTy();
	}
}


