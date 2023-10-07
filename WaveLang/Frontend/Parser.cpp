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
	//<parameter-declaration> ::= {<type-qualifier>}? <declarator> : <type-specifier>
	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDeclaration()
	{
		WAVE_ASSERT(ctx.sym_table->IsGlobal());
		SCOPED_SYMBOL_TABLE(ctx.sym_table);

		if (current_token->IsNot(TokenKind::identifier)) Report(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		Expect(TokenKind::left_round);
		std::unique_ptr<FunctionDeclAST> function_decl = std::make_unique<FunctionDeclAST>(identifier, current_token->GetLocation());
		QualifiedType function_type{};

		if (Consume(TokenKind::right_round))
		{
			if (Consume(TokenKind::minus))
			{
				Expect(TokenKind::greater);
				QualifiedType return_type{};
				ParseTypeSpecifier(return_type);
				function_type.SetRawType(FunctionType(return_type));
			}
			else function_type.SetRawType(FunctionType(builtin_types::Void));
		}
		else
		{
			std::vector<FunctionParameter> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Report(diag::function_params_missing_coma);

				QualifiedType param_type{};
				ParseTypeQualifier(param_type);

				if (current_token->IsNot(TokenKind::identifier)) Report(diag::expected_identifier);
				std::string_view identifier = current_token->GetIdentifier(); ++current_token;

				Expect(TokenKind::colon);
				ParseTypeSpecifier(param_type);
				if (!param_type.HasRawType()) Report(diag::missing_type_specifier);
				if (param_type->Is(TypeKind::Void)) Report(diag::void_invalid_context);

				std::unique_ptr<VariableDeclAST> param_decl = ParseVariableDeclaration(true);
				param_decl->SetType(param_type);
				function_decl->AddParamDeclaration(std::move(param_decl));

				param_types.emplace_back(std::string(identifier), param_type);
				ctx.sym_table->Insert(Symbol{ .name = std::string(identifier), .type = param_type });
			}

			QualifiedType return_type{};
			if (Consume(TokenKind::minus))
			{
				Expect(TokenKind::greater);
				ParseTypeSpecifier(return_type);
			}
			else return_type = builtin_types::Void;

			function_type.SetRawType(FunctionType(return_type, param_types));
		}

		function_decl->SetType(function_type);
		ctx.sym_table->Insert(Symbol{ .name = std::string(identifier), .type = function_type });

		return function_decl;
	}

	//<function_definition> ::= fn <identifier>( <parameter-list> )-> <type-specifier>  <compound_statement>
	//<parameter-list> ::= <parameter-declaration>
	//                   | <parameter-list>, <parameter-declaration>
	//<parameter-declaration> ::= <type-qualifier> <declarator> : <type-specifier>
	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDefinition()
	{
		std::unique_ptr<FunctionDeclAST> function_decl = ParseFunctionDeclaration();
		std::unique_ptr<CompoundStmtAST> function_body = ParseCompoundStatement();
		function_decl->SetDefinition(std::move(function_body));
		return function_decl;
	}

	//let a = 5;
	//let const a = 5;
	//let a : int = 5;
	//a : int
	//const a : int
	std::unique_ptr<VariableDeclAST> Parser::ParseVariableDeclaration(bool function_param_decl)
	{
		QualifiedType param_type{};
		ParseTypeQualifier(param_type);
		if (current_token->IsNot(TokenKind::identifier)) Report(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		if (function_param_decl)
		{
			Expect(TokenKind::colon);
			ParseTypeSpecifier(param_type);
			if (!param_type.HasRawType()) Report(diag::missing_type_specifier);
			if (param_type->Is(TypeKind::Void)) Report(diag::void_invalid_context);
		}
		else
		{
			if (Consume(TokenKind::colon)) ParseTypeSpecifier(param_type);
			
		}
		std::unique_ptr<VariableDeclAST> variable_decl = std::make_unique<VariableDeclAST>(identifier, current_token->GetLocation());
		variable_decl->SetType(param_type);
		


		return variable_decl;
	}

	std::unique_ptr<StmtAST> Parser::ParseStatement()
	{
		return nullptr;
	}

	std::unique_ptr<CompoundStmtAST> Parser::ParseCompoundStatement()
	{
		Expect(TokenKind::left_brace);
		SCOPED_SYMBOL_TABLE(ctx.sym_table);
		std::unique_ptr<CompoundStmtAST> compound_stmt = std::make_unique<CompoundStmtAST>();
		while (current_token->IsNot(TokenKind::right_brace))
		{
			if (current_token->Is(TokenKind::KW_let))
			{
				std::unique_ptr<VariableDeclAST> decl = ParseVariableDeclaration(false);

				compound_stmt->AddStatement(std::make_unique<DeclStmtAST>(std::move(decl)));
			}
			else
			{
				std::unique_ptr<StmtAST> stmt = ParseStatement();
				compound_stmt->AddStatement(std::move(stmt));
			}
		}
		Expect(TokenKind::right_brace);
		return compound_stmt;
	}

	//<type-qualifier> ::= {const}?
	void Parser::ParseTypeQualifier(QualifiedType& type)
	{
		if (Consume(TokenKind::KW_const))
		{
			type.AddConst();
		}
	}

	//<type-specifier> ::= void
	//                   | bool  | bool [ {<constant-expression>}? ]
	//                   | char  | char [ {<constant-expression>}? ]
	//                   | int   | int  [ {<constant-expression>}? ]
	//                   | float | float[ {<constant-expression>}? ]
	//                   | <enum-specifier> | <enum-specifier>[ {<constant-expression>}? ]
	//                   | <class-specifier> | <class-specifier>[ {<constant-expression>}? ]
	void Parser::ParseTypeSpecifier(QualifiedType& type)
	{
		switch (current_token->GetKind())
		{
		case TokenKind::KW_void:  type.SetRawType(builtin_types::Void); break;
		case TokenKind::KW_bool:  type.SetRawType(builtin_types::Bool);	break;
		case TokenKind::KW_char:  type.SetRawType(builtin_types::Char);	break;
		case TokenKind::KW_int:   type.SetRawType(builtin_types::Int); break;
		case TokenKind::KW_float: type.SetRawType(builtin_types::Float); break;
		case TokenKind::identifier:
		{
			std::string_view identifier = current_token->GetIdentifier();
			WAVE_ASSERT(false); //#todo : check if it's enum or class
		}
		break;
		default:
			Report(diag::invalid_type_specifier);
			return;
		}

		while (Consume(TokenKind::left_square))
		{
			if (type->Is(TypeKind::Void))
			{
				Report(diag::invalid_type_specifier);
				return;
			}

			if (Consume(TokenKind::right_square))
			{
				ArrayType array_type(type);
				type.SetRawType(array_type);
			}
			else
			{
				//#todo parse constant-expression
				Expect(TokenKind::right_square);
			}
		}
	}

}