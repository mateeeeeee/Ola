#pragma once
#include "Scope.h"
#include "AST.h"

namespace wave
{
	namespace diag
	{
		enum DiagCode : uint32;
	}

	class Parser;
	class Diagnostics;
	struct SourceLocation;

	class Sema 
	{
		friend class Parser;
		struct Context
		{
			ScopeStack<Decl> decl_scope_stack;
			class QualifiedType const* current_func = nullptr;
			bool return_stmt_encountered = false;
		};

	public:
		explicit Sema(Diagnostics& diagnostics);
		WAVE_NONCOPYABLE(Sema);
		WAVE_DEFAULT_MOVABLE(Sema);
		~Sema();

	private:
		UniqueVariableDeclPtr ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& init_expr);
		UniqueFunctionDeclPtr ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt = nullptr);

		UniqueCompoundStmtPtr ActOnCompoundStmt(UniqueStmtPtrList&& stmts);
		UniqueExprStmtPtr ActOnExprStmt(UniqueExprPtr&& expr);
		UniqueDeclStmtPtr ActOnDeclStmt(UniqueDeclPtr&& decl);
		UniqueReturnStmtPtr ActOnReturnStmt(UniqueExprStmtPtr&& expr_stmt);
		UniqueIfStmtPtr ActOnIfStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& then_stmt, UniqueStmtPtr&& else_stmt);

		UniqueUnaryExprPtr ActOnUnaryExpr(UnaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& operand);
		UniqueBinaryExprPtr ActOnBinaryExpr(BinaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& lhs, UniqueExprPtr&& rhs);
		UniqueTernaryExprPtr ActOnTernaryExpr(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueExprPtr&& true_expr, UniqueExprPtr&& false_expr);
		UniqueCastExprPtr ActOnCastExpr(SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& expr);
		UniqueFunctionCallExprPtr ActOnFunctionCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args);
		UniqueConstantIntPtr ActOnConstantInt(int64 value, SourceLocation const& loc);
		UniqueConstantStringPtr ActOnConstantString(std::string_view str, SourceLocation const& loc);
		UniqueConstantBoolPtr ActOnConstantBool(bool value, SourceLocation const& loc);
		UniqueConstantFloatPtr ActOnConstantFloat(double value, SourceLocation const& loc);
		UniqueIdentifierExprPtr ActOnIdentifier(std::string_view name, SourceLocation const& loc);

	private:
		Diagnostics& diagnostics;
		Context ctx;
	};
}