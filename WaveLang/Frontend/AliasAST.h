#pragma once
#include <memory>
#include <vector>
#include "ForwardAST.h"

namespace wave
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename Type, typename... Args>
	inline UniquePtr<Type> MakeUnique(Args&&... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}

	using UniqueTranslationUnitPtr	= UniquePtr<TranslationUnitAST>;
	using UniqueDeclPtr				= UniquePtr<DeclAST>;
	using UniqueFunctionDeclPtr		= UniquePtr<FunctionDeclAST>;
	using UniqueVariableDeclPtr		= UniquePtr<VariableDeclAST>;
	using UniqueStmtPtr				= UniquePtr<StmtAST>;
	using UniqueCompoundStmtPtr		= UniquePtr<CompoundStmtAST>;
	using UniqueExprStmtPtr			= UniquePtr<ExprStmtAST>;
	using UniqueDeclStmtPtr			= UniquePtr<DeclStmtAST>;
	using UniqueNullStmtPtr			= UniquePtr<NullStmtAST>;
	using UniqueIfStmtPtr			= UniquePtr<IfStmtAST>;
	using UniqueReturnStmtPtr		= UniquePtr<ReturnStmtAST>;
	using UniqueExprPtr				= UniquePtr<ExprAST>;
	using UniqueUnaryExprPtr		= UniquePtr<UnaryExprAST>;
	using UniqueBinaryExprPtr		= UniquePtr<BinaryExprAST>;
	using UniqueTernaryExprPtr		= UniquePtr<TernaryExprAST>;
	using UniqueIntLiteralPtr		= UniquePtr<IntLiteralAST>;
	using UniqueStringLiteralPtr	= UniquePtr<StringLiteralAST>;
	using UniqueIdentifierPtr		= UniquePtr<IdentifierAST>;
	using UniqueCastExprPtr			= UniquePtr<CastExprAST>;
	using UniqueFunctionCallExprPtr = UniquePtr<FunctionCallExprAST>;

	using TranslationUnitPtr		= TranslationUnitAST*;
	using DeclPtr					= DeclAST*;
	using FunctionDeclPtr			= FunctionDeclAST*;
	using VariableDeclPtr			= VariableDeclAST*;
	using StmtPtr					= StmtAST*;
	using CompoundStmtPtr			= CompoundStmtAST*;
	using ExprStmtPtr				= ExprStmtAST*;
	using DeclStmtPtr				= DeclStmtAST*;
	using NullStmtPtr				= NullStmtAST*;
	using IfStmtPtr					= IfStmtAST*;
	using ReturnStmtPtr				= ReturnStmtAST*;
	using ExprPtr					= ExprAST*;
	using UnaryExprPtr				= UnaryExprAST*;
	using BinaryExprPtr				= BinaryExprAST*;
	using TernaryExprPtr			= TernaryExprAST*;
	using IntLiteralPtr				= IntLiteralAST*;
	using StringLiteralPtr			= StringLiteralAST*;
	using IdentifierPtr				= IdentifierAST*;
	using CastExprPtr				= CastExprAST*;
	using FunctionCallExprPtr		= FunctionCallExprAST*;

	using UniqueVariableDeclPtrList = std::vector<UniqueVariableDeclPtr>;
	using VariableDeclPtrList		= std::vector<VariableDeclPtr>;
	using UniqueDeclPtrList			= std::vector<UniqueDeclPtr>;
	using DeclPtrList				= std::vector<DeclPtr>;
	using UniqueStmtPtrList			= std::vector<UniqueStmtPtr>;
	using StmtPtrList				= std::vector<StmtPtr>;
	using UniqueExprPtrList			= std::vector<UniqueExprPtr>;
	using ExprPtrList				= std::vector<ExprPtr>;
}