#pragma once
#include <vector>
#include <memory>
#include "Token.h"

namespace wave
{
	struct AST;
	class ExprAST;

	using ExprParseFn = std::unique_ptr<ExprAST>(Parser::*)();
	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;

		struct Context
		{

		};
	public:

		explicit Parser(std::vector<Token> const& tokens);
		~Parser();

		void Parse();
		AST* GetAST() const { return ast.get(); }

	private:
		std::vector<Token> tokens;
		TokenPtr current_token;
		std::unique_ptr<AST> ast;
		Context context;

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
				Report(diag::unexpected_token);
				return false;
			}
			return true;
		}
		void Report(diag::DiagCode);

		void ParseTranslationUnit();
		[[nodiscard]] std::vector<std::unique_ptr<DeclAST>> ParseDeclaration();
	};
}