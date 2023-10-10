#include "Sema.h"
#include "Diagnostics.h"
#include "Type.h"

namespace wave
{

	Sema::Sema(Diagnostics& diagnostics) : diagnostics(diagnostics) {}
	Sema::~Sema() = default;

	UniqueVariableDeclPtr Sema::ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& init_expr)
	{
		bool const has_init = (init_expr != nullptr);
		bool const has_type_specifier = type.HasRawType();

		if (has_init && has_type_specifier)
		{
			//#todo
			//if (!type->IsCompatible(init_expr->GetType()))
			//{
			//	diagnostics.Report(loc, incompatible_initializer);
			//}
		}
		else if(!has_init && !has_type_specifier)
		{
			diagnostics.Report(loc, missing_type_specifier_or_init_expr);
		}

		if (ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier);
		}

		std::unique_ptr<VariableDecl> var_decl = MakeUnique<VariableDecl>(name, loc);
		var_decl->SetInitExpr(std::move(init_expr));
		if (has_init && !has_type_specifier)
		{
			QualifiedType var_type(var_decl->GetInitExpr()->GetType());
			if (type.IsConst()) var_type.AddConst();
			var_decl->SetType(var_type);
		}
		else
		{
			var_decl->SetType(type);
		}
		bool result = ctx.decl_scope_stack.Insert(var_decl.get());
		WAVE_ASSERT(result);
		return var_decl;
	}

	UniqueFunctionDeclPtr Sema::ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueVariableDeclPtrList&& param_decls)
	{
		if (ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier);
		}
		UniqueFunctionDeclPtr function_decl = MakeUnique<FunctionDecl>(name, loc);
		function_decl->SetType(type);
		function_decl->SetParamDeclarations(std::move(param_decls));
		bool result = ctx.decl_scope_stack.Insert(function_decl.get());
		WAVE_ASSERT(result);
		return function_decl;
	}

	void Sema::ActOnFunctionDecl(UniqueFunctionDeclPtr& function_decl, UniqueCompoundStmtPtr&& definition)
	{
		function_decl->SetDefinition(std::move(definition));
	}

	UniqueIdentifierExprPtr Sema::ActOnIdentifier(std::string_view name, SourceLocation const& loc)
	{
		if (Decl* decl = ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(decl, loc);
			return decl_ref;
		}
		else
		{
			diagnostics.Report(loc, undeclared_identifier, name);
			return nullptr;
		}
	}

	/*

	void Sema::ActOnReturnStmt(ReturnStmtAST* return_stmt)
	{
		WAVE_ASSERT(ctx.current_func);
		ctx.return_stmt_encountered = true;
		FunctionType const& func_type = type_cast<FunctionType>(*ctx.current_func);
		QualifiedType const& return_type = func_type.GetReturnType();
		
		ExprAST const* ret_expr = return_stmt->GetExprStmt()->GetExpr();
		QualifiedType const& ret_expr_type = ret_expr ? ret_expr->GetType() : builtin_types::Void;
		if (!ret_expr_type->IsCompatible(return_type))
		{
			diagnostics.Report(ret_expr ? ret_expr->GetLocation() : SourceLocation{}, incompatible_return_stmt_type);
		}
	}

	void Sema::ActOnUnaryExpr(UnaryExprAST* unary_expr)
	{
		QualifiedType const& operand_type = unary_expr->GetOperand()->GetType();
		unary_expr->SetType(operand_type);
	}

	void Sema::ActOnBinaryExpr(BinaryExprAST* binary_expr)
	{
		QualifiedType const& lhs_type = binary_expr->GetLHS()->GetType();
		QualifiedType const& rhs_type = binary_expr->GetRHS()->GetType();

		if (lhs_type->GetKind() == rhs_type->GetKind())
		{
			binary_expr->SetType(lhs_type);
			return;
		}
	}

	void Sema::ActOnCastExpr(CastExprAST* cast_expr)
	{
		QualifiedType const& cast_type = cast_expr->GetType();
		QualifiedType const& operand_type = cast_expr->GetOperand()->GetType();

		if (IsArrayType(cast_type) || IsArrayType(operand_type)) diagnostics.Report(cast_expr->GetLocation(), invalid_cast);
		if(IsVoidType(cast_type)) diagnostics.Report(cast_expr->GetLocation(), invalid_cast);
		if(cast_type->IsCompatible(operand_type))  diagnostics.Report(cast_expr->GetLocation(), invalid_cast);

		cast_expr->SetType(operand_type);
	}
	*/
}

