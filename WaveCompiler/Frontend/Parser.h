#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Diagnostics.h"
#include "ASTTypeAliases.h"

namespace wave
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
		void Parse(std::vector<Token> const& tokens);
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

		WAVE_NODISCARD UniqueDeclPtrList ParseGlobalDeclaration();
		WAVE_NODISCARD UniqueFunctionDeclPtr ParseFunctionDeclaration();
		WAVE_NODISCARD UniqueFunctionDeclPtr ParseFunctionDefinition(DeclVisibility visibility);
		WAVE_NODISCARD UniqueMethodDeclPtr ParseMethodDefinition(bool first_pass);
		WAVE_NODISCARD UniqueParamVarDeclPtr ParseParamVariableDeclaration();
		WAVE_NODISCARD UniqueVarDeclPtrList ParseVariableDeclaration(DeclVisibility visibility);
		WAVE_NODISCARD UniqueFieldDeclPtrList ParseFieldDeclaration(bool first_pass);
		WAVE_NODISCARD UniqueDeclPtrList ParseExternVariableDeclaration();
		WAVE_NODISCARD UniqueEnumDeclPtr ParseEnumDeclaration();
		WAVE_NODISCARD UniqueAliasDeclPtr ParseAliasDeclaration();
		WAVE_NODISCARD UniqueClassDeclPtr ParseClassDeclaration();

		WAVE_NODISCARD UniqueStmtPtr ParseStatement();
		WAVE_NODISCARD UniqueCompoundStmtPtr ParseCompoundStatement();
		WAVE_NODISCARD UniqueExprStmtPtr ParseExpressionStatement();
		WAVE_NODISCARD UniqueReturnStmtPtr ParseReturnStatement();
		WAVE_NODISCARD UniqueIfStmtPtr ParseIfStatement();
		WAVE_NODISCARD UniqueBreakStmtPtr ParseBreakStatement();
		WAVE_NODISCARD UniqueContinueStmtPtr ParseContinueStatement();
		WAVE_NODISCARD UniqueForStmtPtr ParseForStatement();
		WAVE_NODISCARD UniqueForStmtPtr ParseForeachStatement();
		WAVE_NODISCARD UniqueWhileStmtPtr ParseWhileStatement();
		WAVE_NODISCARD UniqueDoWhileStmtPtr ParseDoWhileStatement();
		WAVE_NODISCARD UniqueCaseStmtPtr ParseCaseStatement();
		WAVE_NODISCARD UniqueSwitchStmtPtr ParseSwitchStatement();
		WAVE_NODISCARD UniqueGotoStmtPtr ParseGotoStatement();
		WAVE_NODISCARD UniqueLabelStmtPtr ParseLabelStatement();

		template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
		WAVE_NODISCARD UniqueExprPtr ParseBinaryExpression();
		WAVE_NODISCARD UniqueExprPtr ParseExpression();
		WAVE_NODISCARD UniqueExprPtr ParseParenthesizedExpression();
		WAVE_NODISCARD UniqueExprPtr ParseAssignmentExpression();
		WAVE_NODISCARD UniqueExprPtr ParseConditionalExpression();
		WAVE_NODISCARD UniqueExprPtr ParseLogicalOrExpression();
		WAVE_NODISCARD UniqueExprPtr ParseLogicalAndExpression();
		WAVE_NODISCARD UniqueExprPtr ParseInclusiveOrExpression();
		WAVE_NODISCARD UniqueExprPtr ParseExclusiveOrExpression();
		WAVE_NODISCARD UniqueExprPtr ParseAndExpression();
		WAVE_NODISCARD UniqueExprPtr ParseEqualityExpression();
		WAVE_NODISCARD UniqueExprPtr ParseRelationalExpression();
		WAVE_NODISCARD UniqueExprPtr ParseShiftExpression();
		WAVE_NODISCARD UniqueExprPtr ParseAdditiveExpression();
		WAVE_NODISCARD UniqueExprPtr ParseMultiplicativeExpression();
		WAVE_NODISCARD UniqueExprPtr ParseUnaryExpression();
		WAVE_NODISCARD UniqueExprPtr ParsePostFixExpression();
		WAVE_NODISCARD UniqueExprPtr ParsePrimaryExpression();
		WAVE_NODISCARD UniqueConstantIntPtr ParseSizeofExpression();
		WAVE_NODISCARD UniqueConstantIntPtr ParseLengthExpression();
		WAVE_NODISCARD UniqueConstantIntPtr ParseConstantInt();
		WAVE_NODISCARD UniqueConstantCharPtr ParseConstantChar();
		WAVE_NODISCARD UniqueConstantStringPtr ParseConstantString();
		WAVE_NODISCARD UniqueConstantBoolPtr ParseConstantBool();
		WAVE_NODISCARD UniqueConstantFloatPtr ParseConstantFloat();
		WAVE_NODISCARD UniqueExprPtr ParseIdentifier();
		WAVE_NODISCARD UniqueThisExprPtr ParseThisExpression();
		WAVE_NODISCARD UniqueDeclRefExprPtr ParseMemberIdentifier();
		WAVE_NODISCARD UniqueInitializerListExprPtr ParseInitializerListExpression();

		void ParseTypeQualifier(QualType& type);
		void ParseTypeSpecifier(QualType& type, bool array_size_required = false);

		bool IsFunctionDeclaration();
		bool IsCurrentTokenTypename();
	};

}