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

		if (ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}

		if (has_init && has_type_specifier)
		{
			if (!type->IsCompatible(init_expr->GetType()))
			{
				diagnostics.Report(loc, incompatible_initializer);
			}
		}
		else if(!has_init && !has_type_specifier)
		{
			diagnostics.Report(loc, missing_type_specifier_or_init_expr);
		}

		if (ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
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

	UniqueFunctionDeclPtr Sema::ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt)
	{
		if (ctx.decl_scope_stack.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}

		if (name == "main")
		{
			FunctionType const* func_type = type->TryAs<FunctionType>();
			WAVE_ASSERT(func_type);
			if (func_type->GetReturnType()->IsNot(TypeKind::Int) || !func_type->GetParameters().empty())
			{
				diagnostics.Report(loc, invalid_main_function_declaration);
			}
		}
		UniqueFunctionDeclPtr function_decl = MakeUnique<FunctionDecl>(name, loc);
		function_decl->SetType(type);
		function_decl->SetParamDecls(std::move(param_decls));
		if(body_stmt) function_decl->SetBodyStmt(std::move(body_stmt));

		bool result = ctx.decl_scope_stack.Insert(function_decl.get());
		WAVE_ASSERT(result);
		return function_decl;
	}

	UniqueCompoundStmtPtr Sema::ActOnCompoundStmt(UniqueStmtPtrList&& stmts)
	{
		return MakeUnique<CompoundStmt>(std::move(stmts));
	}

	UniqueExprStmtPtr Sema::ActOnExprStmt(UniqueExprPtr&& expr)
	{
		return MakeUnique<ExprStmt>(std::move(expr));
	}

	UniqueDeclStmtPtr Sema::ActOnDeclStmt(UniqueDeclPtr&& decl)
	{
		return MakeUnique<DeclStmt>(std::move(decl));
	}

	UniqueReturnStmtPtr Sema::ActOnReturnStmt(UniqueExprStmtPtr&& expr_stmt)
	{
		WAVE_ASSERT(ctx.current_func);
		ctx.return_stmt_encountered = true;
		FunctionType const& func_type = type_cast<FunctionType>(*ctx.current_func);
		QualifiedType const& return_type = func_type.GetReturnType();

		Expr const* ret_expr = expr_stmt->GetExpr();
		QualifiedType const& ret_expr_type = ret_expr ? ret_expr->GetType() : builtin_types::Void;
		if (!ret_expr_type->IsCompatible(return_type))
		{
			diagnostics.Report(ret_expr ? ret_expr->GetLocation() : SourceLocation{}, incompatible_return_stmt_type);
		}
		return MakeUnique<ReturnStmt>(std::move(expr_stmt));
	}

	UniqueUnaryExprPtr Sema::ActOnUnaryExpr(UnaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& operand)
	{
		//#todo semantic analysis

		UniqueUnaryExprPtr unary_expr = MakeUnique<UnaryExpr>(op, loc);
		unary_expr->SetType(operand->GetType());
		unary_expr->SetOperand(std::move(operand));

		return unary_expr;
	}

	UniqueBinaryExprPtr Sema::ActOnBinaryExpr(BinaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& lhs, UniqueExprPtr&& rhs)
	{
		//#todo semantic analysis
		switch (op)
		{
		case BinaryExprKind::Assign:
		{
			if (lhs->IsLValue())
			{
				if (lhs->GetType().IsConst()) diagnostics.Report(loc, invalid_assignment_to_const);
			}
			else diagnostics.Report(loc, invalid_assignment_to_rvalue);
		}
		break;
		case BinaryExprKind::Add:
		break;
		case BinaryExprKind::Subtract:
		break;
		case BinaryExprKind::Multiply:
		break;
		case BinaryExprKind::Divide:
		break;
		break;
		}

		UniqueBinaryExprPtr binary_expr = MakeUnique<BinaryExpr>(op, loc);
		binary_expr->SetType(lhs->GetType());
		binary_expr->SetLHS(std::move(lhs));
		binary_expr->SetRHS(std::move(rhs));
		return binary_expr;
	}

	UniqueTernaryExprPtr Sema::ActOnTernaryExpr(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueExprPtr&& true_expr, UniqueExprPtr&& false_expr)
	{
		//#todo semantic analysis
		UniqueTernaryExprPtr ternary_expr = MakeUnique<TernaryExpr>(loc);
		ternary_expr->SetType(true_expr->GetType());
		ternary_expr->SetConditionExpr(std::move(cond_expr));
		ternary_expr->SetTrueExpr(std::move(true_expr));
		ternary_expr->SetFalseExpr(std::move(false_expr));
		return ternary_expr;
	}

	UniqueCastExprPtr Sema::ActOnCastExpr(SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& expr)
	{
		//#todo semantic analysis
		QualifiedType const& cast_type = type;
		QualifiedType const& operand_type = expr->GetType();

		if (IsArrayType(cast_type) || IsArrayType(operand_type)) diagnostics.Report(loc, invalid_cast);
		if(IsVoidType(cast_type)) diagnostics.Report(loc, invalid_cast);
		if(operand_type->IsCompatible(cast_type)) diagnostics.Report(loc, invalid_cast);
		
		UniqueCastExprPtr cast_expr = MakeUnique<CastExpr>(loc, type);
		cast_expr->SetOperand(std::move(expr));
		return cast_expr;
	}

	UniqueFunctionCallExprPtr Sema::ActOnFunctionCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args)
	{
		//#todo semantic analysis
		QualifiedType const& func_expr_type = func_expr->GetType();
		WAVE_ASSERT(IsFunctionType(func_expr_type));
		FunctionType func_type = type_cast<FunctionType>(func_expr_type);

		UniqueFunctionCallExprPtr func_call_expr = MakeUnique<FunctionCallExpr>(loc, std::move(func_expr));
		func_call_expr->SetType(func_type.GetReturnType());
		func_call_expr->SetArgs(std::move(args));
		return func_call_expr;
	}

	UniqueConstantIntPtr Sema::ActOnConstantInt(int64 value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantInt>(value, loc);
	}

	UniqueConstantStringPtr Sema::ActOnConstantString(std::string_view str, SourceLocation const& loc)
	{
		return MakeUnique<ConstantString>(str, loc);
	}

	UniqueConstantBoolPtr Sema::ActOnConstantBool(bool value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantBool>(value, loc);
	}

	UniqueConstantFloatPtr Sema::ActOnConstantFloat(double value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantFloat>(value, loc);
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
}

