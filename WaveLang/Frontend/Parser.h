#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Sema.h"
#include "Diagnostics.h"

namespace wave
{
	enum class BinaryExprKind : uint8;

	using ExprParseFn = std::unique_ptr<ExprAST>(Parser::*)();
	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;
	public:

		explicit Parser(std::vector<Token> const& tokens);
		~Parser();

		void Parse();
		AST* GetAST() const { return ast.get(); }

	private:
		Sema sema;
		std::vector<Token> tokens;
		TokenPtr current_token;
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
				Diag(diag::unexpected_token);
				return false;
			}
			return true;
		}
		void Diag(diag::DiagCode);

		void PreprocessTokens();
		void ParseTranslationUnit();
		[[nodiscard]] std::unique_ptr<DeclAST> ParseGlobalDeclaration();
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDeclaration(bool expect_semicolon = true);
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDefinition();
		[[nodiscard]] std::unique_ptr<VariableDeclAST> ParseVariableDeclaration(bool function_param_decl);

		[[nodiscard]] std::unique_ptr<StmtAST> ParseStatement();
		[[nodiscard]] std::unique_ptr<CompoundStmtAST> ParseCompoundStatement();
		[[nodiscard]] std::unique_ptr<ExprStmtAST> ParseExpressionStatement();
		[[nodiscard]] std::unique_ptr<ReturnStmtAST> ParseReturnStatement();

		template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
		[[nodiscard]] std::unique_ptr<ExprAST> ParseBinaryExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseParenthesizedExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseAssignmentExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseConditionalExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseLogicalOrExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseLogicalAndExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseInclusiveOrExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseExclusiveOrExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseAndExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseEqualityExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseRelationalExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseShiftExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseAdditiveExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseMultiplicativeExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseCastExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseUnaryExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParsePostFixExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParseSizeofExpression();
		[[nodiscard]] std::unique_ptr<IntLiteralAST> ParseAlignofExpression();
		[[nodiscard]] std::unique_ptr<IntLiteralAST> ParseAlignasExpression();
		[[nodiscard]] std::unique_ptr<ExprAST> ParsePrimaryExpression();
		[[nodiscard]] std::unique_ptr<IntLiteralAST> ParseIntegerLiteral();
		[[nodiscard]] std::unique_ptr<StringLiteralAST> ParseStringLiteral();
		[[nodiscard]] std::unique_ptr<IdentifierAST> ParseIdentifier();

		void ParseTypeQualifier(QualifiedType& type);
		void ParseTypeSpecifier(QualifiedType& type);
	};

}