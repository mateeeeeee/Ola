#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Symbol.h"
#include "Diagnostics.h"

namespace wave
{
	class Parser;
	struct AST;
	class ExprAST;
	class DeclAST;
	class StmtAST;
	class FunctionDeclAST;
	class VariableDeclAST;
	class CompoundStmtAST;
	class ExprStmtAST;
	class ReturnStmtAST;

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

		void ParseTranslationUnit();
		[[nodiscard]] std::unique_ptr<DeclAST> ParseGlobalDeclaration();
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDeclaration();
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDefinition();
		[[nodiscard]] std::unique_ptr<VariableDeclAST> ParseVariableDeclaration(bool function_param_decl);

		[[nodiscard]] std::unique_ptr<StmtAST> ParseStatement();
		[[nodiscard]] std::unique_ptr<CompoundStmtAST> ParseCompoundStatement();
		[[nodiscard]] std::unique_ptr<ExprStmtAST> ParseExpressionStatement();
		[[nodiscard]] std::unique_ptr<ReturnStmtAST> ParseReturnStatement();

		[[nodiscard]] std::unique_ptr<ExprAST> ParseExpression();

		void ParseTypeQualifier(QualifiedType& type);
		void ParseTypeSpecifier(QualifiedType& type);
	};

}