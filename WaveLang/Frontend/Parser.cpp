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

	//<translation-unit> ::= { <function_definition> | <function_declaration> }*
	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof))
		{
			std::vector<std::unique_ptr<DeclAST>> declarations = ParseGlobalDeclaration();
			for (auto&& declaration : declarations) ast->translation_unit->AddDeclaration(std::move(declaration));
		}
	}

	std::vector<std::unique_ptr<DeclAST>> Parser::ParseGlobalDeclaration()
	{
		while (Consume(TokenKind::semicolon)) Report(diag::empty_statement);
		std::vector<std::unique_ptr<DeclAST>> declarations;
		if (Consume(TokenKind::KW_extern))
		{
			if (!Consume(TokenKind::KW_fn)) Report(diag::missing_fn);
			declarations.push_back(ParseFunctionDeclaration());
		}
		else if (Consume(TokenKind::KW_fn))
		{
			declarations.push_back(ParseFunctionDefinition());
		}
		else
		{
			Report(diag::missing_fn);
		}
		return declarations;
	}

	//<function_declaration> ::= extern fn <identifier>( <parameter-list> ) -> <type-specifier>};
	//<parameter-list> ::= <parameter-declaration>
	//                   | <parameter-list>, <parameter-declaration>
	//<parameter-declaration> ::= <type-qualifier> <declarator> : <type-specifier>
	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDeclaration()
	{
		WAVE_ASSERT(ctx.sym_table->IsGlobal());
		ctx.sym_table->EnterScope();

		if (current_token->IsNot(TokenKind::identifier)) Report(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		Expect(TokenKind::left_round);
		std::unique_ptr<FunctionDeclAST> function_decl = std::make_unique<FunctionDeclAST>(identifier, current_token->GetLocation());
		std::unique_ptr<FunctionType> function_type = nullptr;
		if (Consume(TokenKind::right_round))
		{
			Expect(TokenKind::minus);
			Expect(TokenKind::greater);
			std::unique_ptr<Type> type = ParseTypeSpecifier();
			function_type = std::make_unique<FunctionType>(std::move(type));
		}
		else
		{
			std::vector<FunctionParameter> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Report(diag::function_params_missing_coma);
			}
		}
	}

	//<function_definition> ::= fn <identifier>( <parameter-list> )-> <type-specifier>  <compound_statement>
	//<parameter-list> ::= <parameter-declaration>
	//                   | <parameter-list>, <parameter-declaration>
	//<parameter-declaration> ::= <type-qualifier> <declarator> : <type-specifier>
	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDefinition()
	{
		WAVE_ASSERT(ctx.sym_table->IsGlobal());
		ctx.sym_table->EnterScope();

		if (current_token->IsNot(TokenKind::identifier)) Report(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		Expect(TokenKind::left_round);
		std::unique_ptr<FunctionDeclAST> function_decl = std::make_unique<FunctionDeclAST>(identifier, current_token->GetLocation());
		std::unique_ptr<FunctionType> function_type = nullptr;
		if (Consume(TokenKind::right_round))
		{
			Expect(TokenKind::minus);
			Expect(TokenKind::greater);
			std::unique_ptr<Type> type = ParseTypeSpecifier();
			function_type = std::make_unique<FunctionType>(std::move(type));
		}
		else
		{
			std::vector<FunctionParameter> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Report(diag::function_params_missing_coma);
			}
		}
	}

	//<type-specifier> ::= void
	//                   | bool  | bool [ {<constant-expression>}? ]
	//                   | char  | char [ {<constant-expression>}? ]
	//                   | int   | int  [ {<constant-expression>}? ]
	//                   | float | float[ {<constant-expression>}? ]
	//                   | <enum-specifier> | <enum-specifier>[ {<constant-expression>}? ]
	//                   | <class-specifier> | <class-specifier>[ {<constant-expression>}? ]
	std::unique_ptr<Type> Parser::ParseTypeSpecifier()
	{
		std::unique_ptr<Type> type = nullptr;
		switch (current_token->GetKind())
		{
		case TokenKind::KW_void:  type = std::make_unique<VoidType>();
		case TokenKind::KW_bool:  type = std::make_unique<BoolType>();
		case TokenKind::KW_char:  type = std::make_unique<CharType>();
		case TokenKind::KW_int:   type = std::make_unique<IntType>();
		case TokenKind::KW_float: type = std::make_unique<FloatType>();
		case TokenKind::identifier:
		{
			std::string_view identifier = current_token->GetIdentifier();
			WAVE_ASSERT(false); //#todo : check if it's enum or class
		}
		default:
			Report(diag::invalid_type_specifier);
			return nullptr;
		}
		
		if (Consume(TokenKind::left_square))
		{
			if (type->Is(TypeKind::Void))
			{
				Report(diag::invalid_type_specifier);
				return nullptr;
			}

			if (Consume(TokenKind::right_square))
			{
				return std::make_unique<ArrayType>(*type);
			}
			else
			{
				//#todo parse constant-expression
			}
		}
		else return type;
	}

}