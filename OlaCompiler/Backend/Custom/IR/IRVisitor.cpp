#include "IRVisitor.h"
#include "IRBuilder.h"
#include "IRModule.h"
#include "IRContext.h"
#include "IRType.h"
#include "IR.h"
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

	void IRVisitor::Visit(ASTNode const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(TranslationUnit const& translation_unit, uint32)
	{
		for (auto&& decl : translation_unit.GetDecls()) decl->Accept(*this);
	}

	void IRVisitor::Visit(Decl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(FunctionDecl const& function_decl, uint32)
	{
		FuncType const* type = function_decl.GetFuncType();
		IRFuncType* function_type = cast<IRFuncType>(ConvertToIRType(type));
		Linkage linkage = function_decl.IsPublic() || function_decl.IsExtern() ? Linkage::External : Linkage::Internal;
		Function* ir_function = Create<Function>(function_type, module, linkage, function_decl.GetMangledName());

		Argument* param_arg = ir_function->GetArg(0);
		if (isa<ClassType>(type->GetReturnType()))
		{
			Value* sret_value = param_arg;
			++param_arg;
			return_value = sret_value;
		}
		for (auto& param : function_decl.GetParamDecls())
		{
			Value* llvm_param = param_arg;
			llvm_param->SetName(param->GetName());
			value_map[param.get()] = llvm_param;
			++param_arg;
		}
		if (!function_decl.HasDefinition()) return;

		VisitFunctionDeclCommon(function_decl, ir_function);
	}

	void IRVisitor::Visit(MethodDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(ParamVarDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(FieldDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(VarDecl const& var_decl, uint32)
	{
		Type const* var_type = var_decl.GetType().GetTypePtr();
		bool const is_const = var_decl.GetType().IsConst();
		IRType* ir_type = ConvertToIRType(var_type);
		bool const is_array = isa<ArrayType>(var_type);
		bool const is_class = isa<ClassType>(var_type);
		bool const is_ref = isa<RefType>(var_type);

		if (var_decl.IsGlobal())
		{
			if (var_decl.IsExtern())
			{
				GlobalVariable* global_var = Create<GlobalVariable>(ir_type, module, Linkage::External, nullptr, is_const, var_decl.GetName());
				value_map[&var_decl] = global_var;
			}
			else if (Expr const* init_expr = var_decl.GetInitExpr())
			{
				if (is_array)
				{
					ArrayType const* array_type = cast<ArrayType>(var_type);
					IRType* ir_element_type = ConvertToIRType(array_type->GetBaseType());

					if (InitializerListExpr const* init_list_expr = dyn_cast<InitializerListExpr>(init_expr))
					{
						OLA_ASSERT(init_list_expr->IsConstexpr());
						init_list_expr->Accept(*this);

						Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
						GlobalVariable* global_array = Create<GlobalVariable>(ir_type, module, linkage, cast<Constant>(value_map[init_list_expr]), is_const, var_decl.GetName());
						value_map[&var_decl] = global_array;
					}
					else if (StringLiteral const* string = dyn_cast<StringLiteral>(init_expr))
					{
						ConstantString* constant = context.GetString(string->GetString());
						Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
						GlobalVariable* global_string = Create<GlobalVariable>(ir_type, module, linkage, constant, is_const, var_decl.GetName());
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
					GlobalVariable* global_var = Create<GlobalVariable>(ir_type, module, linkage, constant_init_value, is_const, var_decl.GetName());
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
				for (uint64 i = 0; i < fields.size(); ++i)
				{
					initializers.push_back(cast<Constant>(value_map[fields[i].get()]));
				}

				OLA_ASSERT_MSG(false, "todo");
				//IRStructType* llvm_struct_type = cast<IRStructType>(ir_type);
				//GlobalVariable* global_var = new llvm::GlobalVariable(module, ir_type, false, llvm::GlobalValue::ExternalLinkage,
				//	ConstantStruct::get(llvm_struct_type, initializers), var_decl.GetName());
				//value_map[&var_decl] = global_var;
			}
			else if (is_ref)
			{
				OLA_ASSERT_MSG(false, "todo");
			}
			else
			{
				Constant* constant_init_value = Constant::GetNullValue(ir_type);
				Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;

				GlobalVariable* global_var = Create<GlobalVariable>(ir_type, module, linkage, constant_init_value, is_const, var_decl.GetName());
				value_map[&var_decl] = global_var;
			}
		}
		else
		{
			if (Expr const* init_expr = var_decl.GetInitExpr(); init_expr && !isa<ConstructorExpr>(init_expr))
			{
				init_expr->Accept(*this);
				AllocaInst* alloc = builder->CreateAlloca(ir_type, nullptr);
				Value* init_value = value_map[init_expr];
				Store(init_value, alloc);
				value_map[&var_decl] = alloc;
			}
			else
			{
				AllocaInst* alloc = builder->CreateAlloca(ir_type, nullptr);
				value_map[&var_decl] = alloc;
			}
		}
	}

	void IRVisitor::Visit(TagDecl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(EnumDecl const& enum_decl, uint32)
	{
		for (auto const& enum_member : enum_decl.GetEnumMembers()) enum_member->Accept(*this);
	}

	void IRVisitor::Visit(EnumMemberDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(AliasDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(ClassDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(Stmt const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(CompoundStmt const& compound_stmt, uint32)
	{
		for (auto const& stmt : compound_stmt.GetStmts()) stmt->Accept(*this);
	}

	void IRVisitor::Visit(DeclStmt const& decl_stmt, uint32)
	{
		for (auto const& decl : decl_stmt.GetDecls())  decl->Accept(*this);
	}

	void IRVisitor::Visit(ExprStmt const& expr_stmt, uint32)
	{
		if (expr_stmt.GetExpr()) expr_stmt.GetExpr()->Accept(*this);
	}

	void IRVisitor::Visit(NullStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ReturnStmt const& return_stmt, uint32)
	{
		BasicBlock* current_block = builder->GetInsertBlock();
		Function* current_function = current_block->GetParent();
		if (Expr const* return_expr = return_stmt.GetExprStmt()->GetExpr())
		{
			return_expr->Accept(*this);
			Value* return_expr_value = value_map[return_expr];
			OLA_ASSERT(return_expr_value);

			if (current_function->GetReturnType()->IsPointerType())
			{
				builder->CreateStore(return_expr_value, return_value);
			}
			else
			{
				return_value = return_expr_value;
			}
		}
		builder->CreateBranch(exit_block);
		BasicBlock* return_block = Create<BasicBlock>(context, "return", current_function, current_block->GetNext());
		builder->SetInsertPoint(return_block);
	}

	void IRVisitor::Visit(IfStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(BreakStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ContinueStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ForStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(WhileStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(DoWhileStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(CaseStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(SwitchStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(GotoStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(LabelStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(Expr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(UnaryExpr const& unary_expr, uint32)
	{
		Expr const* operand_expr = unary_expr.GetOperand();
		operand_expr->Accept(*this);
		Value* operand_value = value_map[operand_expr];
		OLA_ASSERT(operand_value);
		Value* operand = Load(operand_expr->GetType(), operand_value);

		bool const is_float_expr = isa<FloatType>(operand_expr->GetType());
		Value* result = nullptr;
		switch (unary_expr.GetUnaryKind())
		{
		case UnaryExprKind::PreIncrement:
		{
			Value* incremented_value = is_float_expr ? builder->CreateBinaryOp(Binary_Add, operand, Create<ConstantFloat>(context, 1.0)) :
								builder->CreateBinaryOp(Binary_Add, operand, Create<ConstantInt>(operand->GetType(), 1));
			Store(incremented_value, operand_value);
			result = incremented_value;
		}
		break;
		case UnaryExprKind::PreDecrement:
		{
			Value* decremented_value = is_float_expr ? builder->CreateBinaryOp(Binary_Sub, operand, Create<ConstantFloat>(context, 1.0)) :
				builder->CreateBinaryOp(Binary_Sub, operand, Create<ConstantInt>(operand->GetType(), 1));
			Store(decremented_value, operand_value);
			result = decremented_value;
		}
		break;
		case UnaryExprKind::PostIncrement:
		{
			result = builder->CreateAlloca(operand_value->GetType(), nullptr);
			Store(operand_value, result);
			Value* incremented_value = is_float_expr ? builder->CreateBinaryOp(Binary_Add, operand, Create<ConstantFloat>(context, 1.0)) :
				builder->CreateBinaryOp(Binary_Sub, operand, Create<ConstantInt>(operand->GetType(), 1));
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder->CreateAlloca(operand_value->GetType(), nullptr);
			Store(operand_value, result);
			Value* incremented_value = is_float_expr ? builder->CreateBinaryOp(Binary_Sub, operand, Create<ConstantFloat>(context, 1.0)) :
				builder->CreateBinaryOp(Binary_Sub, operand, Create<ConstantInt>(operand->GetType(), 1));
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::Plus:
		{
			result = operand_value;
		}
		break;
		case UnaryExprKind::Minus:
		{
			builder->CreateUnaryOp(UnaryOpcode::Unary_Neg, operand);
		}
		break;
		case UnaryExprKind::BitNot:
		{
			builder->CreateUnaryOp(UnaryOpcode::Unary_Not, operand);
		}
		break;
		case UnaryExprKind::LogicalNot:
		{
			context.GetInt64(1);
			result = is_float_expr ? builder->CreateCmp(FCMP_EQ, operand, Create<ConstantFloat>(context, 0.0)) :
				     builder->CreateCmp(ICMP_EQ, operand, Create<ConstantInt>(operand->GetType(), 1));
		}
		break;
		default:
			OLA_ASSERT(false);
		}
		OLA_ASSERT(result);
		value_map[&unary_expr] = result;
	}

	void IRVisitor::Visit(BinaryExpr const& binary_expr, uint32)
	{
		Expr const* lhs_expr = binary_expr.GetLHS();
		lhs_expr->Accept(*this);
		Value* lhs_value = value_map[lhs_expr];
		Expr const* rhs_expr = binary_expr.GetRHS();
		rhs_expr->Accept(*this);
		Value* rhs_value = value_map[rhs_expr];
		OLA_ASSERT(lhs_value && rhs_value);

		Value* lhs = Load(lhs_expr->GetType(), lhs_value);
		Value* rhs = Load(rhs_expr->GetType(), rhs_value);
		bool const is_float_expr = isa<FloatType>(lhs_expr->GetType()) || isa<FloatType>(rhs_expr->GetType());

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
			BinaryOpcode opcode = is_float_expr ? Binary_FAdd : Binary_Add;
			result = builder->CreateBinaryOp(opcode, lhs, rhs);
		}
		break;
		case BinaryExprKind::Subtract:
		{
			BinaryOpcode opcode = is_float_expr ? Binary_FSub : Binary_Sub;
			result = builder->CreateBinaryOp(opcode, lhs, rhs);
		}
		break;
		case BinaryExprKind::Multiply:
		{
			BinaryOpcode opcode = is_float_expr ? Binary_FMul : Binary_Mul;
			result = builder->CreateBinaryOp(opcode, lhs, rhs);
		}
		break;
		case BinaryExprKind::Divide:
		{
			BinaryOpcode opcode = is_float_expr ? Binary_FDiv : Binary_Div;
			result = builder->CreateBinaryOp(opcode, lhs, rhs);
		}
		break;
		case BinaryExprKind::Modulo:
		{
			OLA_ASSERT(!is_float_expr);
			result = builder->CreateBinaryOp(Binary_Rem, lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftLeft:
		{
			result = builder->CreateBinaryOp(Binary_Shl, lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftRight:
		{
			result = builder->CreateBinaryOp(Binary_Shr, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitAnd:
		{
			result = builder->CreateBinaryOp(Binary_And, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitOr:
		{
			result = builder->CreateBinaryOp(Binary_Or, lhs, rhs);
		}
		break;
		case BinaryExprKind::BitXor:
		{
			result = builder->CreateBinaryOp(Binary_Xor, lhs, rhs);

		}
		break;
		case BinaryExprKind::LogicalAnd:
		{
			Value* tmp = builder->CreateBinaryOp(Binary_And, lhs, rhs);
			result = builder->CreateCmp(ICMP_NE, tmp, Create<ConstantInt>(tmp->GetType(), 1));
		}
		break;
		case BinaryExprKind::LogicalOr:
		{
			Value* tmp = builder->CreateBinaryOp(Binary_Or, lhs, rhs);
			result = builder->CreateCmp(ICMP_NE, tmp, Create<ConstantInt>(tmp->GetType(), 0));
		}
		break;
		case BinaryExprKind::Equal:
		{
			CmpPredicate pred = is_float_expr ? FCMP_EQ : ICMP_EQ;
			result = builder->CreateCmp(pred, lhs, rhs);
		}
		break;
		case BinaryExprKind::NotEqual:
		{
			CmpPredicate pred = is_float_expr ? FCMP_NE : ICMP_NE;
			result = builder->CreateCmp(pred, lhs, rhs);
		}
		break;
		case BinaryExprKind::Less:
		{
			CmpPredicate pred = is_float_expr ? FCMP_LT : ICMP_SLT;
			result = builder->CreateCmp(pred, lhs, rhs);
		}
		break;
		case BinaryExprKind::Greater:
		{
			CmpPredicate pred = is_float_expr ? FCMP_GT : ICMP_SGT;
			result = builder->CreateCmp(pred, lhs, rhs);
		}
		break;
		case BinaryExprKind::LessEqual:
		{
			CmpPredicate pred = is_float_expr ? FCMP_LE : ICMP_SLE;
			result = builder->CreateCmp(pred, lhs, rhs);
		}
		break;
		case BinaryExprKind::GreaterEqual:
		{
			CmpPredicate pred = is_float_expr ? FCMP_GE : ICMP_SGE;
			result = builder->CreateCmp(pred, lhs, rhs);
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

	void IRVisitor::Visit(TernaryExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(IdentifierExpr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(DeclRefExpr const& decl_ref, uint32)
	{
		Value* value = value_map[decl_ref.GetDecl()];
		OLA_ASSERT(value);
		value_map[&decl_ref] = value;
	}

	void IRVisitor::Visit(IntLiteral const& int_constant, uint32)
	{
		ConstantInt* constant = context.GetInt64(int_constant.GetValue()); 
		value_map[&int_constant] = constant;
	}

	void IRVisitor::Visit(CharLiteral const& char_constant, uint32)
	{
		ConstantInt* constant = context.GetInt8(char_constant.GetChar());
		value_map[&char_constant] = constant;
	}

	void IRVisitor::Visit(StringLiteral const& string_constant, uint32)
	{
		Constant* constant = context.GetString(string_constant.GetString()); 

		static uint32 counter = 0;
		std::string name = "__StringLiteral"; name += std::to_string(counter++);

		Linkage linkage = Linkage::Internal;
		GlobalVariable* global_string = Create<GlobalVariable>(ConvertToIRType(string_constant.GetType()), module, linkage, constant, true, name);
		value_map[&string_constant] = global_string;
	}

	void IRVisitor::Visit(BoolLiteral const& bool_constant, uint32)
	{
		ConstantInt* constant = Create<ConstantInt>(bool_type, bool_constant.GetValue());
		value_map[&bool_constant] = constant;
	}

	void IRVisitor::Visit(FloatLiteral const& float_constant, uint32)
	{
		Constant* constant = Create<ConstantFloat>(float_type, float_constant.GetValue());
		value_map[&float_constant] = constant;
	}

	void IRVisitor::Visit(ImplicitCastExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(CallExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(InitializerListExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(ArrayAccessExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(MemberExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(MethodCallExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(ThisExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(SuperExpr const&, uint32)
	{

	}

	void IRVisitor::VisitFunctionDeclCommon(FunctionDecl const& func_decl, Function* func)
	{
		if (func_decl.IsInline()) func->SetFuncAttribute(Function::Attribute_ForceInline);
		else if (func_decl.IsNoInline()) func->SetFuncAttribute(Function::Attribute_NoInline);

		BasicBlock* entry_block = Create<BasicBlock>(context, "entry", func);
		builder->SetInsertPoint(entry_block);

		for (auto& param : func_decl.GetParamDecls())
		{
			Value* arg_value = value_map[param.get()];
			AllocaInst* arg_alloc = builder->CreateAlloca(arg_value->GetType(), nullptr);
			builder->CreateStore(arg_value, arg_alloc);
			if (isa<RefType>(param->GetType()))
			{
				Value* arg_ref = builder->CreateLoad(arg_value->GetType(), arg_alloc);
				value_map[param.get()] = arg_ref;
			}
			else
			{
				value_map[param.get()] = arg_alloc;
			}
		}

		if (!func->GetReturnType()->IsVoidType()) return_value = builder->CreateAlloca(func->GetReturnType(), nullptr);
		exit_block = Create<BasicBlock>(context, "exit", func);

		auto const& labels = func_decl.GetLabels();
		for (LabelStmt const* label : labels)
		{
			std::string block_name = "label."; block_name += label->GetName();
			BasicBlock* label_block = Create<BasicBlock>(context, block_name, func, exit_block);
			label_blocks[block_name] = label_block;
		}

		func_decl.GetBodyStmt()->Accept(*this);

		builder->SetInsertPoint(exit_block);
		if (!func->GetReturnType()->IsVoidType())
		{
			builder->CreateRet(return_value);
		}
		else builder->CreateRetVoid();

		std::vector<BasicBlock*> unreachable_blocks{};
		for (auto&& block : *func) if (block.HasNPredecessors(0) && &block != entry_block) unreachable_blocks.push_back(&block);

		std::vector<BasicBlock*> empty_blocks{};
		for (auto&& block : *func) if (block.Empty()) empty_blocks.push_back(&block);

		for (BasicBlock* empty_block : empty_blocks)
		{
			builder->SetInsertPoint(empty_block);
			builder->CreateAlloca(IRIntType::Get(context, 1), nullptr);
			if (empty_block_successors.contains(empty_block))
				builder->CreateBranch(empty_block_successors[empty_block]);
			else builder->CreateBranch(exit_block);
		}

		for (auto&& block : *func)
		{
			if (block.GetTerminator() == nullptr)
			{
				builder->SetInsertPoint(&block);
				builder->CreateBranch(exit_block);
			}
		}

		label_blocks.clear();

		exit_block = nullptr;
		return_value = nullptr;

		value_map[&func_decl] = func;
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
			if (array_type->GetArraySize() > 0) return IRArrayType::Get(ConvertToIRType(array_type->GetBaseType()), array_type->GetArraySize());
			else return GetPointerType(ConvertToIRType(array_type->GetBaseType()));
		}
		case TypeKind::Function:
		{
			FuncType const* function_type = cast<FuncType>(type);
			std::span<QualType const> function_params = function_type->GetParams();

			IRType* return_type = ConvertToIRType(function_type->GetReturnType());
			bool return_type_struct = return_type->IsStructType();

			std::vector<IRType*> param_types; param_types.reserve(function_params.size());
			if (return_type_struct) param_types.push_back(GetPointerType(return_type));

			for (auto const& func_param_type : function_params)
			{
				IRType* param_type = ConvertToIRType(func_param_type);
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

	IRType* IRVisitor::ConvertClassDecl(ClassDecl const*)
	{
		return nullptr;
	}

	IRFuncType* IRVisitor::ConvertMethodType(FuncType const*, IRType*)
	{
		return nullptr;
	}

	IRType* IRVisitor::GetStructType(Type const*)
	{
		return nullptr;
	}

	IRPtrType* IRVisitor::GetPointerType(IRType* type)
	{
		return IRPtrType::Get(context, type);
	}

	Value* IRVisitor::Load(Type const* type, Value* ptr)
	{
		IRType* ir_type = nullptr;
		if (RefType const* ref_type = dyn_cast<RefType>(type))
			ir_type = ConvertToIRType(ref_type->GetReferredType());
		else ir_type = ConvertToIRType(type);
		return Load(ir_type, ptr);
	}

	Value* IRVisitor::Load(IRType* ir_type, Value* ptr)
	{
		if (ptr->GetType()->IsPointerType())
		{
			if (ir_type->IsPointerType() && isa<GlobalVariable>(ptr))
			{
				return ptr;
			}
			return builder->CreateLoad(ir_type, ptr);
		}
		return ptr;
	}

	Value* IRVisitor::Store(Value* value, Value* ptr)
	{
		if (!value->GetType()->IsPointerType()) return builder->CreateStore(value, ptr);
		Value* load = Load(value->GetType(), value);
		return builder->CreateStore(load, ptr);
	}

}

