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
		Function* ir_function = new Function(function_decl.GetMangledName(), function_type, linkage);
		module.AddGlobal(ir_function);

		uint32 arg_index = 0;
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

		if (!function_decl.HasDefinition()) return;

		VisitFunctionDeclCommon(function_decl, ir_function);
	}

	void IRVisitor::Visit(MethodDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(ParamVarDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(FieldDecl const& field_decl, uint32)
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
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, Linkage::External, nullptr);
				if(is_const) global_var->SetReadOnly();
				module.AddGlobal(global_var);
				value_map[&var_decl] = global_var;
			}
			else if (Expr const* init_expr = var_decl.GetInitExpr())
			{
				if (is_array)
				{
					OLA_ASSERT(false);
				}
				else
				{
					OLA_ASSERT(init_expr->IsConstexpr());
					init_expr->Accept(*this);
					Value* init_value = value_map[init_expr];
					Constant* constant_init_value = dyn_cast<Constant>(init_value);
					OLA_ASSERT(constant_init_value);

					Linkage linkage = var_decl.IsPublic() || var_decl.IsExtern() ? Linkage::External : Linkage::Internal;
					GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, Linkage::External, nullptr);
					if (is_const) global_var->SetReadOnly();
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
				for (uint64 i = 0; i < fields.size(); ++i)
				{
					initializers.push_back(cast<Constant>(value_map[fields[i].get()]));
				}

				IRStructType* llvm_struct_type = cast<IRStructType>(ir_type);
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, Linkage::External, nullptr); // ConstantStruct::get(llvm_struct_type, initializers));
				if (is_const) global_var->SetReadOnly();
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
				GlobalVariable* global_var = new GlobalVariable(var_decl.GetName(), ir_type, Linkage::External, nullptr);
				if (is_const) global_var->SetReadOnly();
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

				}
				else if (is_class)
				{
					
				}
				else if (is_ref)
				{
					
				}
				else
				{
					AllocaInst* alloc = builder->MakeInst<AllocaInst>(ir_type);
					Value* init_value = value_map[init_expr];
					Store(init_value, alloc);
					value_map[&var_decl] = alloc;
				}
			}
			else
			{
				if (is_class)
				{
					
				}
				else
				{
					AllocaInst* alloc = builder->MakeInst<AllocaInst>(ir_type);
					value_map[&var_decl] = alloc;
				}
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

	void IRVisitor::Visit(EnumMemberDecl const& enum_member_decl, uint32)
	{
		ConstantInt* constant = context.GetInt64(enum_member_decl.GetValue());
		value_map[&enum_member_decl] = constant;
	}

	void IRVisitor::Visit(AliasDecl const&, uint32)
	{
	}

	void IRVisitor::Visit(ClassDecl const& class_decl, uint32)
	{
		for (auto& field : class_decl.GetFields()) field->Accept(*this);
		for (auto& method : class_decl.GetMethods()) method->Accept(*this);

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
				else vtable_function_ptrs.push_back(Constant::GetNullValue(GetPointerType(void_type)));
			}

			std::string vtable_name = "VTable_";
			vtable_name += class_decl.GetName();
			GlobalVariable* vtable_var = new GlobalVariable(vtable_name, vtable_type, Linkage::Internal, nullptr); //todo

			vtable_var->SetReadOnly();
			module.AddGlobal(vtable_var);

			vtable_map[&class_decl] = vtable_var;
		}
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
		BasicBlock* return_block = builder->AddBlock(current_function, current_block->GetNextNode());
		return_block->SetName("return");
		builder->SetCurrentBlock(return_block);
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

	void IRVisitor::Visit(GotoStmt const& goto_stmt, uint32)
	{
		std::string label_name = "label."; label_name += goto_stmt.GetLabelName();
		builder->MakeInst<BranchInst>(context, label_blocks[label_name]);

		BasicBlock* goto_block = builder->AddBlock(exit_block);
		goto_block->SetName("goto");
		builder->SetCurrentBlock(goto_block);
	}

	void IRVisitor::Visit(LabelStmt const& label_stmt, uint32)
	{
		std::string block_name = "label."; block_name += label_stmt.GetName();
		BasicBlock* label_block = label_blocks[block_name];
		builder->MakeInst<BranchInst>(context, label_block);
		builder->SetCurrentBlock(label_block);
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
			Store(operand_value, result);
			Value* incremented_value = nullptr;
			incremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FAdd : Opcode::Add, operand, one);
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder->MakeInst<AllocaInst>(operand_value->GetType());
			Store(operand_value, result);
			Value* decremented_value = nullptr;
			decremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? Opcode::FSub : Opcode::Sub, operand, one);
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
			Opcode id = is_float_expr ? Opcode::FMul : Opcode::Mul;
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

	void IRVisitor::Visit(TernaryExpr const& ternary_expr, uint32)
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
		context.GetString(string_constant.GetString());

		Constant* constant = context.GetString(string_constant.GetString());

		static uint32 counter = 0;
		std::string name = "__StringLiteral"; name += std::to_string(counter++);

		Linkage linkage = Linkage::Internal;
		GlobalVariable* global_string = new GlobalVariable(name, ConvertToIRType(string_constant.GetType()), linkage, constant);
		value_map[&string_constant] = global_string;
		module.AddGlobal(global_string);
	}

	void IRVisitor::Visit(BoolLiteral const& bool_constant, uint32)
	{
		ConstantInt* constant = context.GetInt8(bool_constant.GetValue()); 
		value_map[&bool_constant] = constant;
	}

	void IRVisitor::Visit(FloatLiteral const& float_constant, uint32)
	{
		ConstantFloat* constant = context.GetFloat(float_constant.GetValue());
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

	void IRVisitor::Visit(ThisExpr const& this_expr, uint32)
	{
		value_map[&this_expr] = this_value;
	}

	void IRVisitor::Visit(SuperExpr const& super_expr, uint32)
	{
		value_map[&super_expr] = this_value;
	}

	void IRVisitor::VisitFunctionDeclCommon(FunctionDecl const& func_decl, Function* func)
	{
		if (func_decl.IsInline()) func->SetForceInline();
		else if (func_decl.IsNoInline()) func->SetNoInline();

		BasicBlock* entry_block = builder->AddBlock(func); 
		entry_block->SetName("entry");
		builder->SetCurrentBlock(entry_block);

		for (auto& param : func_decl.GetParamDecls())
		{
			Value* arg_value = value_map[param.get()];
			AllocaInst* arg_alloc = builder->MakeInst<AllocaInst>(arg_value->GetType());

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
		if (!func->GetReturnType()->IsVoidType()) return_value = builder->MakeInst<AllocaInst>(func->GetReturnType());
		
		exit_block = builder->AddBlock(func);
		exit_block->SetName("exit");

		auto const& labels = func_decl.GetLabels();
		for (LabelStmt const* label : labels)
		{
			BasicBlock* label_block = builder->AddBlock(func, exit_block); 
			label_blocks[std::string(label_block->GetName())] = label_block;
		}

		func_decl.GetBodyStmt()->Accept(*this);

		builder->SetCurrentBlock(exit_block);

		if (!func->GetReturnType()->IsVoidType()) builder->MakeInst<ReturnInst>(Load(func->GetReturnType(), return_value));
		else builder->MakeInst<ReturnInst>(context);

		std::vector<BasicBlock*> empty_blocks{};
		for (auto&& block : *func) if (block.Instructions().Empty()) empty_blocks.push_back(&block);

		for (BasicBlock* empty_block : empty_blocks)
		{
			builder->SetCurrentBlock(empty_block);
			UnaryInst* nop = builder->MakeInst<UnaryInst>(Opcode::Neg, context.GetInt64(0));
			nop->SetName("nop");
			if (empty_block_successors.contains(empty_block))
				 builder->MakeInst<BranchInst>(context, empty_block_successors[empty_block]);
			else builder->MakeInst<BranchInst>(context, exit_block);
		}

		for (auto&& block : *func)
		{
			if(block.Instructions().Empty())
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

	IRType* IRVisitor::ConvertClassDecl(ClassDecl const* class_decl)
	{
		using LLVMStructTypeMap = std::unordered_map<ClassDecl const*, IRStructType*, VoidPointerHash>;
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
			for (auto const& field : base_class_decl->GetFields()) llvm_member_types.push_back(ConvertToIRType(field->GetType()));
			curr_class_decl = base_class_decl;
		}
		for (auto const& field : fields) llvm_member_types.push_back(ConvertToIRType(field->GetType()));

		IRStructType* class_type = context.GetStructType(class_decl->GetName(), llvm_member_types);
		struct_type_map[class_decl] = class_type;
		return class_type;
	}

	IRFuncType* IRVisitor::ConvertMethodType(FuncType const* type, IRType* class_type)
	{
		std::span<QualType const> function_params = type->GetParams();

		IRType* return_type = ConvertToIRType(type->GetReturnType());
		bool return_type_struct = return_type->IsStructType();

		std::vector<IRType*> param_types; param_types.reserve(function_params.size());
		if (return_type_struct) param_types.push_back(IRPtrType::Get(return_type));

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
			else return nullptr;
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
			return builder->MakeInst<LoadInst>(ptr, ir_type); 
		}
		return ptr;
	}

	Value* IRVisitor::Store(Value* value, Value* ptr)
	{
		if (!value->GetType()->IsPointerType()) return builder->MakeInst<StoreInst>(value, ptr);
		Value* load = nullptr;
		if (AllocaInst* AI = dyn_cast<AllocaInst>(value))
		{
			load = Load(AI->GetAllocatedType(), AI);
		}
		else
		{
			load = Load(value->GetType(), value);
		}
		return builder->MakeInst<StoreInst>(load, ptr);
	}

}

