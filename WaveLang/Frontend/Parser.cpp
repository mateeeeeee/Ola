#include "Parser.h"
#include "Diagnostics.h"
#include "AST.h"

namespace wave
{

	Parser::Parser(std::vector<Token> const& _tokens) : tokens(_tokens), current_token(tokens.begin()) {}
	Parser::~Parser() = default;

	void Parser::Parse()
	{
		ast = std::make_unique<AST>();
		ParseTranslationUnit();
	}

	bool Parser::Expect(TokenKind k)
	{
		if (!Consume(k))
		{
			Report(diag::unexpected_token);
			return false;
		}
		return true;
	}

	void Parser::Report(diag::DiagCode code)
	{
		--current_token;
		diag::Report(code, current_token->GetLocation());
		++current_token;
	}

	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof))
		{
			std::vector<std::unique_ptr<DeclAST>> declarations = ParseDeclaration();
			for (auto&& declaration : declarations) ast->translation_unit->AddDeclaration(std::move(declaration));
		}
	}

	std::vector<std::unique_ptr<wave::DeclAST>> Parser::ParseDeclaration()
	{
		while (Consume(TokenKind::semicolon)) Report(diag::empty_statement);
		std::vector<std::unique_ptr<DeclAST>> declarations;



		return declarations;
	}

}