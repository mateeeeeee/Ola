#pragma once
#include <functional>
#include <unordered_set>
#include "Scope.h"
#include "AST/AST.h"
#include "AST/Decl.h"
#include "AST/Stmt.h"
#include "AST/Expr.h"

namespace ola
{
	namespace diag
	{
		enum DiagCode : uint32;
	}

	class Parser;
	class Diagnostics;
	struct SourceLocation;

	enum TagKind
	{
		Tag_Enum,
		Tag_Class
	};

	class Sema 
	{
		friend class Parser;

		using CaseStmtCallback = std::function<void(CaseStmt*)>;
		struct Context
		{
			SymbolTable<Decl> decl_sym_table;
			SymbolTable<TagDecl> tag_sym_table;

			std::vector<Expr const*> current_class_expr_stack;
			bool is_method_const = false;
			class QualType const* current_func = nullptr;
			ClassDecl const* current_base_class = nullptr;
			bool return_stmt_encountered = false;

			uint32 stmts_using_break_count = 0; 
			uint32 stmts_using_continue_count = 0;
			std::vector<CaseStmtCallback> case_callback_stack;

			std::unordered_set<std::string> labels;
			std::vector<std::string> gotos;
		};

	public:
		explicit Sema(Diagnostics& diagnostics);
		OLA_NONCOPYABLE(Sema)
		OLA_DEFAULT_MOVABLE(Sema)
		~Sema();

	private:

		UniqueVarDeclPtr       ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility);
		UniqueFieldDeclPtr ActOnFieldDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility);
		UniqueParamVarDeclPtr  ActOnParamVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type);

		UniqueFunctionDeclPtr ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualType const& type, 
												UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt,
												DeclVisibility visibility, FuncAttributes attributes);
		UniqueMethodDeclPtr ActOnMethodDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
												UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt,
												DeclVisibility visibility, FuncAttributes func_attrs, MethodAttributes method_attrs);
		UniqueEnumDeclPtr ActOnEnumDecl(std::string_view name, SourceLocation const& loc, UniqueEnumMemberDeclPtrList&& enum_members);
		UniqueEnumMemberDeclPtr ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, UniqueExprPtr&& enum_value_expr);
		UniqueEnumMemberDeclPtr ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, int64 enum_value);
		UniqueAliasDeclPtr ActOnAliasDecl(std::string_view name, SourceLocation const& loc, QualType const& type);

		ClassDecl const* ActOnBaseClassSpecifier(std::string_view base_name, SourceLocation const& loc);
		UniqueClassDeclPtr ActOnClassDecl(std::string_view name, ClassDecl const* base_class, SourceLocation const& loc,
										  UniqueFieldDeclPtrList&& member_variables, UniqueMethodDeclPtrList&& member_functions);

		UniqueCompoundStmtPtr ActOnCompoundStmt(UniqueStmtPtrList&& stmts);
		UniqueExprStmtPtr ActOnExprStmt(UniqueExprPtr&& expr);
		UniqueDeclStmtPtr ActOnDeclStmt(UniqueDeclPtr&& decl);
		UniqueDeclStmtPtr ActOnDeclStmt(UniqueDeclPtrList&& decls);
		UniqueReturnStmtPtr ActOnReturnStmt(UniqueExprStmtPtr&& expr_stmt);
		UniqueIfStmtPtr ActOnIfStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& then_stmt, UniqueStmtPtr&& else_stmt);
		UniqueBreakStmtPtr ActOnBreakStmt(SourceLocation const& loc);
		UniqueContinueStmtPtr ActOnContinueStmt(SourceLocation const& loc);
		UniqueForStmtPtr ActOnForStmt(UniqueStmtPtr&& init_stmt, UniqueExprPtr&& cond_expr, UniqueExprPtr&& iter_expr, UniqueStmtPtr&& body_stmt);
		UniqueForStmtPtr ActOnForeachStmt(SourceLocation const& loc, UniqueVarDeclPtr&& var_decl, UniqueExprPtr&& array_identifier, UniqueStmtPtr&& body_stmt);
		UniqueWhileStmtPtr ActOnWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt);
		UniqueDoWhileStmtPtr ActOnDoWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt);
		UniqueCaseStmtPtr ActOnCaseStmt(SourceLocation const& loc, UniqueExprPtr&& case_expr = nullptr);
		UniqueSwitchStmtPtr ActOnSwitchStmt(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueStmtPtr body_stmt, std::vector<CaseStmt*>&& case_stmts);
		UniqueGotoStmtPtr ActOnGotoStmt(SourceLocation const& loc, std::string_view label_name);
		UniqueLabelStmtPtr ActOnLabelStmt(SourceLocation const& loc, std::string_view label_name);

		UniqueUnaryExprPtr ActOnUnaryExpr(UnaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& operand);
		UniqueBinaryExprPtr ActOnBinaryExpr(BinaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& lhs, UniqueExprPtr&& rhs);
		UniqueTernaryExprPtr ActOnTernaryExpr(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueExprPtr&& true_expr, UniqueExprPtr&& false_expr);
		UniqueCallExprPtr ActOnCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args);
		UniqueConstantIntPtr ActOnConstantInt(int64 value, SourceLocation const& loc);
		UniqueConstantIntPtr ActOnLengthOperator(QualType const& type, SourceLocation const& loc);
		UniqueConstantCharPtr ActOnConstantChar(std::string_view str, SourceLocation const& loc);
		UniqueConstantStringPtr ActOnConstantString(std::string_view str, SourceLocation const& loc);
		UniqueConstantBoolPtr ActOnConstantBool(bool value, SourceLocation const& loc);
		UniqueConstantFloatPtr ActOnConstantFloat(double value, SourceLocation const& loc);
		UniqueExprPtr ActOnIdentifier(std::string_view name, SourceLocation const& loc);
		UniqueDeclRefExprPtr ActOnMemberIdentifier(std::string_view name, SourceLocation const& loc);
		UniqueInitializerListExprPtr ActOnInitializerListExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtrList&& expr_list);
		UniqueArrayAccessExprPtr ActOnArrayAccessExpr(SourceLocation const& loc, UniqueExprPtr&& array_expr, UniqueExprPtr&& index_expr);
		UniqueMemberExprPtr ActOnMemberExpr(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueDeclRefExprPtr&& member_identifier);
		UniqueThisExprPtr ActOnThisExpr(SourceLocation const& loc, bool implicit);
		UniqueSuperExprPtr ActOnSuperExpr(SourceLocation const& loc, bool implicit);

	private:
		Diagnostics& diagnostics;
		Context ctx;

	private:
		UniqueImplicitCastExprPtr ActOnImplicitCastExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtr&& expr);

		template<typename Decl> requires std::is_base_of_v<VarDecl, Decl>
		UniquePtr<Decl> ActOnVariableDeclCommon(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility);
	};

}