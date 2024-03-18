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
		BasicBlock* current_block = builder->GetCurrentBlock();
		Function* current_function = current_block->GetFunction();
		if (Expr const* return_expr = return_stmt.GetExprStmt()->GetExpr())
		{
			return_expr->Accept(*this);
			Value* return_expr_value = value_map[return_expr];
			OLA_ASSERT(return_expr_value);

			if (current_function->GetReturnType()->IsPointerType()) builder->MakeInst<StoreInst>(return_value, return_expr_value);
			else return_value = return_expr_value;
		}
		builder->MakeInst<BranchInst>(context, exit_block);
		BasicBlock* return_block = builder->AddBlock(current_function, current_block->GetNextNode());
		return_block->SetLabel("return");
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
			incremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? InstructionID::FAdd : InstructionID::Add, operand, one);
			Store(incremented_value, operand_value);
			result = incremented_value;
		}
		break;
		case UnaryExprKind::PreDecrement:
		{
			Value* decremented_value = nullptr;
			decremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? InstructionID::FSub : InstructionID::Sub, operand, one);
			Store(decremented_value, operand_value);
			result = decremented_value;
		}
		break;
		case UnaryExprKind::PostIncrement:
		{
			result = builder->MakeInst<AllocaInst>(operand_value->GetType());
			Store(operand_value, result);
			Value* incremented_value = nullptr;
			incremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? InstructionID::FAdd : InstructionID::Add, operand, one);
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder->MakeInst<AllocaInst>(operand_value->GetType());
			Store(operand_value, result);
			Value* decremented_value = nullptr;
			decremented_value = builder->MakeInst<BinaryInst>(is_float_expr ? InstructionID::FSub : InstructionID::Sub, operand, one);
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
			result = is_float_expr ? builder->MakeInst<UnaryInst>(InstructionID::FNeg, operand) : builder->MakeInst<UnaryInst>(InstructionID::Neg, operand);
		}
		break;
		case UnaryExprKind::BitNot:
		{
			result = builder->MakeInst<UnaryInst>(InstructionID::Not, operand);
		}
		break;
		case UnaryExprKind::LogicalNot:
		{
			result = builder->MakeInst<CompareInst>(is_float_expr ? InstructionID::FCmpUEQ : InstructionID::ICmpEQ, operand, zero);
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
		return ptr;
	}

	Value* IRVisitor::Store(Value* value, Value* ptr)
	{
		return ptr;
	}

}

