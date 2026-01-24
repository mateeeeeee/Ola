#include "IRVisitor.h"
#include "IRBuilder.h"
#include "IRModule.h"
#include "IRContext.h"
#include "IRType.h"
#include "Instruction.h"
#include "Constant.h"
#include "BasicBlock.h"
#include "GlobalValue.h"
#include "Frontend/AST/AST.h"
#include "Frontend/AST/Decl.h"
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"

namespace ola
{

	IRVisitor::IRVisitor(IRContext& context, IRModule& module) : context(context), module(module)
	{
		builder = std::make_unique<IRBuilder>(context);

		void_type = IRVoidType::Get(context);
		bool_type = IRIntType::Get(context, 1);
		char_type = IRIntType::Get(context, 1);
		int_type = IRIntType::Get(context, 8);
		float_type = IRFloatType::Get(context);
	}

	IRVisitor::~IRVisitor()
	{
	}

	void IRVisitor::VisitAST(AST const* ast)
	{
		ast->translation_unit->Accept(*this);
	}

	void IRVisitor::Visit(ASTNode const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(TranslationUnit const& translation_unit, Uint32)
	{
		for (auto&& decl : translation_unit.GetDecls())
		{
			decl->Accept(*this);
		}
	}

	void IRVisitor::Visit(Decl const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(FunctionDecl const& function_decl, Uint32)
	{
		FuncType const* type = function_decl.GetFuncType();
		IRFuncType* function_type = cast<IRFuncType>(ConvertToIRType(type));
		Linkage linkage = function_decl.IsPublic() || function_decl.IsExtern() ? Linkage::External : Linkage::Internal;
		Function* ir_function = new Function(function_decl.GetMangledName(), function_type, linkage);
		module.AddGlobal(ir_function);

		Uint32 arg_index = 0;
		Argument* param_arg = ir_function->GetArg(arg_index);
		if (isa<ClassType>(type->GetReturnType()))
		{
			Value* sret_value = param_arg;
			++param_arg;
			return_value = sret_value;
		}
		for (auto& param : function_decl.GetParamDecls())
		{
			Value* ir_param = param_arg;
			ir_param->SetName(param->GetName());
			value_map[param.get()] = ir_param;
			param_arg = ir_function->GetArg(++arg_index);
		}

		if (!function_decl.HasDefinition())
		{
			return;
		}

		VisitFunctionDeclCommon(function_decl, ir_function);
	}

	void IRVisitor::Visit(MethodDecl const& method_decl, Uint32)
	{
		ClassDecl const* class_decl = method_decl.GetParentDecl();
		IRType* ir_class_type = ConvertClassDecl(class_decl);
		FuncType const* func_type = method_decl.GetFuncType();
		IRFuncType* ir_func_type = ConvertMethodType(func_type, ir_class_type);

		Linkage linkage = Linkage::External;
		std::string name(class_decl->GetName()); name += "$"; name += method_decl.GetMangledName();
		Function* ir_function = new Function(name, ir_func_type, linkage);
		module.AddGlobal(ir_function);

		Argument* param_arg = ir_function->GetArg(0);
		Uint32 arg_index = 0;
		if (isa<ClassType>(func_type->GetReturnType()))
		{
			Value* sret_value = param_arg;
			param_arg = ir_function->GetArg(++arg_index);
			return_value = sret_value;
		}

		Value* this_param = param_arg;
		this_param->SetName("this");
		this_struct_type = ir_class_type;
		this_value = this_param;

		param_arg = ir_function->GetArg(++arg_index);
		for (auto& param : method_decl.GetParamDecls())
		{
			Value* ir_param = param_arg;
			ir_param->SetName(param->GetName());
			value_map[param.get()] = ir_param;
			param_arg = ir_function->GetArg(++arg_index);
		}

		if (method_decl.HasDefinition())
		{
			VisitFunctionDeclCommon(method_decl, ir_function);
		}
		this_value = nullptr;
		this_struct_type = nullptr;
	}

	void IRVisitor::Visit(ConstructorDecl const& ctor_decl, Uint32)
	{
		ClassDecl const* class_decl = ctor_decl.GetParentDecl();
		IRType* ir_class_type = ConvertClassDecl(class_decl);
		FuncType const* func_type = ctor_decl.GetFuncType();
		IRFuncType* ir_func_type = ConvertMethodType(func_type, ir_class_type);

		Linkage linkage = Linkage::External;
		std::string name(class_decl->GetName()); name += "$"; name += ctor_decl.GetMangledName();
		Function* ir_function = new Function(name, ir_func_type, linkage);
		module.AddGlobal(ir_function);

		Argument* param_arg = ir_function->GetArg(0);
		Uint32 arg_index = 0;

		Value* this_param = param_arg;
		this_param->SetName("this");
		this_struct_type = ir_class_type;
		this_value = this_param;

		param_arg = ir_function->GetArg(++arg_index);
		for (auto& param : ctor_decl.GetParamDecls())
		{
			Value* ir_param = param_arg;
			ir_param->SetName(param->GetName());
			value_map[param.get()] = ir_param;
			param_arg = ir_function->GetArg(++arg_index);
		}

		if (ctor_decl.HasDefinition())
		{
			VisitFunctionDeclCommon(ctor_decl, ir_function);
		}
		this_value = nullptr;
		this_struct_type = nullptr;
	}

	void IRVisitor::Visit(ParamVarDecl const&, Uint32)
	{
	}

	void IRVisitor::Visit(FieldDecl const& field_decl, Uint32)
	{
		QualType const& var_type = field_decl.GetType();
		IRType* ir_type = ConvertToIRType(var_type);

		if (Expr const* init_expr = field_decl.GetInitExpr())
		{
			init_expr->Accept(*this);
			Value* init_value = value_map[init_expr];
			OLA_ASSERT(isa<Constant>(init_value));
			value_map[&field_decl] = cast<Constant>(init_value);
		}
		else
		{
			value_map[&field_decl] = Constant::GetNullValue(ir_type);
		}
	}

	void IRVisitor::Visit(VarDecl const& var_decl, Uint32)
	{
		Type const* var_type = var_decl.GetType().GetTypePtr();
		Bool const is_const = var_decl.GetType().IsConst();
		IRType* ir_type = ConvertToIRType(var_type);
		Bool const is_array = isa<ArrayType>(var_type);
		Bool const is_class = isa<ClassType>(var_type);
		Bool const is_ref = isa<RefType>(var_type);

		if (var_decl.IsGlobal())
		{
			if (var_decl.IsExtern())
			{
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, Linkage::External, nullptr);
				if (is_const)
				{
					global_var->SetReadOnly();
				}
				module.AddGlobal(global_var);
				value_map[&var_decl] = global_var;
			}
			else if (Expr const* init_expr = var_decl.GetInitExpr())
			{
				if (is_array)
				{
					ArrayType const* array_type = cast<ArrayType>(var_type);
					IRType* element_type = ConvertToIRType(array_type->GetElementType());

					if (InitializerListExpr const* init_list_expr = dyn_cast<InitializerListExpr>(init_expr))
					{
						OLA_ASSERT(init_list_expr->IsConstexpr());
						init_list_expr->Accept(*this);

						Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
						GlobalVariable* global_array = new GlobalVariable(var_decl.GetName(), ir_type, linkage, value_map[init_list_expr]);
						if (array_type->GetElementType().IsConst())
						{
							global_array->SetReadOnly();
						}
						module.AddGlobal(global_array);
						value_map[&var_decl] = global_array;
					}
					else if (StringLiteral const* string = dyn_cast<StringLiteral>(init_expr))
					{
						Constant* constant = new ConstantString(context, string->GetString());

						Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
						GlobalVariable* global_string = new GlobalVariable(var_decl.GetName(), ir_type, linkage, constant);
						if (array_type->GetElementType().IsConst())
						{
							global_string->SetReadOnly();
						}
						module.AddGlobal(global_string);
						value_map[&var_decl] = global_string;
					}
					else OLA_ASSERT(false);
				}
				else
				{
					OLA_ASSERT(init_expr->IsConstexpr());
					init_expr->Accept(*this);
					Value* init_value = value_map[init_expr];
					Constant* constant_init_value = dyn_cast<Constant>(init_value);
					OLA_ASSERT(constant_init_value);

					Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
					GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, linkage, init_value);
					if (is_const)
					{
						global_var->SetReadOnly();
					}
					module.AddGlobal(global_var);
					value_map[&var_decl] = global_var;
				}
			}
			else if (is_class)
			{
				ClassType const* class_type = cast<ClassType>(var_type);
				ClassDecl const* class_decl = class_type->GetClassDecl();

				UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
				std::vector<Constant*> initializers;
				if (class_decl->IsPolymorphic())
				{
					initializers.push_back(vtable_map[class_decl]);
				}

				ClassDecl const* curr_class_decl = class_decl;
				while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
				{
					for (auto const& base_field : base_class_decl->GetFields())
					{
						initializers.push_back(cast<Constant>(value_map[base_field.get()]));
					}
					curr_class_decl = base_class_decl;
				}
				for (Uint64 i = 0; i < fields.size(); ++i)
				{
					initializers.push_back(cast<Constant>(value_map[fields[i].get()]));
				}

				IRStructType* llvm_struct_type = cast<IRStructType>(ir_type);
				Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, linkage, nullptr);
				if (is_const)
				{
					global_var->SetReadOnly();
				}
				module.AddGlobal(global_var);
				value_map[&var_decl] = global_var;
			}
			else if (is_ref)
			{
				OLA_ASSERT_MSG(false, "todo");
			}
			else
			{
				Constant* constant_init_value = Constant::GetNullValue(ir_type); 
				Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, linkage, nullptr);
				if (is_const)
				{
					global_var->SetReadOnly();
				}
				module.AddGlobal(global_var);
				value_map[&var_decl] = global_var;
			}
		}
		else
		{
			if (Expr const* init_expr = var_decl.GetInitExpr(); init_expr && !isa<ConstructorExpr>(init_expr))
			{
				init_expr->Accept(*this);
				if (is_array)
				{
					ArrayType const* array_type = cast<ArrayType>(var_type);
					IRType* element_type = ConvertToIRType(array_type->GetElementType());
					ConstantInt* zero = context.GetInt64(0);
					if (InitializerListExpr const* init_list_expr = dyn_cast<InitializerListExpr>(init_expr))
					{
						Value* alloc = builder->MakeInst<AllocaInst>(ir_type);
						UniqueExprPtrList const& init_list = init_list_expr->GetInitList();

						for (Uint64 i = 0; i < init_list.size(); ++i)
						{
							ConstantInt* index = context.GetInt64(i);
							Value* indices[] = { zero, index };
							Value* ptr = builder->MakeInst<GetElementPtrInst>(alloc, indices);
							Store(value_map[init_list[i].get()], ptr);
						}
						for (Uint64 i = init_list.size(); i < array_type->GetArraySize(); ++i)
						{
							ConstantInt* index = context.GetInt64(i);
							Value* indices[] = { zero, index };
							Value* ptr = builder->MakeInst<GetElementPtrInst>(alloc, indices);
							Store(context.GetNullValue(element_type), ptr);
						}
						value_map[&var_decl] = alloc;
					}
					else if (StringLiteral const* string = dyn_cast<StringLiteral>(init_expr))
					{
						Value* alloc = builder->MakeInst<AllocaInst>(ir_type);
						std::string_view str = string->GetString();
						for (Uint64 i = 0; i < str.size(); ++i)
						{
							ConstantInt* index = context.GetInt64(i);
							Value* indices[] = { zero, index };
							Value* ptr = builder->MakeInst<GetElementPtrInst>(alloc, indices);
							Store(context.GetInt8(str[i]), ptr);
						}
						ConstantInt* index = context.GetInt64(str.size());
						Value* indices[] = { zero, index };
						Value* ptr = builder->MakeInst<GetElementPtrInst>(alloc, indices);
						Store(context.GetInt8('\0'), ptr);
						value_map[&var_decl] = alloc;
					}
					else if (isoneof<DeclRefExpr, ArrayAccessExpr>(init_expr))
					{
						OLA_ASSERT(isa<ArrayType>(init_expr->GetType()));
						IRType* init_expr_type = ConvertToIRType(init_expr->GetType());
						Value* alloc = builder->MakeInst<AllocaInst>(GetPointerType(element_type));
						Value* ptr = nullptr;
						if (init_expr_type->IsArray())
						{
							Value* indices[] = { zero, zero };
							ptr = builder->MakeInst<GetElementPtrInst>(value_map[init_expr], indices);
						}
						else
						{
							ptr = builder->MakeInst<LoadInst>(value_map[init_expr], init_expr_type);
						}
						builder->MakeInst<StoreInst>(ptr, alloc);
						value_map[&var_decl] = alloc;
					}
				}
				else if (is_class)
				{
					ClassType const* class_type = cast<ClassType>(var_type);
					ClassDecl const* class_decl = class_type->GetClassDecl();

					Value* struct_alloc = builder->MakeInst<AllocaInst>(ir_type);
					Value* init_value = value_map[init_expr];

					Bool const is_polymorphic = class_decl->IsPolymorphic();
					ConstantInt* zero = context.GetInt64(0);
					if (is_polymorphic)
					{
						ConstantInt* index = context.GetInt64(0);
						std::vector<Value*> indices = { zero, index };
						Value* field_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
						Store(vtable_map[class_decl], field_ptr);
					}

					ClassDecl const* curr_class_decl = class_decl;
					while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
					{
						UniqueFieldDeclPtrList const& base_fields = base_class_decl->GetFields();
						for (auto const& base_field : base_fields)
						{
							Uint32 field_idx = is_polymorphic + base_field->GetFieldIndex();
							ConstantInt* index = context.GetInt64(field_idx);
							std::vector<Value*> indices = { zero, index };
							Value* dst_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
							Value* src_ptr = builder->MakeInst<GetElementPtrInst>(init_value, indices);
							IRType* field_type = ConvertToIRType(base_field->GetType());
							Store(Load(field_type, src_ptr), dst_ptr);
						}
						curr_class_decl = base_class_decl;
					}

					UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
					for (auto const& field : fields)
					{
						Uint32 field_idx = is_polymorphic + field->GetFieldIndex();
						ConstantInt* index = context.GetInt64(field_idx);
						std::vector<Value*> indices = { zero, index };
						Value* dst_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
						Value* src_ptr = builder->MakeInst<GetElementPtrInst>(init_value, indices);
						IRType* field_type = ConvertToIRType(field->GetType());
						Store(Load(field_type, src_ptr), dst_ptr);
					}

					value_map[&var_decl] = struct_alloc;
				}
				else if (is_ref)
				{
					Value* alloc = builder->MakeInst<AllocaInst>(ir_type);
					Value* init_value = value_map[init_expr];
					builder->MakeInst<StoreInst>(init_value, alloc);
					Value* ref = builder->MakeInst<LoadInst>(alloc, ir_type); 
					value_map[&var_decl] = ref;
				}
				else
				{
					Value* alloc = builder->MakeInst<AllocaInst>(ir_type);
					Value* init_value = value_map[init_expr];
					Store(init_value, alloc);
					value_map[&var_decl] = alloc;
				}
			}
			else
			{
				if (is_class)
				{
					ClassType const* class_type = cast<ClassType>(var_type);
					ClassDecl const* class_decl = class_type->GetClassDecl();

					Value* struct_alloc = builder->MakeInst<AllocaInst>(ir_type);
					value_map[&var_decl] = struct_alloc;

					Bool const is_polymorphic = class_decl->IsPolymorphic();
					ConstantInt* zero = context.GetInt64(0);
					if (is_polymorphic)
					{
						ConstantInt* index = context.GetInt64(0);
						std::vector<Value*> indices = { zero, index };
						Value* field_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
						Store(vtable_map[class_decl], field_ptr);
					}

					ClassDecl const* curr_class_decl = class_decl;
					while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
					{
						UniqueFieldDeclPtrList const& base_fields = base_class_decl->GetFields();
						for (auto const& base_field : base_fields)
						{
							ConstantInt* index = context.GetInt64(is_polymorphic + base_field->GetFieldIndex());
							std::vector<Value*> indices = { zero, index };
							Value* field_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
							Store(value_map[base_field.get()], field_ptr);
						}
						curr_class_decl = base_class_decl;
					}
					UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
					for (auto const& field : fields)
					{
						ConstantInt* index = context.GetInt64(is_polymorphic + field->GetFieldIndex());
						std::vector<Value*> indices = { zero, index };
						Value* field_ptr = builder->MakeInst<GetElementPtrInst>(struct_alloc, indices);
						Store(value_map[field.get()], field_ptr);
					}

					Expr const* init_expr = var_decl.GetInitExpr();
					if (init_expr && isa<ConstructorExpr>(init_expr))
					{
						ConstructorExpr const* ctor_expr = cast<ConstructorExpr>(init_expr);
						std::string name(class_decl->GetName());
						name += "$";
						name += ctor_expr->GetCtorDecl()->GetMangledName();
						Function* called_ctor = module.GetFunctionByName(name);

						std::vector<Value*> args;
						Uint32 arg_index = 0;
						args.push_back(struct_alloc);
						++arg_index;
						for (auto const& arg_expr : ctor_expr->GetArgs())
						{
							arg_expr->Accept(*this);
							Value* arg_value = value_map[arg_expr.get()];
							OLA_ASSERT(arg_value);
							IRType* arg_type = called_ctor->GetArg(arg_index)->GetType();
							if (arg_type->IsPointer()) args.push_back(arg_value);
							else args.push_back(Load(arg_type, arg_value));
							++arg_index;
						}
						builder->MakeInst<CallInst>(called_ctor, args);
					}
				}
				else
				{
					Value* alloc = builder->MakeInst<AllocaInst>(ir_type);
					value_map[&var_decl] = alloc;
				}
			}
		}
	}

	void IRVisitor::Visit(TagDecl const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(EnumDecl const& enum_decl, Uint32)
	{
		for (auto const& enum_member : enum_decl.GetEnumMembers())
		{
			enum_member->Accept(*this);
		}
	}

	void IRVisitor::Visit(EnumMemberDecl const& enum_member_decl, Uint32)
	{
		ConstantInt* constant = context.GetInt64(enum_member_decl.GetValue());
		value_map[&enum_member_decl] = constant;
	}

	void IRVisitor::Visit(AliasDecl const&, Uint32)
	{
	}

	void IRVisitor::Visit(ClassDecl const& class_decl, Uint32)
	{
		for (auto& field : class_decl.GetFields())
		{
			field->Accept(*this);
		}
		for (auto& method : class_decl.GetMethods())
		{
			method->Accept(*this);
		}

		if (class_decl.IsPolymorphic())
		{
			std::vector<MethodDecl const*> const& vtable = class_decl.GetVTable();
			IRArrayType* vtable_type = context.GetArrayType(GetPointerType(void_type), vtable.size());
			std::vector<Constant*> vtable_function_ptrs;

			for (MethodDecl const* method : vtable)
			{
				Value* method_value = value_map[method];
				if (!method->IsPure())
				{
					Function* method_fn = cast<Function>(method_value);
					vtable_function_ptrs.push_back(method_fn);
				}
				else
				{
					vtable_function_ptrs.push_back(Constant::GetNullValue(GetPointerType(void_type)));
				}
			}

			std::string vtable_name = "VTable_";
			vtable_name += class_decl.GetName();
			ConstantArray* vtable_init = new ConstantArray(vtable_type, vtable_function_ptrs);
			GlobalVariable* vtable_var = new GlobalVariable(vtable_name, vtable_type, Linkage::Internal, vtable_init);
			// vtables cannot be read-only on macOS ARM64 because they contain function
			// pointers that require runtime relocation (illegal text-relocations)
			// vtable_var->SetReadOnly();
			module.AddGlobal(vtable_var);

			vtable_map[&class_decl] = vtable_var;
		}
	}

	void IRVisitor::Visit(Stmt const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(CompoundStmt const& compound_stmt, Uint32)
	{
		for (auto const& stmt : compound_stmt.GetStmts())
		{
			stmt->Accept(*this);
		}
	}

	void IRVisitor::Visit(DeclStmt const& decl_stmt, Uint32)
	{
		for (auto const& decl : decl_stmt.GetDecls())
		{
			decl->Accept(*this);
		}
	}

	void IRVisitor::Visit(ExprStmt const& expr_stmt, Uint32)
	{
		if (expr_stmt.GetExpr())
		{
			expr_stmt.GetExpr()->Accept(*this);
		}
	}

	void IRVisitor::Visit(NullStmt const&, Uint32)
	{

	}

	void IRVisitor::Visit(ReturnStmt const& return_stmt, Uint32)
	{
		BasicBlock* current_block = builder->GetCurrentBlock();
		Function* current_function = current_block->GetFunction();
		if (Expr const* return_expr = return_stmt.GetExprStmt()->GetExpr())
		{
			return_expr->Accept(*this);
			Value* return_expr_value = value_map[return_expr];
			OLA_ASSERT(return_expr_value);
			Store(return_expr_value, return_value);
		}
		builder->MakeInst<BranchInst>(context, exit_block);
		BasicBlock* return_block = builder->AddBlock(current_function, current_block->GetNextNode(), "return");
		builder->SetCurrentBlock(return_block);
	}

	void IRVisitor::Visit(IfStmt const& if_stmt, Uint32)
	{
		Expr const* cond_expr = if_stmt.GetCondExpr();
		Stmt const* then_stmt = if_stmt.GetThenStmt();
		Stmt const* else_stmt = if_stmt.GetElseStmt();

		Function* function = builder->GetCurrentFunction();
		BasicBlock* then_block = builder->AddBlock(function, exit_block, "if.then");
		BasicBlock* else_block = builder->AddBlock(function, exit_block, "if.else");
		BasicBlock* end_block  = builder->AddBlock(function, exit_block, "if.end");

		cond_expr->Accept(*this);
		Value* condition_value = value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, then_block, else_stmt ? else_block : end_block);

		builder->SetCurrentBlock(then_block);

		end_blocks.push_back(end_block);
		then_stmt->Accept(*this);
		if (!then_block->GetTerminator())
		{
			builder->MakeInst<BranchInst>(context, end_block);
		}
		if (else_stmt)
		{
			builder->SetCurrentBlock(else_block);
			else_stmt->Accept(*this);
			if (!else_block->GetTerminator())
			{
				builder->MakeInst<BranchInst>(context, end_block);
			}
		}
		end_blocks.pop_back();

		builder->SetCurrentBlock(end_block);
		empty_block_successors[end_block] = end_blocks.empty() ? exit_block : end_blocks.back();
	}

	void IRVisitor::Visit(BreakStmt const& break_stmt, Uint32)
	{
		OLA_ASSERT(!break_blocks.empty());
		builder->MakeInst<BranchInst>(context, break_blocks.back());
		BasicBlock* break_block = builder->AddBlock(builder->GetCurrentFunction(), exit_block, "break");
		builder->SetCurrentBlock(break_block);
	}

	void IRVisitor::Visit(ContinueStmt const& continue_stmt, Uint32)
	{
		OLA_ASSERT(!continue_blocks.empty());

		builder->MakeInst<BranchInst>(context, continue_blocks.back());
		BasicBlock* continue_block = builder->AddBlock(builder->GetCurrentFunction(), exit_block, "continue");
		builder->SetCurrentBlock(continue_block);
	}

	void IRVisitor::Visit(ForStmt const& for_stmt, Uint32)
	{
		Stmt const* init_stmt = for_stmt.GetInitStmt();
		Expr const* cond_expr = for_stmt.GetCondExpr();
		Expr const* iter_expr = for_stmt.GetIterExpr();
		Stmt const* body_stmt = for_stmt.GetBodyStmt();

		Function* function = builder->GetCurrentFunction();
		BasicBlock* body_block = builder->AddBlock(function, exit_block, "for.body");
		BasicBlock* cond_block = builder->AddBlock(function, exit_block, "for.cond");
		BasicBlock* iter_block = builder->AddBlock(function, exit_block, "for.iter");
		BasicBlock* end_block  = builder->AddBlock(function, exit_block, "for.end"); 

		if (init_stmt)
		{
			init_stmt->Accept(*this);
		}
		builder->MakeInst<BranchInst>(context, cond_block);
		builder->SetCurrentBlock(cond_block);
		if (cond_expr)
		{
			cond_expr->Accept(*this);
			Value* condition_value = value_map[cond_expr];
			OLA_ASSERT(condition_value);
			ConditionalBranch(condition_value, body_block, end_block);
		}
		else
		{
			builder->MakeInst<BranchInst>(context, body_block);
		}
		builder->SetCurrentBlock(body_block);

		end_blocks.push_back(end_block);
		continue_blocks.push_back(iter_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();
		end_blocks.pop_back();

		builder->MakeInst<BranchInst>(context, iter_block);
		builder->SetCurrentBlock(iter_block);
		if (iter_expr)
		{
			iter_expr->Accept(*this);
		}
		builder->MakeInst<BranchInst>(context, cond_block);

		builder->SetCurrentBlock(end_block);
		empty_block_successors[end_block] = end_blocks.empty() ? exit_block : end_blocks.back();
	}

	void IRVisitor::Visit(WhileStmt const& while_stmt, Uint32)
	{
		Expr const* cond_expr = while_stmt.GetCondExpr();
		Stmt const* body_stmt = while_stmt.GetBodyStmt();

		Function* function = builder->GetCurrentFunction();
		BasicBlock* cond_block = builder->AddBlock(function, exit_block, "while.cond");
		BasicBlock* body_block = builder->AddBlock(function, exit_block, "while.body");
		BasicBlock* end_block = builder->AddBlock(function, exit_block, "while.end");

		builder->MakeInst<BranchInst>(context, cond_block);
		builder->SetCurrentBlock(cond_block);
		cond_expr->Accept(*this);
		Value* condition_value = value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, body_block, end_block);

		builder->SetCurrentBlock(body_block);

		end_blocks.push_back(end_block);
		continue_blocks.push_back(cond_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();
		end_blocks.pop_back();

		builder->MakeInst<BranchInst>(context, cond_block);

		builder->SetCurrentBlock(end_block);
		empty_block_successors[end_block] = end_blocks.empty() ? exit_block : end_blocks.back();
	}

	void IRVisitor::Visit(DoWhileStmt const& do_while_stmt, Uint32)
	{
		Expr const* cond_expr = do_while_stmt.GetCondExpr();
		Stmt const* body_stmt = do_while_stmt.GetBodyStmt();

		Function* function = builder->GetCurrentFunction();
		BasicBlock* body_block = builder->AddBlock(function, exit_block, "dowhile.body");
		BasicBlock* cond_block = builder->AddBlock(function, exit_block, "dowhile.cond");
		BasicBlock* end_block = builder->AddBlock(function, exit_block, "dowhile.end");  

		builder->MakeInst<BranchInst>(context, body_block);
		builder->SetCurrentBlock(body_block);

		end_blocks.push_back(end_block);
		continue_blocks.push_back(cond_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		continue_blocks.pop_back();
		end_blocks.pop_back();

		builder->MakeInst<BranchInst>(context, cond_block);
		builder->SetCurrentBlock(cond_block);

		cond_expr->Accept(*this);
		Value* condition_value = value_map[cond_expr];
		OLA_ASSERT(condition_value);
		ConditionalBranch(condition_value, body_block, end_block);

		builder->SetCurrentBlock(end_block);
		empty_block_successors[end_block] = end_blocks.empty() ? exit_block : end_blocks.back();
	}

	void IRVisitor::Visit(CaseStmt const& case_stmt, Uint32)
	{
		OLA_ASSERT(!switch_instructions.empty());
		SwitchInst* switch_inst = switch_instructions.back();
		if (case_stmt.IsDefault())
		{
			builder->SetCurrentBlock(switch_inst->GetDefaultCase());
		}
		else
		{
			Int64 case_value = case_stmt.GetValue();
			Function* function = builder->GetCurrentFunction();
			std::string block_name = "switch.case"; block_name += std::to_string(case_value);
			BasicBlock* case_block = builder->AddBlock(function, exit_block, block_name);
			switch_inst->AddCase(case_value, case_block);
			builder->SetCurrentBlock(case_block);
		}
	}

	void IRVisitor::Visit(SwitchStmt const& switch_stmt, Uint32)
	{
		Expr const* cond_expr = switch_stmt.GetCondExpr();
		Stmt const* body_stmt = switch_stmt.GetBodyStmt();

		Function* function = builder->GetCurrentFunction();
		BasicBlock* header_block	= builder->AddBlock(function, exit_block, "switch.header");  
		BasicBlock* default_block	= builder->AddBlock(function, exit_block, "switch.default"); 
		BasicBlock* end_block		= builder->AddBlock(function, exit_block, "switch.end");     

		builder->MakeInst<BranchInst>(context, header_block);
		builder->SetCurrentBlock(header_block);

		cond_expr->Accept(*this);
		Value* condition_value = value_map[cond_expr];
		OLA_ASSERT(condition_value);
		Value* condition = Load(int_type, condition_value);
		SwitchInst* switch_inst = static_cast<SwitchInst*>(builder->MakeInst<SwitchInst>(condition, default_block));

		switch_instructions.push_back(switch_inst);
		end_blocks.push_back(end_block);
		break_blocks.push_back(end_block);
		body_stmt->Accept(*this);
		break_blocks.pop_back();
		end_blocks.pop_back();
		switch_instructions.pop_back();

		std::vector<BasicBlock*> case_blocks;
		for (Uint32 i = 0; i < switch_inst->GetNumCases(); ++i)
		{
			case_blocks.push_back(switch_inst->GetCaseBlock(i));
		}
		for (Uint32 i = 0; i < case_blocks.size(); ++i)
		{
			BasicBlock* case_block = case_blocks[i];
			if (!case_block->GetTerminator())
			{
				BasicBlock* dest_block = i < case_blocks.size() - 1 ? case_blocks[i + 1] : default_block;
				builder->SetCurrentBlock(case_block);
				builder->MakeInst<BranchInst>(context, dest_block);
			}
		}
		builder->SetCurrentBlock(end_block);
		empty_block_successors[end_block] = end_blocks.empty() ? exit_block : end_blocks.back();
	}

	void IRVisitor::Visit(GotoStmt const& goto_stmt, Uint32)
	{
		std::string label_name(goto_stmt.GetLabelName());
		builder->MakeInst<BranchInst>(context, label_blocks[label_name]);

		BasicBlock* goto_block = builder->AddBlock(exit_block, "goto");
		builder->SetCurrentBlock(goto_block);
	}

	void IRVisitor::Visit(LabelStmt const& label_stmt, Uint32)
	{
		std::string label_name(label_stmt.GetName());
		BasicBlock* label_block = label_blocks[label_name];
		builder->MakeInst<BranchInst>(context, label_block);
		builder->SetCurrentBlock(label_block);
	}

	void IRVisitor::Visit(Expr const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(UnaryExpr const& unary_expr, Uint32)
	{
		Expr const* operand_expr = unary_expr.GetOperand();
		operand_expr->Accept(*this);
		Value* operand_value = value_map[operand_expr];
		OLA_ASSERT(operand_value);
		Value* operand = Load(operand_expr->GetType(), operand_value);

		Bool const is_float_expr = isa<FloatType>(operand_expr->GetType());
		Value* result = nullptr;
		Constant* zero = nullptr;
		Constant* one = nullptr;
		if (is_float_expr)
		{
			one  = context.GetFloat(1.0);
			zero = context.GetFloat(0.0);
		}
		else
		{
			zero = cast<IRIntType>(operand->GetType())->GetWidth() == 1 ? context.GetInt8(0) : context.GetInt64(0);
			one  = cast<IRIntType>(operand->GetType())->GetWidth() == 1 ? context.GetInt8(1) : context.GetInt64(1);
		}

		switch (unary_expr.GetUnaryKind())
		{
		case UnaryExprKind::PreIncrement:
		{
			Value* incremented_value = nullptr;
			incremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FAdd : Opcode::Add, operand, one);
			Store(incremented_value, operand_value);
			result = incremented_value;
		}
		break;
		case UnaryExprKind::PreDecrement:
		{
			Value* decremented_value = nullptr;
			decremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FSub : Opcode::Sub, operand, one);
			Store(decremented_value, operand_value);
			result = decremented_value;
		}
		break;
		case UnaryExprKind::PostIncrement:
		{
			result = builder->MakeInst<AllocaInst>(operand_value->GetType());
			Store(operand, result);
			Value* incremented_value = nullptr;
			incremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FAdd : Opcode::Add, operand, one);
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder->MakeInst<AllocaInst>(operand_value->GetType());
			Store(operand, result);
			Value* decremented_value = nullptr;
			decremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FSub : Opcode::Sub, operand, one);
			Store(decremented_value, operand_value);
		}
		break;
		case UnaryExprKind::Plus:
		{
			result = operand;
		}
		break;
		case UnaryExprKind::Minus:
		{
			result = is_float_expr ? builder->MakeInst<UnaryInst>(Opcode::FNeg, operand) : builder->MakeInst<UnaryInst>(Opcode::Neg, operand);
		}
		break;
		case UnaryExprKind::BitNot:
		{
			result = builder->MakeInst<UnaryInst>(Opcode::Not, operand);
		}
		break;
		case UnaryExprKind::LogicalNot:
		{
			result = builder->MakeInst<CompareInst>(is_float_expr ? Opcode::FCmpUEQ : Opcode::ICmpEQ, operand, zero);
		}
		break;
		default:
			OLA_ASSERT(false);
		}
		OLA_ASSERT(result);
		value_map[&unary_expr] = result;
	}

	void IRVisitor::Visit(BinaryExpr const& binary_expr, Uint32)
	{
		Expr const* lhs_expr = binary_expr.GetLHS();
		lhs_expr->Accept(*this);
		Value* lhs_value = value_map[lhs_expr];
		Expr const* rhs_expr = binary_expr.GetRHS();
		rhs_expr->Accept(*this);
		Value* rhs_value = value_map[rhs_expr];
		OLA_ASSERT(lhs_value && rhs_value);

		Value* lhs = nullptr;
		Value* rhs = nullptr;
		if (binary_expr.GetBinaryKind() != BinaryExprKind::Assign)
		{
			lhs = Load(lhs_expr->GetType(), lhs_value);
			rhs = Load(rhs_expr->GetType(), rhs_value);
		}
		Bool const is_float_expr = isa<FloatType>(lhs_expr->GetType()) || isa<FloatType>(rhs_expr->GetType());

		Value* result = nullptr;
		switch (binary_expr.GetBinaryKind())
		{
		case BinaryExprKind::Assign:
		{
			result = Store(rhs_value, lhs_value);
		}
		break;
		case BinaryExprKind::Add:
		{
			Opcode id = is_float_expr ? Opcode::FAdd : Opcode::Add;
			result = builder->MakeInst<BinaryInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Subtract:
		{
			Opcode id = is_float_expr ? Opcode::FSub : Opcode::Sub;
			result = builder->MakeInst<BinaryInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Multiply:
		{
			Opcode id = is_float_expr ? Opcode::FMul : Opcode::SMul;
			result = builder->MakeInst<BinaryInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Divide:
		{
			Opcode id = is_float_expr ? Opcode::FDiv : Opcode::SDiv;
			result = builder->MakeInst<BinaryInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Modulo:
		{
			OLA_ASSERT(!is_float_expr);
			result = builder->MakeInst<BinaryInst>(Opcode::SRem, lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftLeft:
		{
			result = builder->MakeInst<BinaryInst>(Opcode::Shl, lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftRight:
		{
			result = builder->MakeInst<BinaryInst>(Opcode::AShr, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitAnd:
		{
			result = builder->MakeInst<BinaryInst>(Opcode::And, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitOr:
		{
			result = builder->MakeInst<BinaryInst>(Opcode::Or, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitXor:
		{
			result = builder->MakeInst<BinaryInst>(Opcode::Xor, lhs, rhs);
		}
		break;
		case BinaryExprKind::LogicalAnd:
		{
			Value* tmp = builder->MakeInst<BinaryInst>(Opcode::And, lhs, rhs);
			Constant* zero = cast<IRIntType>(tmp->GetType())->GetWidth() == 1 ? context.GetInt8(0) : context.GetInt64(0);
			result = builder->MakeInst<CompareInst>(Opcode::ICmpNE, tmp, zero);
		}
		break;
		case BinaryExprKind::LogicalOr:
		{
			Value* tmp = builder->MakeInst<BinaryInst>(Opcode::Or, lhs, rhs);
			Constant* zero = cast<IRIntType>(tmp->GetType())->GetWidth() == 1 ? context.GetInt8(0) : context.GetInt64(0);
			result = builder->MakeInst<CompareInst>(Opcode::ICmpNE, tmp, zero);
		}
		break;
		case BinaryExprKind::Equal:
		{
			Opcode id = is_float_expr ? Opcode::FCmpOEQ : Opcode::ICmpEQ;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::NotEqual:
		{
			Opcode id = is_float_expr ? Opcode::FCmpONE : Opcode::ICmpNE;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Less:
		{
			Opcode id = is_float_expr ? Opcode::FCmpOLT : Opcode::ICmpSLT;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::Greater:
		{
			Opcode id = is_float_expr ? Opcode::FCmpOGT : Opcode::ICmpSGT;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::LessEqual:
		{
			Opcode id = is_float_expr ? Opcode::FCmpOLE : Opcode::ICmpSLE;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
		}
		break;
		case BinaryExprKind::GreaterEqual:
		{
			Opcode id = is_float_expr ? Opcode::FCmpOGE : Opcode::ICmpSGE;
			result = builder->MakeInst<CompareInst>(id, lhs, rhs);
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
		value_map[&binary_expr] = result;
	}

	void IRVisitor::Visit(TernaryExpr const& ternary_expr, Uint32)
	{
		Expr const* cond_expr = ternary_expr.GetCondExpr();
		Expr const* true_expr = ternary_expr.GetTrueExpr();
		Expr const* false_expr = ternary_expr.GetFalseExpr();

		cond_expr->Accept(*this);
		Value* condition_value = value_map[cond_expr];
		OLA_ASSERT(condition_value);
		condition_value = Load(bool_type, condition_value);

		true_expr->Accept(*this);
		Value* true_value = value_map[true_expr];
		OLA_ASSERT(true_value);
		true_value = Load(true_expr->GetType(), true_value);

		false_expr->Accept(*this);
		Value* false_value = value_map[false_expr];
		OLA_ASSERT(false_value);
		false_value = Load(false_expr->GetType(), false_value);

		OLA_ASSERT(condition_value->GetType() == context.GetIntegerType(1));
		value_map[&ternary_expr] = builder->MakeInst<SelectInst>(condition_value, true_value, false_value);
	}

	void IRVisitor::Visit(IdentifierExpr const&, Uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(DeclRefExpr const& decl_ref, Uint32)
	{
		Value* value = value_map[decl_ref.GetDecl()];
		OLA_ASSERT(value);
		value_map[&decl_ref] = value;
	}

	void IRVisitor::Visit(IntLiteral const& int_constant, Uint32)
	{
		ConstantInt* constant = context.GetInt64(int_constant.GetValue()); 
		value_map[&int_constant] = constant;
	}

	void IRVisitor::Visit(CharLiteral const& char_constant, Uint32)
	{
		ConstantInt* constant = context.GetInt8(char_constant.GetChar());
		value_map[&char_constant] = constant;
	}

	void IRVisitor::Visit(StringLiteral const& string_constant, Uint32)
	{
		context.GetString(string_constant.GetString());

		Constant* constant = context.GetString(string_constant.GetString());

		static Uint32 counter = 0;
		std::string name = "__StringLiteral"; name += std::to_string(counter++);

		Linkage linkage = Linkage::Internal;
		GlobalVariable* global_string = new GlobalVariable(name, ConvertToIRType(string_constant.GetType()), linkage, constant);
		global_string->SetReadOnly();
		module.AddGlobal(global_string);
		value_map[&string_constant] = global_string;
	}

	void IRVisitor::Visit(BoolLiteral const& bool_constant, Uint32)
	{
		ConstantInt* constant = context.GetInt8(bool_constant.GetValue()); 
		value_map[&bool_constant] = constant;
	}

	void IRVisitor::Visit(FloatLiteral const& float_constant, Uint32)
	{
		ConstantFloat* constant = context.GetFloat(float_constant.GetValue());
		value_map[&float_constant] = constant;
	}

	void IRVisitor::Visit(ImplicitCastExpr const& cast_expr, Uint32)
	{
		Expr const* cast_operand_expr = cast_expr.GetOperand();
		cast_operand_expr->Accept(*this);
		Value* cast_operand_value = value_map[cast_operand_expr];
		OLA_ASSERT(cast_operand_value);

		IRType* cast_type = ConvertToIRType(cast_expr.GetType());
		IRType* cast_operand_type = ConvertToIRType(cast_operand_expr->GetType());

		Value* cast_operand = Load(cast_operand_type, cast_operand_value);
		if (cast_type == int_type)
		{
			if (cast_operand_type == bool_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CastInst>(Opcode::ZExt, int_type, cast_operand);
			}
			else if (cast_operand_type == float_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CastInst>(Opcode::F2S, int_type, cast_operand);
			}
			else if (cast_operand_type->IsPointer())
			{
				value_map[&cast_expr] = builder->MakeInst<LoadInst>(cast_operand_value, int_type);
			}
			else OLA_ASSERT(false);
		}
		else if (cast_type == bool_type)
		{
			if (cast_operand_type == int_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CompareInst>(Opcode::ICmpNE, cast_operand, context.GetInt64(0));
			}
			else if (cast_operand_type == float_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CompareInst>(Opcode::FCmpONE, cast_operand, context.GetFloat(0.0));
			}
			else if (cast_operand_type->IsPointer())
			{
				value_map[&cast_expr] = builder->MakeInst<LoadInst>(cast_operand_value, bool_type);
			}
			else OLA_ASSERT(false);
		}
		else if (cast_type == float_type)
		{
			if (cast_operand_type == bool_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CastInst>(Opcode::S2F, float_type, cast_operand);
			}
			else if (cast_operand_type == int_type)
			{
				value_map[&cast_expr] = builder->MakeInst<CastInst>(Opcode::S2F, float_type, cast_operand);
			}
			else if (cast_operand_type->IsPointer())
			{
				value_map[&cast_expr] = builder->MakeInst<LoadInst>(cast_operand_value, float_type);
			}
			else OLA_ASSERT(false);
		}
		else if (cast_type->IsStruct())
		{
			if (cast_operand_type->IsPointer())
			{
				value_map[&cast_expr] = cast_operand_value;
			}
			else if (cast_operand_type->IsStruct())
			{
				//Value* bitcast_value = builder.CreateBitCast(cast_operand_value, GetPointerType(cast_type));
				//value_map[&cast_expr] = builder.CreateStructGEP(cast_type, bitcast_value, 0);
			}
			else OLA_ASSERT(false);
		}
		else if (cast_type->IsPointer())
		{
			value_map[&cast_expr] = cast_operand_value;
		}
		else OLA_ASSERT(value_map[&cast_expr] != nullptr);
	}

	void IRVisitor::Visit(CallExpr const& call_expr, Uint32)
	{
		Function* called_function = module.GetFunctionByName(call_expr.GetFunctionDecl()->GetMangledName());
		OLA_ASSERT(called_function);

		std::vector<Value*> args;
		Uint32 arg_index = 0;
		Bool return_struct = isa<ClassType>(call_expr.GetCalleeType()->GetReturnType());
		Value* return_alloc = nullptr;
		if (return_struct)
		{
			return_alloc = builder->MakeInst<AllocaInst>(called_function->GetArg(arg_index)->GetType());
			args.push_back(return_alloc);
			++arg_index;
		}
		for (auto const& arg_expr : call_expr.GetArgs())
		{
			arg_expr->Accept(*this);
			Value* arg_value = value_map[arg_expr.get()];
			OLA_ASSERT(arg_value);
			IRType* arg_type = called_function->GetArg(arg_index)->GetType();
			if (arg_type->IsPointer()) args.push_back(arg_value);
			else args.push_back(Load(arg_type, arg_value));

			arg_index++;
		}

		Value* call_result = builder->MakeInst<CallInst>(called_function, args);
		value_map[&call_expr] = return_alloc ? return_alloc : call_result;
	}

	void IRVisitor::Visit(InitializerListExpr const& initializer_list_expr, Uint32)
	{
		UniqueExprPtrList const& init_expr_list = initializer_list_expr.GetInitList();
		for (auto const& element_expr : init_expr_list) element_expr->Accept(*this);
		if (initializer_list_expr.IsConstexpr())
		{
			ArrayType const* array_type = cast<ArrayType>(initializer_list_expr.GetType());
			IRType* ir_element_type = ConvertToIRType(array_type->GetElementType());
			IRType* ir_array_type = ConvertToIRType(array_type);
			OLA_ASSERT(isa<IRArrayType>(ir_array_type));

			std::vector<Constant*> array_init_list(array_type->GetArraySize());
			for (Uint64 i = 0; i < array_type->GetArraySize(); ++i)
			{
				if (i < init_expr_list.size())
				{
					array_init_list[i] = dyn_cast<Constant>(value_map[init_expr_list[i].get()]);
				}
				else
				{
					array_init_list[i] = context.GetNullValue(ir_element_type);
				}
			}
			Constant* constant_array = new ConstantArray(cast<IRArrayType>(ir_array_type), array_init_list);
			value_map[&initializer_list_expr] = constant_array;
		}
	}

	void IRVisitor::Visit(ArrayAccessExpr const& array_access, Uint32)
	{
		Expr const* array_expr = array_access.GetArrayExpr();
		Expr const* index_expr = array_access.GetIndexExpr();

		array_expr->Accept(*this);
		index_expr->Accept(*this);

		Value* array_value = value_map[array_expr];
		Value* index_value = value_map[index_expr];
		OLA_ASSERT(array_value && index_value);
		index_value = Load(int_type, index_value);

		ConstantInt* zero = context.GetInt64(0);
		if (AllocaInst* alloc = dyn_cast<AllocaInst>(array_value))
		{
			IRType* alloc_type = alloc->GetAllocatedType();
			if (alloc_type->IsArray())
			{
				std::vector<Value*> indices = { zero, index_value };
				Value* ptr = builder->MakeInst<GetElementPtrInst>(alloc, indices);
				value_map[&array_access] = ptr;
			}
			else if (alloc_type->IsPointer())
			{
				std::vector<Value*> indices = { index_value };
				Value* ptr = builder->MakeInst<GetElementPtrInst>(Load(alloc_type, alloc), indices);
				value_map[&array_access] = ptr;
			}
			else OLA_ASSERT(false);
		}
		else
		{
			Type const* array_expr_type = array_expr->GetType();
			OLA_ASSERT(isa<ArrayType>(array_expr_type));
			ArrayType const* array_type = cast<ArrayType>(array_expr_type);
			if (isa<ArrayType>(array_type->GetElementType()))
			{
				Uint32 array_size = array_type->GetArraySize();
				index_value = builder->MakeInst<BinaryInst>(Opcode::SMul, index_value, context.GetInt64(array_size));
			}
			std::vector<Value*> indices = { zero, index_value };
			Value* ptr = builder->MakeInst<GetElementPtrInst>(array_value, indices);
			value_map[&array_access] = ptr;
		}
	}

	void IRVisitor::Visit(MemberExpr const& member_expr, Uint32)
	{
		Expr const* class_expr = member_expr.GetClassExpr();
		Decl const* member_decl = member_expr.GetMemberDecl();
		class_expr->Accept(*this);
		Value* struct_value = value_map[class_expr];

		if (isa<FieldDecl>(member_decl))
		{
			FieldDecl const* field_decl = cast<FieldDecl>(member_decl);
			Uint32 field_index = field_decl->GetFieldIndex() + field_decl->GetParentDecl()->IsPolymorphic();
			ConstantInt* zero = context.GetInt64(0);
			ConstantInt* index = context.GetInt64(field_index);
			std::vector<Value*> indices = { zero, index };
			Value* field_value = builder->MakeInst<GetElementPtrInst>(struct_value, indices);
			value_map[&member_expr] = field_value;
		}
		else if (isa<MethodDecl>(member_decl))
		{
			OLA_ASSERT(false);
		}
		else OLA_ASSERT(false);
	}

	void IRVisitor::Visit(MethodCallExpr const& method_call_expr, Uint32)
	{
		Expr const* callee_expr = method_call_expr.GetCallee();
		OLA_ASSERT(isa<MemberExpr>(callee_expr));
		MemberExpr const* member_expr = cast<MemberExpr>(callee_expr);

		Decl const* decl = member_expr->GetMemberDecl();
		OLA_ASSERT(isa<MethodDecl>(decl));
		MethodDecl const* method_decl = cast<MethodDecl>(decl);
		ClassDecl const* class_decl = method_decl->GetParentDecl();

		Expr const* class_expr = member_expr->GetClassExpr();
		class_expr->Accept(*this);

		if (!isa<SuperExpr>(class_expr) && method_decl->IsVirtual())
		{
			// Virtual dispatch: load function pointer from vtable and call indirectly
			Value* this_ptr = value_map[class_expr];
			ConstantInt* zero = context.GetInt64(0);

			// 1. Get pointer to vtable pointer (first field of object, index 0)
			std::vector<Value*> vtable_ptr_indices = { zero, zero };
			Value* vtable_ptr_addr = builder->MakeInst<GetElementPtrInst>(this_ptr, vtable_ptr_indices);

			// 2. Load vtable pointer
			Value* vtable_ptr = Load(GetPointerType(GetPointerType(void_type)), vtable_ptr_addr);

			// 3. Index into vtable to get function pointer address
			Uint32 vtable_idx = method_decl->GetVTableIndex();
			std::vector<Value*> func_ptr_indices = { context.GetInt64(vtable_idx) };
			Value* func_ptr_addr = builder->MakeInst<GetElementPtrInst>(vtable_ptr, func_ptr_indices);

			// 4. Load the function pointer
			Value* func_ptr = Load(GetPointerType(void_type), func_ptr_addr);

			// 5. Determine return type and build args
			FuncType const* func_type = method_decl->GetFuncType();
			IRType* ir_class_type = ConvertClassDecl(class_decl);
			IRFuncType* ir_func_type = ConvertMethodType(func_type, ir_class_type);
			IRType* return_type = ir_func_type->GetReturnType();

			std::vector<Value*> args;
			Uint32 arg_index = 0;
			Bool return_struct = isa<ClassType>(method_call_expr.GetCalleeType()->GetReturnType());
			Value* return_alloc = nullptr;
			if (return_struct)
			{
				IRType* sret_type = ir_func_type->GetParamType(arg_index);
				return_alloc = builder->MakeInst<AllocaInst>(sret_type);
				args.push_back(return_alloc);
				++arg_index;
			}

			args.push_back(this_ptr);
			++arg_index;

			for (auto const& arg_expr : method_call_expr.GetArgs())
			{
				arg_expr->Accept(*this);
				Value* arg_value = value_map[arg_expr.get()];
				OLA_ASSERT(arg_value);
				IRType* arg_type = ir_func_type->GetParamType(arg_index);
				if (arg_type->IsPointer()) args.push_back(arg_value);
				else args.push_back(Load(arg_type, arg_value));
				++arg_index;
			}

			// 6. Create indirect call with explicit return type
			Value* call_result = builder->MakeInst<CallInst>(func_ptr, args, return_type);
			value_map[&method_call_expr] = return_alloc ? return_alloc : call_result;
		}
		else
		{
			std::string name(class_decl->GetName());
			name += "$";
			name += method_call_expr.GetFunctionDecl()->GetMangledName();
			Function* called_function = module.GetFunctionByName(name);
			OLA_ASSERT(called_function);

			std::vector<Value*> args;
			Uint32 arg_index = 0;
			Bool return_struct = isa<ClassType>(method_call_expr.GetCalleeType()->GetReturnType());
			Value* return_alloc = nullptr;
			if (return_struct)
			{
				return_alloc = builder->MakeInst<AllocaInst>(called_function->GetArg(arg_index)->GetType());
				args.push_back(return_alloc);
				++arg_index;
			}

			Value* this_ptr = value_map[class_expr];
			args.push_back(this_ptr);
			++arg_index;

			for (auto const& arg_expr : method_call_expr.GetArgs())
			{
				arg_expr->Accept(*this);
				Value* arg_value = value_map[arg_expr.get()];
				OLA_ASSERT(arg_value);
				IRType* arg_type = called_function->GetArg(arg_index)->GetType();
				if (arg_type->IsPointer()) args.push_back(arg_value);
				else args.push_back(Load(arg_type, arg_value));
				++arg_index;
			}

			Value* call_result = builder->MakeInst<CallInst>(called_function, args);
			value_map[&method_call_expr] = return_alloc ? return_alloc : call_result;
		}
	}

	void IRVisitor::Visit(ThisExpr const& this_expr, Uint32)
	{
		value_map[&this_expr] = this_value;
	}

	void IRVisitor::Visit(SuperExpr const& super_expr, Uint32)
	{
		value_map[&super_expr] = this_value;
	}

	void IRVisitor::Visit(ConstructorExpr const& ctor_expr, Uint32)
	{
		ConstructorDecl const* ctor_decl = ctor_expr.GetCtorDecl();
		ClassDecl const* class_decl = ctor_decl->GetParentDecl();

		std::string name(class_decl->GetName());
		name += "$";
		name += ctor_decl->GetMangledName();
		Function* called_ctor = module.GetFunctionByName(name);
		OLA_ASSERT(called_ctor);

		std::vector<Value*> args;
		Uint32 arg_index = 0;
		args.push_back(this_value);
		++arg_index;

		for (auto const& arg_expr : ctor_expr.GetArgs())
		{
			arg_expr->Accept(*this);
			Value* arg_value = value_map[arg_expr.get()];
			OLA_ASSERT(arg_value);
			IRType* arg_type = called_ctor->GetArg(arg_index)->GetType();
			if (arg_type->IsPointer()) args.push_back(arg_value);
			else args.push_back(Load(arg_type, arg_value));
			++arg_index;
		}
		builder->MakeInst<CallInst>(called_ctor, args);
	}

	void IRVisitor::VisitFunctionDeclCommon(FunctionDecl const& func_decl, Function* func)
	{
		if (func_decl.IsInline())
		{
			func->SetForceInline();
		}
		else if (func_decl.IsNoInline())
		{
			func->SetNoInline();
		}
		if (func_decl.IsNoOpt())
		{
			func->SetNoOptimizations();
		}

		BasicBlock* entry_block = builder->AddBlock(func, "entry");
		builder->SetCurrentBlock(entry_block);

		for (auto& param : func_decl.GetParamDecls())
		{
			Value* arg_value = value_map[param.get()];
			Value* arg_alloc = builder->MakeInst<AllocaInst>(arg_value->GetType());

			builder->MakeInst<StoreInst>(arg_value, arg_alloc);
			if (isa<RefType>(param->GetType()))
			{
				Value* arg_ref = builder->MakeInst<LoadInst>(arg_alloc, arg_value->GetType());
				value_map[param.get()] = arg_ref;
			}
			else
			{
				value_map[param.get()] = arg_alloc;
			}
		}
		if (!func->GetReturnType()->IsVoid())
		{
			return_value = builder->MakeInst<AllocaInst>(func->GetReturnType());
		}
		
		exit_block = builder->AddBlock(func, "exit");
		auto const& labels = func_decl.GetLabels();
		for (LabelStmt const* label : labels)
		{
			std::string label_name = std::string(label->GetName());
			BasicBlock* label_block = builder->AddBlock(func, exit_block, label_name);
			label_blocks[label_name] = label_block;
		}

		func_decl.GetBodyStmt()->Accept(*this);

		builder->SetCurrentBlock(exit_block);
		if (!func->GetReturnType()->IsVoid())
		{
			builder->MakeInst<ReturnInst>(Load(func->GetReturnType(), return_value));
		}
		else
		{
			builder->MakeInst<ReturnInst>(context);
		}

		std::vector<BasicBlock*> empty_blocks{};
		for (auto&& block : *func) if (block.Instructions().Empty())
		{
			empty_blocks.push_back(&block);
		}

		for (BasicBlock* empty_block : empty_blocks)
		{
			builder->SetCurrentBlock(empty_block);
			Value* nop = builder->MakeInst<UnaryInst>(Opcode::Neg, context.GetInt64(0));
			nop->SetName("nop");
			if (empty_block_successors.contains(empty_block))
			{
				builder->MakeInst<BranchInst>(context, empty_block_successors[empty_block]);
			}
			else 
			{
				builder->MakeInst<BranchInst>(context, exit_block);
			}
		}

		for (auto&& block : *func)
		{
			if (block.GetTerminator() == nullptr)
			{
				builder->SetCurrentBlock(&block);
				builder->MakeInst<BranchInst>(context, exit_block);
			}
		}

		label_blocks.clear();
		exit_block = nullptr;
		return_value = nullptr;
		value_map[&func_decl] = func;
	}

	void IRVisitor::ConditionalBranch(Value* condition_value, BasicBlock* true_block, BasicBlock* false_block)
	{
		if (condition_value->GetType()->IsPointer())
		{
			if (isa<AllocaInst>(condition_value))
			{
				AllocaInst* alloca_inst = cast<AllocaInst>(condition_value);
				condition_value = builder->MakeInst<LoadInst>(condition_value, alloca_inst->GetAllocatedType());
			}
			else if (isa<GlobalVariable>(condition_value))
			{
				GlobalVariable* global_var_alloc = cast<GlobalVariable>(condition_value);
				condition_value = builder->MakeInst<LoadInst>(condition_value, global_var_alloc->GetValueType());
			}
		}

		if (condition_value->GetType()->IsInteger())
		{
			IRIntType* int_type = cast<IRIntType>(condition_value->GetType());
			if (int_type->GetWidth() == 1)
			{
				builder->MakeInst<BranchInst>(condition_value, true_block, false_block);
			}
			else
			{
				Value* condition = Load(int_type, condition_value);
				Value* boolean_cond = builder->MakeInst<CompareInst>(Opcode::ICmpNE, condition, context.GetInt64(0));
				builder->MakeInst<BranchInst>(boolean_cond, true_block, false_block);
			}
		}
		else if (condition_value->GetType()->IsFloat())
		{
			Value* condition = Load(float_type, condition_value);
			Value* boolean_cond = builder->MakeInst<CompareInst>(Opcode::FCmpONE, condition, context.GetFloat(0.0));
			builder->MakeInst<BranchInst>(boolean_cond, true_block, false_block);
		}
		else OLA_ASSERT(false);
	}

	IRType* IRVisitor::ConvertToIRType(Type const* type)
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
			ArrayType const* array_type = cast<ArrayType>(type);
			if (array_type->GetArraySize() > 0) return IRArrayType::Get(ConvertToIRType(array_type->GetElementType()), array_type->GetArraySize());
			else return GetPointerType(ConvertToIRType(array_type->GetElementType()));
		}
		case TypeKind::Function:
		{
			FuncType const* function_type = cast<FuncType>(type);
			std::span<QualType const> function_params = function_type->GetParams();

			IRType* return_type = ConvertToIRType(function_type->GetReturnType());
			Bool return_type_struct = return_type->IsStruct();

			std::vector<IRType*> param_types; param_types.reserve(function_params.size());
			if (return_type_struct) param_types.push_back(GetPointerType(return_type));

			for (auto const& func_param_type : function_params)
			{
				IRType* param_type = ConvertToIRType(func_param_type);
				OLA_ASSERT_MSG(!param_type->IsStruct(), "Struct pass-by-value not supported in custom backend. Use 'ref' instead.");
				param_types.push_back(param_type);
			}
			return IRFuncType::Get(return_type_struct ? void_type : return_type, param_types);
		}
		case TypeKind::Class:
		{
			ClassType const* class_type = cast<ClassType>(type);
			return ConvertClassDecl(class_type->GetClassDecl());
		}
		case TypeKind::Ref:
		{
			RefType const* ref_type = cast<RefType>(type);
			return GetPointerType(ConvertToIRType(ref_type->GetReferredType()));
		}
		default:
			OLA_UNREACHABLE();
		}
		return nullptr;
	}

	IRType* IRVisitor::ConvertClassDecl(ClassDecl const* class_decl)
	{
		using LLVMStructTypeMap = std::unordered_map<ClassDecl const*, IRStructType*>;
		static LLVMStructTypeMap struct_type_map;

		if (struct_type_map.contains(class_decl)) return struct_type_map[class_decl];

		UniqueFieldDeclPtrList const& fields = class_decl->GetFields();
		std::vector<IRType*> llvm_member_types;
		if (class_decl->IsPolymorphic())
		{
			llvm_member_types.push_back(GetPointerType(GetPointerType(void_type)));
		}
		ClassDecl const* curr_class_decl = class_decl;
		while (ClassDecl const* base_class_decl = curr_class_decl->GetBaseClass())
		{
			for (auto const& field : base_class_decl->GetFields())
			{
				llvm_member_types.push_back(ConvertToIRType(field->GetType()));
			}
			curr_class_decl = base_class_decl;
		}
		for (auto const& field : fields)
		{
			llvm_member_types.push_back(ConvertToIRType(field->GetType()));
		}

		IRStructType* class_type = context.GetStructType(class_decl->GetName(), llvm_member_types);
		struct_type_map[class_decl] = class_type;
		return class_type;
	}

	IRFuncType* IRVisitor::ConvertMethodType(FuncType const* type, IRType* class_type)
	{
		std::span<QualType const> function_params = type->GetParams();

		IRType* return_type = ConvertToIRType(type->GetReturnType());
		Bool return_type_struct = return_type->IsStruct();

		std::vector<IRType*> param_types; param_types.reserve(function_params.size());
		if (return_type_struct)
		{
			param_types.push_back(IRPtrType::Get(return_type));
		}

		param_types.push_back(IRPtrType::Get(class_type));
		for (auto const& func_param_type : function_params)
		{
			IRType* param_type = ConvertToIRType(func_param_type);
			param_types.push_back(param_type);
		}
		return context.GetFunctionType(return_type_struct ? void_type : return_type, param_types);
	}

	IRType* IRVisitor::GetStructType(Type const* class_expr_type)
	{
		if (isa<ClassType>(class_expr_type))
		{
			return ConvertToIRType(class_expr_type);
		}
		else if (isa<RefType>(class_expr_type))
		{
			RefType const* ref_type = cast<RefType>(class_expr_type);
			if (isa<ClassType>(ref_type->GetReferredType()))
			{
				return ConvertToIRType(ref_type->GetReferredType());
			}
			return nullptr;
		}
		else return nullptr;
	}

	IRPtrType* IRVisitor::GetPointerType(IRType* type)
	{
		return IRPtrType::Get(type);
	}

	Value* IRVisitor::Load(Type const* type, Value* ptr)
	{
		IRType* ir_type = nullptr;
		if (RefType const* ref_type = dyn_cast<RefType>(type))
		{
			ir_type = ConvertToIRType(ref_type->GetReferredType());
		}
		else
		{
			ir_type = ConvertToIRType(type);
		}
		return Load(ir_type, ptr);
	}

	Value* IRVisitor::Load(IRType* ir_type, Value* ptr)
	{
		if (ptr->GetType()->IsPointer())
		{
			if (ir_type->IsPointer() && isa<GlobalVariable>(ptr))
			{
				return ptr;
			}
			return builder->MakeInst<LoadInst>(ptr, ir_type); 
		}
		return ptr;
	}

	Value* IRVisitor::Store(Value* value, Value* ptr)
	{
		if (!value->GetType()->IsPointer())
		{
			return builder->MakeInst<StoreInst>(value, ptr);
		}

		Value* load = nullptr;
		if (AllocaInst* AI = dyn_cast<AllocaInst>(value))
		{
			load = Load(AI->GetAllocatedType(), AI);
		}
		else if (GetElementPtrInst* GEPI = dyn_cast<GetElementPtrInst>(value))
		{
			load = Load(GEPI->GetResultElementType(), GEPI);
		}
		else
		{
			load = Load(value->GetType(), value);
		}
		return builder->MakeInst<StoreInst>(load, ptr);
	}

}

