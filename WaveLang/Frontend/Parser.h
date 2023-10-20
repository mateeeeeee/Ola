#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Diagnostics.h"
#include "ASTTypeAliases.h"

namespace wave
{
	class QualifiedType;
	class Sema;
	class Parser;
	
	enum class BinaryExprKind : uint8;
	using ExprParseFn = UniqueExprPtr(Parser::*)();

	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;
	public:

		explicit Parser(Diagnostics& diagnostics, std::vector<Token> const& tokens);
		~Parser();

		void Parse();
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

		void PreprocessTokens();
		void ParseTranslationUnit();
		[[nodiscard]] UniqueDeclPtr ParseGlobalDeclaration();
		[[nodiscard]] UniqueFunctionDeclPtr ParseFunctionDeclaration(bool is_function_def = false);
		[[nodiscard]] UniqueVariableDeclPtr ParseVariableDeclaration(bool function_param_decl);

		[[nodiscard]] UniqueStmtPtr ParseStatement();
		[[nodiscard]] UniqueCompoundStmtPtr ParseCompoundStatement();
		[[nodiscard]] UniqueExprStmtPtr ParseExpressionStatement();
		[[nodiscard]] UniqueReturnStmtPtr ParseReturnStatement();
		[[nodiscard]] UniqueIfStmtPtr ParseIfStatement();
		[[nodiscard]] UniqueBreakStmtPtr ParseBreakStatement();
		[[nodiscard]] UniqueContinueStmtPtr ParseContinueStatement();
		[[nodiscard]] UniqueForStmtPtr ParseForStatement();

		template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
		[[nodiscard]] UniqueExprPtr ParseBinaryExpression();
		[[nodiscard]] UniqueExprPtr ParseExpression();
		[[nodiscard]] UniqueExprPtr ParseParenthesizedExpression();
		[[nodiscard]] UniqueExprPtr ParseAssignmentExpression();
		[[nodiscard]] UniqueExprPtr ParseConditionalExpression();
		[[nodiscard]] UniqueExprPtr ParseLogicalOrExpression();
		[[nodiscard]] UniqueExprPtr ParseLogicalAndExpression();
		[[nodiscard]] UniqueExprPtr ParseInclusiveOrExpression();
		[[nodiscard]] UniqueExprPtr ParseExclusiveOrExpression();
		[[nodiscard]] UniqueExprPtr ParseAndExpression();
		[[nodiscard]] UniqueExprPtr ParseEqualityExpression();
		[[nodiscard]] UniqueExprPtr ParseRelationalExpression();
		[[nodiscard]] UniqueExprPtr ParseShiftExpression();
		[[nodiscard]] UniqueExprPtr ParseAdditiveExpression();
		[[nodiscard]] UniqueExprPtr ParseMultiplicativeExpression();
		[[nodiscard]] UniqueExprPtr ParseUnaryExpression();
		[[nodiscard]] UniqueExprPtr ParsePostFixExpression();
		[[nodiscard]] UniqueExprPtr ParseSizeofExpression();
		[[nodiscard]] UniqueConstantIntPtr ParseAlignofExpression();
		[[nodiscard]] UniqueConstantIntPtr ParseAlignasExpression();
		[[nodiscard]] UniqueExprPtr ParsePrimaryExpression();
		[[nodiscard]] UniqueConstantIntPtr ParseConstantInt();
		[[nodiscard]] UniqueConstantStringPtr ParseConstantString();
		[[nodiscard]] UniqueConstantBoolPtr ParseConstantBool();
		[[nodiscard]] UniqueConstantFloatPtr ParseConstantFloat();
		[[nodiscard]] UniqueIdentifierExprPtr ParseIdentifier();

		void ParseTypeQualifier(QualifiedType& type);
		void ParseTypeSpecifier(QualifiedType& type);
	};

}