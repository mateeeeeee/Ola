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
		enum DiagCode : Uint32;
	}

	class Parser;
	class Diagnostics;
	class FrontendContext;
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
		struct SemaContext
		{
			SymbolTable<Decl> decl_sym_table;
			SymbolTable<TagDecl> tag_sym_table;

			std::vector<Expr const*> current_class_expr_stack;
			Bool is_method_const = false;
			Bool is_constructor = false;
			ClassDecl const* current_base_class = nullptr;
			std::string current_class_name;

			class QualType const* current_func  = nullptr;
			Bool return_stmt_encountered = false;

			Uint32 stmts_using_break_count = 0; 
			Uint32 stmts_using_continue_count = 0;
			std::vector<CaseStmtCallback> case_callback_stack;

			std::unordered_set<std::string> labels;
			std::vector<std::string> gotos;
		};

	public:
		Sema(FrontendContext* context, Diagnostics& diagnostics);
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
		UniqueConstructorDeclPtr ActOnConstructorDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
													  UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt);
		UniqueEnumDeclPtr ActOnEnumDecl(std::string_view name, SourceLocation const& loc, UniqueEnumMemberDeclPtrList&& enum_members);
		UniqueEnumMemberDeclPtr ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, UniqueExprPtr&& enum_value_expr);
		UniqueEnumMemberDeclPtr ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, Int64 enum_value);
		UniqueAliasDeclPtr ActOnAliasDecl(std::string_view name, SourceLocation const& loc, QualType const& type);

		ClassDecl const* ActOnBaseClassSpecifier(std::string_view base_name, SourceLocation const& loc);
		UniqueClassDeclPtr ActOnClassDecl(std::string_view name, ClassDecl const* base_class, SourceLocation const& loc,
										  UniqueFieldDeclPtrList&& member_variables, UniqueMethodDeclPtrList&& member_functions, Bool final);

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
		UniqueIntLiteralPtr ActOnIntLiteral(Int64 value, SourceLocation const& loc);
		UniqueIntLiteralPtr ActOnLengthOperator(QualType const& type, SourceLocation const& loc);
		UniqueCharLiteralPtr ActOnCharLiteral(std::string_view str, SourceLocation const& loc);
		UniqueStringLiteralPtr ActOnStringLiteral(std::string_view str, SourceLocation const& loc);
		UniqueBoolLiteralPtr ActOnBoolLiteral(Bool value, SourceLocation const& loc);
		UniqueFloatLiteralPtr ActOnFloatLiteral(Float64 value, SourceLocation const& loc);
		UniqueExprPtr ActOnIdentifier(std::string_view name, SourceLocation const& loc, Bool overloaded_symbol);
		UniqueIdentifierExprPtr ActOnMemberIdentifier(std::string_view name, SourceLocation const& loc, Bool overloaded_symbol);
		UniqueInitializerListExprPtr ActOnInitializerListExpr(SourceLocation const& loc, UniqueExprPtrList&& expr_list);
		UniqueArrayAccessExprPtr ActOnArrayAccessExpr(SourceLocation const& loc, UniqueExprPtr&& array_expr, UniqueExprPtr&& index_expr);
		UniqueMemberExprPtr ActOnFieldAccess(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueIdentifierExprPtr&& field_name);
		UniqueMethodCallExprPtr ActOnMethodCall(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueIdentifierExprPtr&& method_name, UniqueExprPtrList&& args);
		UniqueThisExprPtr ActOnThisExpr(SourceLocation const& loc, Bool implicit);
		UniqueSuperExprPtr ActOnSuperExpr(SourceLocation const& loc, Bool implicit);
		UniqueConstructorExprPtr ActOnConstructorExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtrList&& args);

	private:
		FrontendContext* ctx;
		Diagnostics& diagnostics;
		SemaContext sema_ctx;

	private:
		UniqueExprPtr ActOnImplicitCastExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtr&& expr);

		template<typename DeclT> requires std::is_base_of_v<VarDecl, DeclT>
		UniquePtr<DeclT> ActOnVariableDeclCommon(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility);

		template<typename DeclT> requires std::is_base_of_v<FunctionDecl, DeclT>
		std::vector<DeclT const*> ResolveCall(std::vector<DeclT const*> const& candidate_decls, UniqueExprPtrList& args);
	};


}