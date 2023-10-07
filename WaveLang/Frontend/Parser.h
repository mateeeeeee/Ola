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
	class FunctionDeclAST;

	using ExprParseFn = std::unique_ptr<ExprAST>(Parser::*)();
	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;

		struct Context
		{
			std::unique_ptr<SymbolTable<Symbol>> sym_table;
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
		Context ctx;

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
		[[nodiscard]] std::vector<std::unique_ptr<DeclAST>> ParseGlobalDeclaration();
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDeclaration();
		[[nodiscard]] std::unique_ptr<FunctionDeclAST> ParseFunctionDefinition();

		void ParseTypeQualifier(QualifiedType& type);
		void ParseTypeSpecifier(QualifiedType& type);
	};

}