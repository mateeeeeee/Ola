#pragma once
#include <memory>
#include <vector>
#include "ASTFwd.h"

namespace ola
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename Type, typename... Args>
	inline UniquePtr<Type> MakeUnique(Args&&... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}

	using UniqueTranslationUnitPtr	= UniquePtr<TranslationUnit>;

	using UniqueDeclPtr				  = UniquePtr<Decl>;
	using UniqueFunctionDeclPtr		  = UniquePtr<FunctionDecl>;
	using UniqueMethodDeclPtr		  = UniquePtr<MethodDecl>;
	using UniqueVarDeclPtr			  = UniquePtr<VarDecl>;
	using UniqueParamVarDeclPtr		  = UniquePtr<ParamVarDecl>;
	using UniqueFieldDeclPtr		  = UniquePtr<FieldDecl>;
	using UniqueTagDeclPtr			  = UniquePtr<TagDecl>;
	using UniqueEnumDeclPtr			  = UniquePtr<EnumDecl>;
	using UniqueEnumMemberDeclPtr	  = UniquePtr<EnumMemberDecl>;
	using UniqueAliasDeclPtr		  = UniquePtr<AliasDecl>;
	using UniqueClassDeclPtr		  = UniquePtr<ClassDecl>;

	using UniqueStmtPtr				= UniquePtr<Stmt>;
	using UniqueCompoundStmtPtr		= UniquePtr<CompoundStmt>;
	using UniqueExprStmtPtr			= UniquePtr<ExprStmt>;
	using UniqueDeclStmtPtr			= UniquePtr<DeclStmt>;
	using UniqueNullStmtPtr			= UniquePtr<NullStmt>;
	using UniqueReturnStmtPtr		= UniquePtr<ReturnStmt>;
	using UniqueIfStmtPtr			= UniquePtr<IfStmt>;
	using UniqueBreakStmtPtr		= UniquePtr<BreakStmt>;
	using UniqueContinueStmtPtr		= UniquePtr<ContinueStmt>;
	using UniqueForStmtPtr			= UniquePtr<ForStmt>;
	using UniqueWhileStmtPtr		= UniquePtr<WhileStmt>;
	using UniqueDoWhileStmtPtr		= UniquePtr<DoWhileStmt>;
	using UniqueCaseStmtPtr			= UniquePtr<CaseStmt>;
	using UniqueSwitchStmtPtr		= UniquePtr<SwitchStmt>;
	using UniqueGotoStmtPtr			= UniquePtr<GotoStmt>;
	using UniqueLabelStmtPtr		= UniquePtr<LabelStmt>;

	using UniqueExprPtr				= UniquePtr<Expr>;
	using UniqueUnaryExprPtr		= UniquePtr<UnaryExpr>;
	using UniqueBinaryExprPtr		= UniquePtr<BinaryExpr>;
	using UniqueTernaryExprPtr		= UniquePtr<TernaryExpr>;
	using UniqueIdentifierExprPtr	= UniquePtr<IdentifierExpr>;
	using UniqueDeclRefExprPtr		= UniquePtr<DeclRefExpr>;
	using UniqueConstantIntPtr		= UniquePtr<ConstantInt>;
	using UniqueConstantCharPtr		= UniquePtr<ConstantChar>;
	using UniqueConstantStringPtr	= UniquePtr<ConstantString>;
	using UniqueConstantBoolPtr		= UniquePtr<ConstantBool>;
	using UniqueConstantFloatPtr	= UniquePtr<ConstantFloat>;
	using UniqueImplicitCastExprPtr	= UniquePtr<ImplicitCastExpr>;
	using UniqueCallExprPtr			= UniquePtr<CallExpr>;
	using UniqueInitializerListExprPtr = UniquePtr<InitializerListExpr>;
	using UniqueArrayAccessExprPtr	= UniquePtr<ArrayAccessExpr>;
	using UniqueMemberExprPtr		= UniquePtr<MemberExpr>;
	using UniqueMethodCallExprPtr	= UniquePtr<MethodCallExpr>;
	using UniqueThisExprPtr			= UniquePtr<ThisExpr>;
	using UniqueSuperExprPtr		= UniquePtr<SuperExpr>;

	using UniqueEnumMemberDeclPtrList	  = std::vector<UniqueEnumMemberDeclPtr>;
	using UniqueVarDeclPtrList			  = std::vector<UniqueVarDeclPtr>;
	using UniqueParamVarDeclPtrList		  = std::vector<UniqueParamVarDeclPtr>;
	using UniqueFieldDeclPtrList		  = std::vector<UniqueFieldDeclPtr>;
	using UniqueFunctionDeclPtrList		  = std::vector<UniqueFunctionDeclPtr>;
	using UniqueMethodDeclPtrList		  = std::vector<UniqueMethodDeclPtr>;
	using UniqueDeclPtrList				  = std::vector<UniqueDeclPtr>;
	using UniqueStmtPtrList				  = std::vector<UniqueStmtPtr>;
	using UniqueExprPtrList				  = std::vector<UniqueExprPtr>;
	using CaseStmtPtrList				  = std::vector<CaseStmt*>;
}