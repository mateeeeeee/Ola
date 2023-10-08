#include "Sema.h"
#include "Diagnostics.h"
#include "AST.h"
#include "Type.h"
#include "Core/Logger.h"

namespace wave
{

	Sema::Sema() = default;
	Sema::~Sema() = default;

	void Sema::ActOnVariableDecl(VariableDeclAST* var_decl)
	{
		WAVE_ASSERT(var_decl != nullptr);
		ExprAST const* init_expr = var_decl->GetInitExpr();
		QualifiedType const& type = var_decl->GetType();
		bool const has_init = (init_expr != nullptr);
		bool const has_type_specifier = type.HasRawType();

		if (has_init)
		{
			if (has_type_specifier)
			{
				if (!type->IsCompatible(init_expr->GetType()))
				{
					Diag(diag::incompatible_initializer, var_decl->GetLocation());
				}
			}
			else
			{
				QualifiedType var_type(init_expr->GetType());
				if (type.IsConst()) var_type.AddConst();
				var_decl->SetType(var_type);
			}
		}
		else
		{
			if (!has_init)
			{
				Diag(diag::missing_type_specifier_or_init_expr, var_decl->GetLocation());
			}
		}
		
		if (ctx.sym_table.LookUpCurrentScope(var_decl->GetName()))
		{
			Diag(diag::redefinition_of_identifier, var_decl->GetLocation());
		}
		bool result = ctx.sym_table.Insert(Symbol{ std::string(var_decl->GetName()), var_decl->GetType()});
		WAVE_ASSERT(result);
	}

	void Sema::ActOnFunctionDecl(FunctionDeclAST* function_decl)
	{
		if (ctx.sym_table.LookUpCurrentScope(function_decl->GetName()))
		{
			Diag(diag::redefinition_of_identifier, function_decl->GetLocation());
		}
		bool result = ctx.sym_table.Insert(Symbol{ std::string(function_decl->GetName()), function_decl->GetType() });
		WAVE_ASSERT(result);
	}

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
			Diag(diag::incompatible_return_stmt_type, ret_expr ? ret_expr->GetLocation() : SourceLocation{});
		}
	}

	void Sema::ActOnExpr(ExprAST* expr)
	{
		switch (expr->GetExprKind())
		{
		case ExprKind::Unary:
		{
			UnaryExprAST* unary_expr = ast_cast<UnaryExprAST>(expr);
			return ActOnUnaryExpr(unary_expr);
		}
		case ExprKind::Binary:
		{
			BinaryExprAST* binary_expr = ast_cast<BinaryExprAST>(expr);
			return ActOnBinaryExpr(binary_expr);
		}
		case ExprKind::Cast:
		{
			CastExprAST* cast_expr = ast_cast<CastExprAST>(expr);
			return ActOnCastExpr(cast_expr);
		}
		}
}

	void Sema::Diag(diag::DiagCode code, SourceLocation const& loc)
	{
		diag::Diag(code, loc);
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

		if (IsArrayType(cast_type) || IsArrayType(operand_type)) Diag(diag::invalid_cast, cast_expr->GetLocation());
		if(IsVoidType(cast_type)) Diag(diag::invalid_cast, cast_expr->GetLocation());
		if(cast_type->IsCompatible(operand_type))  Diag(diag::invalid_cast, cast_expr->GetLocation());

		cast_expr->SetType(operand_type);
	}

	void Sema::ActOnIdentifier(IdentifierAST* identifier)
	{
		if (Symbol* symbol = ctx.sym_table.LookUp(identifier->GetName()))
		{
			identifier->SetType(symbol->type);
		}
		else 
		{
			Diag(diag::undeclared_identifier, identifier->GetLocation());
		}
	}

}

