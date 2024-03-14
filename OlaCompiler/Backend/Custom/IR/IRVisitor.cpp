#include "IRVisitor.h"
#include "IRBuilder.h"
#include "IRModule.h"
#include "IRContext.h"
#include "IRType.h"
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

	void IRVisitor::Visit(FieldDecl const&, uint32)
	{

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
		
	}

	void IRVisitor::Visit(BinaryExpr const& binary_expr, uint32)
	{
		
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

	}

	void IRVisitor::Visit(CharLiteral const& char_constant, uint32)
	{
		
	}

	void IRVisitor::Visit(StringLiteral const& string_constant, uint32)
	{
		
	}

	void IRVisitor::Visit(BoolLiteral const& bool_constant, uint32)
	{
		
	}

	void IRVisitor::Visit(FloatLiteral const& float_constant, uint32)
	{
		
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

