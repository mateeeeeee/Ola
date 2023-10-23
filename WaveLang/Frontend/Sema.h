#pragma once
#include <functional>
#include <unordered_set>
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

		using CaseStmtCallback = std::function<void(CaseStmt*)>;
		struct Context
		{
			ScopeStack<Decl> decl_scope_stack;

			class QualifiedType const* current_func = nullptr;
			bool return_stmt_encountered = false;

			uint32 stmts_using_break_count = 0; 
			uint32 stmts_using_continue_count = 0;
			std::vector<CaseStmtCallback> case_callback_stack;

			std::unordered_set<std::string> labels;
			std::vector<std::string> gotos;
		};

	public:
		explicit Sema(Diagnostics& diagnostics);
		WAVE_NONCOPYABLE(Sema);
		WAVE_DEFAULT_MOVABLE(Sema);
		~Sema();

	private:
		UniqueVariableDeclPtr ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& init_expr);
		UniqueFunctionDeclPtr ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, 
												UniqueVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt = nullptr, 
												VisibilitySpecifier visibility = VisibilitySpecifier::Private);

		UniqueCompoundStmtPtr ActOnCompoundStmt(UniqueStmtPtrList&& stmts);
		UniqueExprStmtPtr ActOnExprStmt(UniqueExprPtr&& expr);
		UniqueDeclStmtPtr ActOnDeclStmt(UniqueDeclPtrList&& decls);
		UniqueReturnStmtPtr ActOnReturnStmt(UniqueExprStmtPtr&& expr_stmt);
		UniqueIfStmtPtr ActOnIfStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& then_stmt, UniqueStmtPtr&& else_stmt);
		UniqueBreakStmtPtr ActOnBreakStmt(SourceLocation const& loc);
		UniqueContinueStmtPtr ActOnContinueStmt(SourceLocation const& loc);
		UniqueForStmtPtr ActOnForStmt(UniqueStmtPtr&& init_stmt, UniqueExprPtr&& cond_expr, UniqueExprPtr&& iter_expr, UniqueStmtPtr&& body_stmt);
		UniqueWhileStmtPtr ActOnWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt);
		UniqueDoWhileStmtPtr ActOnDoWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt);
		UniqueCaseStmtPtr ActOnCaseStmt(SourceLocation const& loc, UniqueExprPtr&& case_expr = nullptr);
		UniqueSwitchStmtPtr ActOnSwitchStmt(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueStmtPtr body_stmt, CaseStmtPtrList&& case_stmts);
		UniqueGotoStmtPtr ActOnGotoStmt(SourceLocation const& loc, std::string_view label_name);
		UniqueLabelStmtPtr ActOnLabelStmt(SourceLocation const& loc, std::string_view label_name);

		UniqueUnaryExprPtr ActOnUnaryExpr(UnaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& operand);
		UniqueBinaryExprPtr ActOnBinaryExpr(BinaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& lhs, UniqueExprPtr&& rhs);
		UniqueTernaryExprPtr ActOnTernaryExpr(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueExprPtr&& true_expr, UniqueExprPtr&& false_expr);
		UniqueFunctionCallExprPtr ActOnFunctionCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args);
		UniqueConstantIntPtr ActOnConstantInt(int64 value, SourceLocation const& loc);
		UniqueConstantStringPtr ActOnConstantString(std::string_view str, SourceLocation const& loc);
		UniqueConstantBoolPtr ActOnConstantBool(bool value, SourceLocation const& loc);
		UniqueConstantFloatPtr ActOnConstantFloat(double value, SourceLocation const& loc);
		UniqueIdentifierExprPtr ActOnIdentifier(std::string_view name, SourceLocation const& loc);

	private:
		Diagnostics& diagnostics;
		Context ctx;

	private:
		UniqueImplicitCastExprPtr ActOnImplicitCastExpr(SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& expr);
	};
}