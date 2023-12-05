#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Diagnostics.h"
#include "AST/ASTTypeAliases.h"

namespace ola
{
	class QualType;
	class Sema;
	class Parser;
	
	enum class BinaryExprKind : uint8;
	enum class DeclVisibility : uint8;
	using ExprParseFn = UniqueExprPtr(Parser::*)();

	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;
	public:

		explicit Parser(Diagnostics& diagnostics);
		~Parser();

		void Parse(std::vector<Token>&& tokens);
		void ParseImported(std::vector<Token> const& tokens);
		AST const* GetAST() const { return ast.get(); }

	private:
		Diagnostics& diagnostics;
		std::vector<Token> tokens;
		TokenPtr current_token;

		std::unique_ptr<Sema> sema;
		std::unique_ptr<AST> ast;

	private:
		bool Consume(TokenKind k)
		{
			if (current_token->Is(k))
			{
				++current_token; return true;
			}
			else return false;
		}
		template<typename... Ts>
		bool Consume(TokenKind k, Ts... ts)
		{
			if (current_token->IsOneOf(k, ts...))
			{
				++current_token; return true;
			}
			else return false;
		}
		bool Expect(TokenKind k);
		template<typename... Ts>
		bool Expect(TokenKind k, Ts... ts)
		{
			if (!Consume(k, ts...))
			{
				Diag(unexpected_token);
				return false;
			}
			return true;
		}
		void Diag(DiagCode);
		template<typename... Ts>
		void Diag(DiagCode code, Ts&&... args)
		{
			diagnostics.Report(code, current_token->GetLocation(), std::forward<Ts>(args)...);
		}

		void ParseTranslationUnit();
		void AddBuiltinDecls(UniqueTranslationUnitPtr& TU);

		OLA_NODISCARD UniqueDeclPtrList ParseGlobalDeclaration();
		OLA_NODISCARD UniqueFunctionDeclPtr ParseFunctionDeclaration();
		OLA_NODISCARD UniqueFunctionDeclPtr ParseFunctionDefinition(DeclVisibility visibility);
		OLA_NODISCARD UniqueMethodDeclPtr ParseMethodDefinition(bool first_pass);
		OLA_NODISCARD UniqueParamVarDeclPtr ParseParamVariableDeclaration();
		OLA_NODISCARD UniqueVarDeclPtrList ParseVariableDeclaration(DeclVisibility visibility);
		OLA_NODISCARD UniqueFieldDeclPtrList ParseFieldDeclaration(bool first_pass);
		OLA_NODISCARD UniqueDeclPtrList ParseExternVariableDeclaration();
		OLA_NODISCARD UniqueEnumDeclPtr ParseEnumDeclaration();
		OLA_NODISCARD UniqueAliasDeclPtr ParseAliasDeclaration();
		OLA_NODISCARD UniqueClassDeclPtr ParseClassDeclaration();

		OLA_NODISCARD UniqueStmtPtr ParseStatement();
		OLA_NODISCARD UniqueCompoundStmtPtr ParseCompoundStatement();
		OLA_NODISCARD UniqueExprStmtPtr ParseExpressionStatement();
		OLA_NODISCARD UniqueReturnStmtPtr ParseReturnStatement();
		OLA_NODISCARD UniqueIfStmtPtr ParseIfStatement();
		OLA_NODISCARD UniqueBreakStmtPtr ParseBreakStatement();
		OLA_NODISCARD UniqueContinueStmtPtr ParseContinueStatement();
		OLA_NODISCARD UniqueForStmtPtr ParseForStatement();
		OLA_NODISCARD UniqueForStmtPtr ParseForeachStatement();
		OLA_NODISCARD UniqueWhileStmtPtr ParseWhileStatement();
		OLA_NODISCARD UniqueDoWhileStmtPtr ParseDoWhileStatement();
		OLA_NODISCARD UniqueCaseStmtPtr ParseCaseStatement();
		OLA_NODISCARD UniqueSwitchStmtPtr ParseSwitchStatement();
		OLA_NODISCARD UniqueGotoStmtPtr ParseGotoStatement();
		OLA_NODISCARD UniqueLabelStmtPtr ParseLabelStatement();

		template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
		OLA_NODISCARD UniqueExprPtr ParseBinaryExpression();
		OLA_NODISCARD UniqueExprPtr ParseExpression();
		OLA_NODISCARD UniqueExprPtr ParseParenthesizedExpression();
		OLA_NODISCARD UniqueExprPtr ParseAssignmentExpression();
		OLA_NODISCARD UniqueExprPtr ParseConditionalExpression();
		OLA_NODISCARD UniqueExprPtr ParseLogicalOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseLogicalAndExpression();
		OLA_NODISCARD UniqueExprPtr ParseInclusiveOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseExclusiveOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseAndExpression();
		OLA_NODISCARD UniqueExprPtr ParseEqualityExpression();
		OLA_NODISCARD UniqueExprPtr ParseRelationalExpression();
		OLA_NODISCARD UniqueExprPtr ParseShiftExpression();
		OLA_NODISCARD UniqueExprPtr ParseAdditiveExpression();
		OLA_NODISCARD UniqueExprPtr ParseMultiplicativeExpression();
		OLA_NODISCARD UniqueExprPtr ParseUnaryExpression();
		OLA_NODISCARD UniqueExprPtr ParsePostFixExpression();
		OLA_NODISCARD UniqueExprPtr ParsePrimaryExpression();
		OLA_NODISCARD UniqueConstantIntPtr ParseSizeofExpression();
		OLA_NODISCARD UniqueConstantIntPtr ParseLengthExpression();
		OLA_NODISCARD UniqueConstantIntPtr ParseConstantInt();
		OLA_NODISCARD UniqueConstantCharPtr ParseConstantChar();
		OLA_NODISCARD UniqueConstantStringPtr ParseConstantString();
		OLA_NODISCARD UniqueConstantBoolPtr ParseConstantBool();
		OLA_NODISCARD UniqueConstantFloatPtr ParseConstantFloat();
		OLA_NODISCARD UniqueExprPtr ParseIdentifier();
		OLA_NODISCARD UniqueThisExprPtr ParseThisExpression();
		OLA_NODISCARD UniqueDeclRefExprPtr ParseMemberIdentifier();
		OLA_NODISCARD UniqueInitializerListExprPtr ParseInitializerListExpression();

		void ParseFunctionAttributes(uint8& attrs);
		void ParseMethodAttributes(uint8& attrs);
		void ParseTypeQualifier(QualType& type);
		void ParseTypeSpecifier(QualType& type, bool array_size_required = false, bool allow_ref = true);

		bool IsFunctionDeclaration();
		bool IsCurrentTokenTypename();
	};

}