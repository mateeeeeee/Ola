#pragma once
#include <memory>
#include <vector>
#include "ASTForwardDeclarations.h"

namespace wave
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename Type, typename... Args>
	inline UniquePtr<Type> MakeUnique(Args&&... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}

	using UniqueTranslationUnitPtr	= UniquePtr<TranslationUnit>;

	using UniqueDeclPtr				= UniquePtr<Decl>;
	using UniqueFunctionDeclPtr		= UniquePtr<FunctionDecl>;
	using UniqueVariableDeclPtr		= UniquePtr<VariableDecl>;
	using UniqueTagDeclPtr			= UniquePtr<TagDecl>;
	using UniqueEnumDeclPtr			= UniquePtr<EnumDecl>;
	using UniqueEnumMemberDeclPtr	= UniquePtr<EnumMemberDecl>;

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
	using UniqueConstantStringPtr	= UniquePtr<ConstantString>;
	using UniqueConstantBoolPtr		= UniquePtr<ConstantBool>;
	using UniqueConstantFloatPtr	= UniquePtr<ConstantFloat>;
	using UniqueImplicitCastExprPtr	= UniquePtr<ImplicitCastExpr>;
	using UniqueFunctionCallExprPtr = UniquePtr<FunctionCallExpr>;
	using UniqueInitializerListExprPtr = UniquePtr<InitializerListExpr>;

	using UniqueEnumMemberDeclPtrList = std::vector<UniqueEnumMemberDeclPtr>;
	using UniqueVariableDeclPtrList   = std::vector<UniqueVariableDeclPtr>;
	using UniqueDeclPtrList			  = std::vector<UniqueDeclPtr>;
	using UniqueStmtPtrList			  = std::vector<UniqueStmtPtr>;
	using UniqueExprPtrList			  = std::vector<UniqueExprPtr>;
	using ExprPtrList				  = std::vector<Expr*>;
	using DeclPtrList				  = std::vector<Decl*>;
	using StmtPtrList				  = std::vector<Stmt*>;
	using VariableDeclPtrList		  = std::vector<VariableDecl*>;
	using BreakStmtPtrList			  = std::vector<BreakStmt*>;
	using ContinueStmtPtrList		  = std::vector<ContinueStmt*>;
	using CaseStmtPtrList			  = std::vector<CaseStmt*>;
	using LabelStmtPtrList			  = std::vector<LabelStmt*>;
	using ConstLabelStmtPtrList		  = std::vector<LabelStmt const*>;
}