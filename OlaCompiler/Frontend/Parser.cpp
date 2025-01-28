#include "Parser.h"
#include "Diagnostics.h"
#include "AST/AST.h"
#include "Sema.h"

namespace ola
{

	Parser::Parser(FrontendContext* context, Diagnostics& diagnostics) : context(context), diagnostics(diagnostics) {}
	Parser::~Parser() = default;

	void Parser::Parse(std::vector<Token>&& _tokens)
	{
		tokens = std::move(_tokens);
		current_token = tokens.begin();
		sema = MakeUnique<Sema>(context, diagnostics);
		ast = MakeUnique<AST>();
		AddBuiltinDecls(ast->translation_unit);
		ParseTranslationUnit();
	}

	void Parser::ParseImported(std::vector<Token> const& _tokens)
	{
		tokens = _tokens;
		current_token = tokens.begin();
		sema = MakeUnique<Sema>(context, diagnostics);
		ast = MakeUnique<AST>();
		ParseTranslationUnit();
	}

	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof))
		{
			UniqueDeclPtrList decls = ParseGlobalDeclaration();
			for(auto&& decl : decls) ast->translation_unit->AddDecl(std::move(decl));
		}
	}

	void Parser::AddBuiltinDecls(UniqueTranslationUnitPtr& TU)
	{
		UniqueAliasDeclPtr string_alias = sema->ActOnAliasDecl("string", SourceLocation{}, ArrayType::Get(context, CharType::Get(context), 0));
		TU->AddDecl(std::move(string_alias));
	}

	UniqueDeclPtrList Parser::ParseGlobalDeclaration()
	{
		UniqueDeclPtrList global_decl_list;
		while (Consume(TokenKind::semicolon)) Diag(empty_statement);
		if (Consume(TokenKind::KW_extern))
		{
			if (IsFunctionDeclaration()) global_decl_list.push_back(ParseFunctionDeclaration());
			else global_decl_list = ParseExternVariableDeclaration();
		}
		else
		{
			DeclVisibility visibility = DeclVisibility::Private;
			if (Consume(TokenKind::KW_public)) visibility = DeclVisibility::Public;
			else if (Consume(TokenKind::KW_private)) visibility = DeclVisibility::Private;

			if (Consume(TokenKind::KW_class))
			{
				global_decl_list.push_back(ParseClassDeclaration());
			}
			else if (Consume(TokenKind::KW_enum))
			{
				global_decl_list.push_back(ParseEnumDeclaration());
			}
			else if (Consume(TokenKind::KW_alias))
			{
				global_decl_list.push_back(ParseAliasDeclaration());
			}
			else
			{
				if (IsFunctionDeclaration())
				{
					global_decl_list.push_back(ParseFunctionDefinition(visibility));
				}
				else
				{
					UniqueVarDeclPtrList variable_decls = ParseVariableDeclaration(visibility);
					for (auto& variable_decl : variable_decls) global_decl_list.push_back(std::move(variable_decl));
				}
			}
			global_decl_list.back()->SetVisibility(visibility);
		}

		return global_decl_list;
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDeclaration()
	{
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		FuncAttributes attrs = FuncAttribute_None;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			ParseFunctionAttributes(attrs);
			QualType return_type{};
			ParseTypeQualifier(return_type);
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);

			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);

			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			Expect(TokenKind::semicolon, function_def_cannot_be_extern);
		}
		return sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls), DeclVisibility::Extern, attrs);
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDefinition(DeclVisibility visibility)
	{
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		UniqueCompoundStmtPtr function_body;
		FuncAttributes attrs = FuncAttribute_None;
		UniqueFunctionDeclPtr func_decl = nullptr;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			ParseFunctionAttributes(attrs);
			QualType return_type{};
			ParseTypeQualifier(return_type);
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);

			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			func_decl = sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls), visibility, attrs);
			if (Consume(TokenKind::semicolon))
			{
				Diag(function_decl_needs_to_be_extern);
				return nullptr;
			}
			sema->sema_ctx.current_func = &function_type;
			function_body = ParseCompoundStatement();
			sema->sema_ctx.current_func = nullptr;
		}
		return sema->ActOnFunctionDefinition(loc, std::move(func_decl), std::move(function_body));
	}

	UniqueMethodDeclPtr Parser::ParseMethodDefinition(Bool first_pass)
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public)) visibility = DeclVisibility::Public;
		else if (Consume(TokenKind::KW_private)) visibility = DeclVisibility::Private;

		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		UniqueCompoundStmtPtr function_body;
		FuncAttributes func_attrs = FuncAttribute_None;
		MethodAttributes method_attrs = MethodAttribute_None;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			ParseFunctionAttributes(func_attrs);
			QualType return_type{};
			ParseTypeQualifier(return_type);
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);
			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			ParseMethodAttributes(method_attrs);
			if (first_pass)
			{
				if (Consume(TokenKind::semicolon)) return nullptr;

				Int32 brace_count = 0;
				Expect(TokenKind::left_brace); ++brace_count;
				while (brace_count != 0)
				{
					if (Consume(TokenKind::left_brace))  ++brace_count;
					else if (Consume(TokenKind::right_brace)) --brace_count;
					else current_token++;
				}
			}
			else
			{
				if (!Consume(TokenKind::semicolon))
				{
					sema->sema_ctx.current_func = &function_type;
					sema->sema_ctx.is_method_const = HasAttribute(method_attrs, MethodAttribute_Const);
					function_body = ParseCompoundStatement();
					sema->sema_ctx.is_method_const = false;
					sema->sema_ctx.current_func = nullptr;
				}
			}
		}
		return first_pass ? nullptr : sema->ActOnMethodDecl(name, loc, function_type, std::move(param_decls), std::move(function_body), visibility, func_attrs, method_attrs);
	}

	UniqueConstructorDeclPtr Parser::ParseConstructorDefinition(Bool first_pass)
	{
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		UniqueCompoundStmtPtr constructor_body;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);
			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, VoidType::Get(context), param_types));
			if (first_pass)
			{
				if (Consume(TokenKind::semicolon)) return nullptr;

				Int32 brace_count = 0;
				Expect(TokenKind::left_brace); ++brace_count;
				while (brace_count != 0)
				{
					if (Consume(TokenKind::left_brace))  ++brace_count;
					else if (Consume(TokenKind::right_brace)) --brace_count;
					else current_token++;
				}
			}
			else
			{
				if (!Consume(TokenKind::semicolon))
				{
					sema->sema_ctx.current_func = &function_type;
					sema->sema_ctx.is_constructor = true;
					constructor_body = ParseCompoundStatement();
					sema->sema_ctx.is_constructor = false;
					sema->sema_ctx.current_func = nullptr;
				}
			}
		}
		return first_pass ? nullptr : sema->ActOnConstructorDecl(name, loc, function_type, std::move(param_decls), std::move(constructor_body));
	}

	UniqueParamVarDeclPtr Parser::ParseParamVariableDeclaration()
	{
		QualType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);

		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		if (current_token->Is(TokenKind::identifier))
		{
			name = current_token->GetData(); 
			++current_token;
		}

		return sema->ActOnParamVariableDecl(name, loc, variable_type);
	}

	UniqueVarDeclPtrList Parser::ParseVariableDeclaration(DeclVisibility visibility)
	{
		UniqueVarDeclPtrList var_decl_list;
		QualType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do
		{
			if (!var_decl_list.empty()) Expect(TokenKind::comma);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueExprPtr init_expr = nullptr;
			if (Consume(TokenKind::equal))
			{
				if (current_token->Is(TokenKind::left_brace)) init_expr = ParseInitializerListExpression();
				else init_expr = ParseAssignmentExpression();
			}
			else if (Consume(TokenKind::left_round))
			{
				UniqueExprPtrList args;
				if (!Consume(TokenKind::right_round))
				{
					while (true)
					{
						UniqueExprPtr arg_expr = ParseAssignmentExpression();
						args.push_back(std::move(arg_expr));
						if (Consume(TokenKind::right_round)) break;
						Expect(TokenKind::comma);
					}
				}
				init_expr = sema->ActOnConstructorExpr(loc, variable_type, std::move(args));
			}

			UniqueVarDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, std::move(init_expr), visibility);
			var_decl_list.push_back(std::move(var_decl));

		} while (!Consume(TokenKind::semicolon));

		return var_decl_list;
	}

	UniqueFieldDeclPtrList Parser::ParseFieldDeclaration(Bool first_pass)
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public)) visibility = DeclVisibility::Public;
		else if (Consume(TokenKind::KW_private)) visibility = DeclVisibility::Private;

		UniqueFieldDeclPtrList member_var_decl_list;
		QualType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do
		{
			if (!member_var_decl_list.empty()) Expect(TokenKind::comma);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueExprPtr init_expr = nullptr;
			if (Consume(TokenKind::equal))
			{
				if (current_token->Is(TokenKind::left_brace)) init_expr = ParseInitializerListExpression();
				else init_expr = ParseAssignmentExpression();
			}
			if (first_pass)
			{
				UniqueFieldDeclPtr var_decl = sema->ActOnFieldDecl(name, loc, variable_type, std::move(init_expr), visibility);
				member_var_decl_list.push_back(std::move(var_decl));
			}
		} while (!Consume(TokenKind::semicolon));

		return member_var_decl_list;
	}

	UniqueDeclPtrList Parser::ParseExternVariableDeclaration()
	{
		UniqueDeclPtrList var_decl_list;
		QualType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do
		{
			if (!var_decl_list.empty()) Expect(TokenKind::comma);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueVarDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, nullptr, DeclVisibility::Extern);
			var_decl_list.push_back(std::move(var_decl));

		} while (!Consume(TokenKind::semicolon));

		return var_decl_list;
	}

	UniqueEnumDeclPtr Parser::ParseEnumDeclaration()
	{
		std::string enum_tag = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->Is(TokenKind::identifier))
		{
			enum_tag = current_token->GetData();
			++current_token;
		}

		UniqueEnumMemberDeclPtrList enum_members;
		Expect(TokenKind::left_brace);
		Int64 val = 0;
		while (true)
		{
			std::string enum_value_name;
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation loc = current_token->GetLocation();
			enum_value_name = current_token->GetData(); ++current_token;

			if (Consume(TokenKind::equal))
			{
				UniqueExprPtr enum_value_expr = ParseAssignmentExpression();
				enum_members.push_back(sema->ActOnEnumMemberDecl(enum_value_name, loc, std::move(enum_value_expr)));
				val = enum_members.back()->GetValue() + 1;
			}
			else
			{
				enum_members.push_back(sema->ActOnEnumMemberDecl(enum_value_name, loc, val++));
			}

			if (Consume(TokenKind::right_brace)) break;
			Expect(TokenKind::comma);
		}
		Expect(TokenKind::semicolon);

		return sema->ActOnEnumDecl(enum_tag, loc, std::move(enum_members));
	}

	UniqueAliasDeclPtr Parser::ParseAliasDeclaration()
	{
		std::string alias_name = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
		alias_name = current_token->GetData();
		++current_token;

		Expect(TokenKind::equal);

		QualType aliased_type{};
		ParseTypeQualifier(aliased_type);
		ParseTypeSpecifier(aliased_type);
		Expect(TokenKind::semicolon);

		return sema->ActOnAliasDecl(alias_name, loc, aliased_type);
	}

	UniqueClassDeclPtr Parser::ParseClassDeclaration()
	{
		std::string class_name = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->Is(TokenKind::identifier))
		{
			class_name = current_token->GetData();
			++current_token;
		}
		else Expect(TokenKind::identifier);
		
		Bool const final = Consume(TokenKind::KW_final);
		ClassDecl const* base_class = nullptr;
		if (Consume(TokenKind::colon))
		{
			std::string base_class_name = "";
			if (current_token->Is(TokenKind::identifier))
			{
				base_class_name = current_token->GetData();
				if (base_class_name.empty())
				{
					Diag(expected_base_class_name);
					return nullptr;
				}
				++current_token;
			}
			else
			{
				Diag(expected_base_class_name);
				return nullptr;
			}
			base_class = sema->ActOnBaseClassSpecifier(base_class_name, current_token->GetLocation());
		}

		UniqueFieldDeclPtrList member_variables;
		UniqueMethodDeclPtrList member_functions;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);

			sema->sema_ctx.current_base_class = base_class;
			sema->sema_ctx.current_class_name = class_name;
			{
				auto ParseClassMembers = [&](Bool first_pass)
					{
						Expect(TokenKind::left_brace);
						while (!Consume(TokenKind::right_brace))
						{
							if (current_token->Is(TokenKind::identifier))
							{
								UniqueConstructorDeclPtr constructor = ParseConstructorDefinition(first_pass);
								if (!first_pass) member_functions.push_back(std::move(constructor));
								continue;
							}

							Bool is_function_declaration = IsFunctionDeclaration();
							if (is_function_declaration)
							{
								UniqueMethodDeclPtr member_function = ParseMethodDefinition(first_pass);
								if (!first_pass) member_functions.push_back(std::move(member_function));
							}
							else
							{
								UniqueFieldDeclPtrList var_decls = ParseFieldDeclaration(first_pass);
								if (first_pass) for (auto& var_decl : var_decls) member_variables.push_back(std::move(var_decl));
							}
						}
						Expect(TokenKind::semicolon);
					};

				TokenPtr start_token = current_token;
				ParseClassMembers(true);
				current_token = start_token;
				ParseClassMembers(false);
			}
			sema->sema_ctx.current_class_name = "";
			sema->sema_ctx.current_base_class = nullptr;
		}
		return sema->ActOnClassDecl(class_name, base_class, loc, std::move(member_variables), std::move(member_functions), final);
	}

	UniqueStmtPtr Parser::ParseStatement()
	{
		switch (current_token->GetKind())
		{
		case TokenKind::left_brace: return ParseCompoundStatement();
		case TokenKind::KW_return: return ParseReturnStatement();
		case TokenKind::KW_if: return ParseIfStatement();
		case TokenKind::KW_continue: return ParseContinueStatement();
		case TokenKind::KW_break: return ParseBreakStatement();
		case TokenKind::KW_for: return ParseForStatement();
		case TokenKind::KW_foreach: return ParseForeachStatement();
		case TokenKind::KW_while: return ParseWhileStatement();
		case TokenKind::KW_do: return ParseDoWhileStatement();
		case TokenKind::KW_switch: return ParseSwitchStatement();
		case TokenKind::KW_case:
		case TokenKind::KW_default: return ParseCaseStatement();
		case TokenKind::KW_goto: return ParseGotoStatement();
		case TokenKind::identifier:
			if ((current_token + 1)->Is(TokenKind::colon)) return ParseLabelStatement();
			return ParseExpressionStatement();
		default:
			return ParseExpressionStatement();
		}
		return nullptr;
	}

	UniqueCompoundStmtPtr Parser::ParseCompoundStatement()
	{
		SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
		SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);
		Expect(TokenKind::left_brace);
		UniqueStmtPtrList stmts;
		while (current_token->IsNot(TokenKind::right_brace))
		{
			if (IsCurrentTokenTypename())
			{
				if (Consume(TokenKind::KW_enum))
				{
					UniqueEnumDeclPtr enum_decl = ParseEnumDeclaration();
					stmts.push_back(sema->ActOnDeclStmt(std::move(enum_decl)));
				}
				else if (Consume(TokenKind::KW_alias))
				{
					UniqueAliasDeclPtr alias_decl = ParseAliasDeclaration();
					stmts.push_back(sema->ActOnDeclStmt(std::move(alias_decl)));
				}
				else
				{
					UniqueVarDeclPtrList variable_decls = ParseVariableDeclaration(DeclVisibility::None);
					for (auto& variable_decl : variable_decls) stmts.push_back(sema->ActOnDeclStmt(std::move(variable_decl)));
				}
			}
			else
			{
				UniqueStmtPtr stmt = ParseStatement();
				stmts.push_back(std::move(stmt));
			}
		}
		Expect(TokenKind::right_brace);
		return sema->ActOnCompoundStmt(std::move(stmts));
	}

	UniqueExprStmtPtr Parser::ParseExpressionStatement()
	{
		if (Consume(TokenKind::semicolon)) return MakeUnique<NullStmt>();
		UniqueExprPtr expr = ParseExpression();
		Expect(TokenKind::semicolon);
		return sema->ActOnExprStmt(std::move(expr));
	}

	UniqueReturnStmtPtr Parser::ParseReturnStatement()
	{
		Expect(TokenKind::KW_return);
		UniqueExprStmtPtr ret_expr_stmt = ParseExpressionStatement();
		return sema->ActOnReturnStmt(std::move(ret_expr_stmt));
	}

	UniqueIfStmtPtr Parser::ParseIfStatement()
	{
		Expect(TokenKind::KW_if);
		UniqueExprPtr cond_expr = ParseParenthesizedExpression();
		UniqueStmtPtr then_stmt = ParseStatement();
		UniqueStmtPtr else_stmt = nullptr;
		if (Consume(TokenKind::KW_else)) else_stmt = ParseStatement();
		
		return sema->ActOnIfStmt(std::move(cond_expr), std::move(then_stmt), std::move(else_stmt));
	}

	UniqueBreakStmtPtr Parser::ParseBreakStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::KW_break);
		Expect(TokenKind::semicolon);
		return sema->ActOnBreakStmt(loc);
	}

	UniqueContinueStmtPtr Parser::ParseContinueStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::KW_continue);
		Expect(TokenKind::semicolon);
		return sema->ActOnContinueStmt(loc);
	}

	UniqueForStmtPtr Parser::ParseForStatement()
	{
		Expect(TokenKind::KW_for);
		Expect(TokenKind::left_round);

		SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
		UniqueStmtPtr init_stmt = nullptr;
		if (current_token->IsTypename())
		{
			UniqueVarDeclPtrList variable_decls = ParseVariableDeclaration(DeclVisibility::None);
			UniqueDeclPtrList decl_list; decl_list.reserve(variable_decls.size());
			for (auto& variable_decl : variable_decls) decl_list.push_back(std::move(variable_decl));
			init_stmt = MakeUnique<DeclStmt>(std::move(decl_list));
		}
		else init_stmt = ParseExpressionStatement();

		UniqueExprPtr cond_expr = nullptr;
		if (!Consume(TokenKind::semicolon))
		{
			cond_expr = ParseExpression();
			Expect(TokenKind::semicolon);
		}

		UniqueExprPtr iter_expr = nullptr;
		if (!Consume(TokenKind::right_round))
		{
			iter_expr = ParseExpression();
			Expect(TokenKind::right_round);
		}

		sema->sema_ctx.stmts_using_break_count++;
		sema->sema_ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->sema_ctx.stmts_using_continue_count--;
		sema->sema_ctx.stmts_using_break_count--;

		return sema->ActOnForStmt(std::move(init_stmt), std::move(cond_expr), std::move(iter_expr), std::move(body_stmt));
	}

	UniqueForStmtPtr Parser::ParseForeachStatement()
	{
		Expect(TokenKind::KW_foreach);
		Expect(TokenKind::left_round);
		SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
		SourceLocation loc = current_token->GetLocation();

		UniqueVarDeclPtr var_decl;
		{
			QualType variable_type{};
			ParseTypeQualifier(variable_type);
			ParseTypeSpecifier(variable_type);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = "";
			if (current_token->Is(TokenKind::identifier))
			{
				name = current_token->GetData();
				++current_token;
			}
			else Diag(expected_identifier);
			var_decl = sema->ActOnVariableDecl(name, loc, variable_type, nullptr, DeclVisibility::None);
		}
		Expect(TokenKind::colon);
		UniqueExprPtr array_expr = ParseIdentifier();
		Expect(TokenKind::right_round);
		
		sema->sema_ctx.stmts_using_break_count++;
		sema->sema_ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->sema_ctx.stmts_using_continue_count--;
		sema->sema_ctx.stmts_using_break_count--;
		
		return sema->ActOnForeachStmt(loc, std::move(var_decl), std::move(array_expr), std::move(body_stmt));
		return nullptr;
	}

	UniqueWhileStmtPtr Parser::ParseWhileStatement()
	{
		Expect(TokenKind::KW_while);
		UniqueExprPtr cond_expr = ParseParenthesizedExpression();
		sema->sema_ctx.stmts_using_break_count++;
		sema->sema_ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->sema_ctx.stmts_using_continue_count--;
		sema->sema_ctx.stmts_using_break_count--;
		return sema->ActOnWhileStmt(std::move(cond_expr), std::move(body_stmt));
	}

	UniqueDoWhileStmtPtr Parser::ParseDoWhileStatement()
	{
		Expect(TokenKind::KW_do);
		sema->sema_ctx.stmts_using_break_count++;
		sema->sema_ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->sema_ctx.stmts_using_continue_count--;
		sema->sema_ctx.stmts_using_break_count--;
		Expect(TokenKind::KW_while);
		UniqueExprPtr cond_expr = ParseParenthesizedExpression();
		Expect(TokenKind::semicolon);
		return sema->ActOnDoWhileStmt(std::move(cond_expr), std::move(body_stmt));
	}

	UniqueCaseStmtPtr Parser::ParseCaseStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		UniqueExprPtr case_value = nullptr;
		if (Consume(TokenKind::KW_case)) case_value = ParseExpression();
		else Expect(TokenKind::KW_default);
		Expect(TokenKind::colon);
		return sema->ActOnCaseStmt(loc, std::move(case_value));
	}

	UniqueSwitchStmtPtr Parser::ParseSwitchStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::KW_switch);
		UniqueExprPtr case_expr = ParseParenthesizedExpression();
		std::vector<CaseStmt*> case_stmts{};
		sema->sema_ctx.case_callback_stack.push_back([&](CaseStmt* case_stmt) {case_stmts.push_back(case_stmt); });
		sema->sema_ctx.stmts_using_break_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->sema_ctx.stmts_using_break_count--;
		sema->sema_ctx.case_callback_stack.pop_back();
		return sema->ActOnSwitchStmt(loc, std::move(case_expr), std::move(body_stmt), std::move(case_stmts));
	}

	UniqueGotoStmtPtr Parser::ParseGotoStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::KW_goto);
		std::string_view label_name = current_token->GetData();
		Expect(TokenKind::identifier);
		Expect(TokenKind::semicolon);
		return sema->ActOnGotoStmt(loc, label_name);
	}

	UniqueLabelStmtPtr Parser::ParseLabelStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		std::string_view label_name = current_token->GetData();
		Expect(TokenKind::identifier);
		Expect(TokenKind::colon);
		return sema->ActOnLabelStmt(loc, label_name);
	}

	template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
	UniqueExprPtr Parser::ParseBinaryExpression()
	{
		UniqueExprPtr lhs = (this->*ParseFn)();
		while (Consume(token_kind))
		{
			SourceLocation loc = current_token->GetLocation();
			UniqueExprPtr rhs = (this->*ParseFn)();

			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs)); 
			lhs = std::move(parent);
		}
		return lhs;
	}

	UniqueExprPtr Parser::ParseExpression()
	{
		return ParseBinaryExpression<&Parser::ParseAssignmentExpression, TokenKind::comma, BinaryExprKind::Comma>();
	}

	UniqueExprPtr Parser::ParseParenthesizedExpression()
	{
		Expect(TokenKind::left_round);
		UniqueExprPtr expr = ParseExpression();
		Expect(TokenKind::right_round);
		return expr;
	}

	UniqueExprPtr Parser::ParseAssignmentExpression()
	{
		TokenPtr current_token_copy = current_token;
		UniqueExprPtr lhs = ParseConditionalExpression();
		BinaryExprKind arith_op_kind = BinaryExprKind::Assign;
		SourceLocation loc = current_token->GetLocation();
		switch (current_token->GetKind())
		{
		case TokenKind::equal:					arith_op_kind = BinaryExprKind::Assign; break;
		case TokenKind::star_equal:				arith_op_kind = BinaryExprKind::Multiply; break;
		case TokenKind::slash_equal:			arith_op_kind = BinaryExprKind::Divide; break;
		case TokenKind::modulo_equal:			arith_op_kind = BinaryExprKind::Modulo; break;
		case TokenKind::plus_equal:				arith_op_kind = BinaryExprKind::Add; break;
		case TokenKind::minus_equal:			arith_op_kind = BinaryExprKind::Subtract; break;
		case TokenKind::less_less_equal:		arith_op_kind = BinaryExprKind::ShiftLeft; break;
		case TokenKind::greater_greater_equal:	arith_op_kind = BinaryExprKind::ShiftRight; break;
		case TokenKind::amp_equal:				arith_op_kind = BinaryExprKind::BitAnd; break;
		case TokenKind::pipe_equal:				arith_op_kind = BinaryExprKind::BitOr; break;
		case TokenKind::caret_equal:			arith_op_kind = BinaryExprKind::BitXor; break;
		default:
			return lhs;
		}
		++current_token;
		UniqueExprPtr rhs = ParseAssignmentExpression();
		if (arith_op_kind != BinaryExprKind::Assign)
		{
			TokenPtr current_token_copy2 = current_token;
			current_token = current_token_copy;
			UniqueExprPtr lhs_copy = ParseConditionalExpression();
			current_token = current_token_copy2;

			UniqueBinaryExprPtr tmp = sema->ActOnBinaryExpr(arith_op_kind, loc, std::move(lhs_copy), std::move(rhs)); 
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(BinaryExprKind::Assign, loc, std::move(lhs), std::move(tmp));
			return parent;
		}
		else
		{
			return sema->ActOnBinaryExpr(arith_op_kind, loc, std::move(lhs), std::move(rhs));
		}
	}

	UniqueExprPtr Parser::ParseConditionalExpression()
	{
		SourceLocation loc = current_token->GetLocation();
		UniqueExprPtr cond = ParseLogicalOrExpression();
		if (Consume(TokenKind::question))
		{
			UniqueExprPtr true_expr = ParseExpression();
			Expect(TokenKind::colon);
			UniqueExprPtr false_expr = ParseConditionalExpression();
			return sema->ActOnTernaryExpr(loc, std::move(cond), std::move(true_expr), std::move(false_expr));
		}
		return cond;
	}

	UniqueExprPtr Parser::ParseLogicalOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseLogicalAndExpression, TokenKind::pipe_pipe, BinaryExprKind::LogicalOr>();
	}

	UniqueExprPtr Parser::ParseLogicalAndExpression()
	{
		return ParseBinaryExpression<&Parser::ParseInclusiveOrExpression, TokenKind::amp_amp, BinaryExprKind::LogicalAnd>();
	}

	UniqueExprPtr Parser::ParseInclusiveOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseExclusiveOrExpression, TokenKind::pipe, BinaryExprKind::BitOr>();
	}

	UniqueExprPtr Parser::ParseExclusiveOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseAndExpression, TokenKind::caret, BinaryExprKind::BitXor>();
	}

	UniqueExprPtr Parser::ParseAndExpression()
	{
		return ParseBinaryExpression<&Parser::ParseEqualityExpression, TokenKind::amp, BinaryExprKind::BitAnd>();
	}

	UniqueExprPtr Parser::ParseEqualityExpression()
	{
		UniqueExprPtr lhs = ParseRelationalExpression();
		while (true)
		{
			BinaryExprKind op_kind = BinaryExprKind::Invalid;
			SourceLocation loc = current_token->GetLocation();
			switch (current_token->GetKind())
			{
			case TokenKind::equal_equal: op_kind = BinaryExprKind::Equal; break;
			case TokenKind::not_equal:	 op_kind = BinaryExprKind::NotEqual; break;
			default:
				return lhs;
			}
			++current_token;
			UniqueExprPtr rhs = ParseRelationalExpression();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseRelationalExpression()
	{
		UniqueExprPtr lhs = ParseShiftExpression();
		while (true)
		{
			BinaryExprKind op_kind = BinaryExprKind::Invalid;
			SourceLocation loc = current_token->GetLocation();
			switch (current_token->GetKind())
			{
			case TokenKind::less:			op_kind = BinaryExprKind::Less; break;
			case TokenKind::less_equal:		op_kind = BinaryExprKind::LessEqual; break;
			case TokenKind::greater:		op_kind = BinaryExprKind::Greater; break;
			case TokenKind::greater_equal:	op_kind = BinaryExprKind::GreaterEqual; break;
			default:
				return lhs;
			}
			++current_token;
			UniqueExprPtr rhs = ParseShiftExpression();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseShiftExpression()
	{
		UniqueExprPtr lhs = ParseAdditiveExpression();
		while (true)
		{
			BinaryExprKind op_kind = BinaryExprKind::Invalid;
			SourceLocation loc = current_token->GetLocation();
			switch (current_token->GetKind())
			{
			case TokenKind::less_less:			op_kind = BinaryExprKind::ShiftLeft; break;
			case TokenKind::greater_greater:	op_kind = BinaryExprKind::ShiftRight; break;
			default:
				return lhs;
			}
			++current_token;
			UniqueExprPtr rhs = ParseAdditiveExpression();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseAdditiveExpression()
	{
		UniqueExprPtr lhs = ParseMultiplicativeExpression();
		while (true)
		{
			BinaryExprKind op_kind = BinaryExprKind::Invalid;
			SourceLocation loc = current_token->GetLocation();
			switch (current_token->GetKind())
			{
			case TokenKind::plus:			op_kind = BinaryExprKind::Add; break;
			case TokenKind::minus:			op_kind = BinaryExprKind::Subtract; break;
			default:
				return lhs;
			}
			++current_token;
			UniqueExprPtr rhs = ParseMultiplicativeExpression();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseMultiplicativeExpression()
	{
		UniqueExprPtr lhs = ParseUnaryExpression();
		while (true)
		{
			BinaryExprKind op_kind = BinaryExprKind::Invalid;
			SourceLocation loc = current_token->GetLocation();
			switch (current_token->GetKind())
			{
			case TokenKind::star:	op_kind = BinaryExprKind::Multiply; break;
			case TokenKind::slash:	op_kind = BinaryExprKind::Divide; break;
			case TokenKind::modulo: op_kind = BinaryExprKind::Modulo; break;
			default:
				return lhs;
			}
			++current_token;
			UniqueExprPtr rhs = ParseUnaryExpression();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(op_kind, loc, std::move(lhs), std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseUnaryExpression()
	{
		UniqueUnaryExprPtr unary_expr;
		SourceLocation loc = current_token->GetLocation();
		UnaryExprKind unary_kind = UnaryExprKind::Plus;
		switch (current_token->GetKind())
		{
		case TokenKind::plus_plus:
			unary_kind = UnaryExprKind::PreIncrement;
			break;
		case TokenKind::minus_minus:
			unary_kind = UnaryExprKind::PreDecrement;
			break;
		case TokenKind::plus:
			unary_kind = UnaryExprKind::Plus;
			break;
		case TokenKind::minus:
			unary_kind = UnaryExprKind::Minus;
			break;
		case TokenKind::tilde:
			unary_kind = UnaryExprKind::BitNot;
			break;
		case TokenKind::exclaim:
			unary_kind = UnaryExprKind::LogicalNot;
			break;
		case TokenKind::KW_sizeof: return ParseSizeofExpression();
		case TokenKind::KW_length: return ParseLengthExpression();
		default:
			return ParsePostFixExpression();
		}
		++current_token;
		UniqueExprPtr operand = ParseUnaryExpression();
		return sema->ActOnUnaryExpr(unary_kind, loc, std::move(operand));
	}

	UniqueExprPtr Parser::ParsePostFixExpression()
	{
		UniqueExprPtr expr = ParsePrimaryExpression();
		SourceLocation loc = current_token->GetLocation();

		while (true)
		{
			switch (current_token->GetKind())
			{
			case TokenKind::left_round: 
			{
				++current_token;
				UniqueExprPtrList args;
				if (!Consume(TokenKind::right_round))
				{
					while (true)
					{
						UniqueExprPtr arg_expr = ParseAssignmentExpression();
						args.push_back(std::move(arg_expr));
						if (Consume(TokenKind::right_round)) break;
						Expect(TokenKind::comma);
					}
				}
				expr = sema->ActOnCallExpr(loc, std::move(expr), std::move(args));
			}
			break;
			case TokenKind::plus_plus:
			{
				++current_token;
				expr = sema->ActOnUnaryExpr(UnaryExprKind::PostIncrement, loc, std::move(expr));
			}
			break;
			case TokenKind::minus_minus:
			{
				++current_token;
				expr = sema->ActOnUnaryExpr(UnaryExprKind::PostDecrement, loc, std::move(expr));
			}
			break;
			case TokenKind::left_square:
			{
				++current_token;
				UniqueExprPtr index_expr = ParseExpression();
				Expect(TokenKind::right_square);
				expr = sema->ActOnArrayAccessExpr(loc, std::move(expr), std::move(index_expr));
			}
			break;
			case TokenKind::period:
			{
				++current_token;
				sema->sema_ctx.current_class_expr_stack.push_back(expr.get());
				UniqueIdentifierExprPtr member_identifier = ParseMemberIdentifier();
				sema->sema_ctx.current_class_expr_stack.pop_back();
				if (current_token->Is(TokenKind::left_round))
				{
					++current_token;
					UniqueExprPtrList args;
					if (!Consume(TokenKind::right_round))
					{
						while (true)
						{
							UniqueExprPtr arg_expr = ParseAssignmentExpression();
							args.push_back(std::move(arg_expr));
							if (Consume(TokenKind::right_round)) break;
							Expect(TokenKind::comma);
						}
					}
					expr = sema->ActOnMethodCall(loc, std::move(expr), std::move(member_identifier), std::move(args));
				}
				else
				{
					expr = sema->ActOnFieldAccess(loc, std::move(expr), std::move(member_identifier));
				}
			}
			break;
			default:
				return expr;
			}
		}

		return expr;
	}

	UniqueExprPtr Parser::ParsePrimaryExpression()
	{
		switch (current_token->GetKind())
		{
		case TokenKind::left_round: return ParseParenthesizedExpression();
		case TokenKind::identifier: return ParseIdentifier(); 
		case TokenKind::int_number: return ParseConstantInt();
		case TokenKind::float_number: return ParseConstantFloat();
		case TokenKind::char_literal: return ParseConstantChar();
		case TokenKind::string_literal: return ParseConstantString(); 
		case TokenKind::KW_true:
		case TokenKind::KW_false: return ParseConstantBool();
		case TokenKind::KW_this:  return ParseThisExpression();
		case TokenKind::KW_super:  return ParseSuperExpression();
		default:
			Diag(unexpected_token);
		}
		OLA_ASSERT(false);
		return nullptr;
	}

	UniqueIntLiteralPtr Parser::ParseSizeofExpression()
	{
		Expect(TokenKind::KW_sizeof);
		Expect(TokenKind::left_round);

		SourceLocation loc = current_token->GetLocation();
		QualType type{};
		std::string_view identifier = current_token->GetData();
		if (current_token->IsTypename() && current_token->IsNot(TokenKind::KW_auto)
		|| (current_token->Is(TokenKind::identifier) && sema->sema_ctx.tag_sym_table.LookUp(identifier) != nullptr))
		{
			ParseTypeQualifier(type);
			ParseTypeSpecifier(type);
		}
		else
		{
			UniqueExprPtr sizeof_expr = ParseUnaryExpression();
			type = sizeof_expr->GetType();
		}
		Expect(TokenKind::right_round);
		return sema->ActOnIntLiteral(type->GetSize(), loc);
	}

	UniqueIntLiteralPtr Parser::ParseLengthExpression()
	{
		Expect(TokenKind::KW_length);
		Expect(TokenKind::left_round);
		SourceLocation loc = current_token->GetLocation();
		UniqueExprPtr length_expr = ParseUnaryExpression();
		QualType const& type = length_expr->GetType();
		Expect(TokenKind::right_round);
		return sema->ActOnLengthOperator(type, loc);
	}

	UniqueIntLiteralPtr Parser::ParseConstantInt()
	{
		OLA_ASSERT(current_token->Is(TokenKind::int_number));
		std::string_view string_number = current_token->GetData();
		Int64 value = std::stoll(current_token->GetData().data(), nullptr, 0);
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnIntLiteral(value, loc);
	}

	UniqueCharLiteralPtr Parser::ParseConstantChar()
	{
		OLA_ASSERT(current_token->Is(TokenKind::char_literal));
		std::string_view char_string = current_token->GetData();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnCharLiteral(char_string, loc);
	}

	UniqueStringLiteralPtr Parser::ParseConstantString()
	{
		OLA_ASSERT(current_token->Is(TokenKind::string_literal));
		std::string_view str = current_token->GetData();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnStringLiteral(str, loc);
	}

	UniqueBoolLiteralPtr Parser::ParseConstantBool()
	{
		OLA_ASSERT(current_token->IsOneOf(TokenKind::KW_true, TokenKind::KW_false));
		Bool value = false;
		if (current_token->Is(TokenKind::KW_false)) value = false;
		else if (current_token->Is(TokenKind::KW_true)) value = true;
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnBoolLiteral(value, loc);
	}

	UniqueFloatLiteralPtr Parser::ParseConstantFloat()
	{
		OLA_ASSERT(current_token->Is(TokenKind::float_number));
		std::string_view string_number = current_token->GetData();
		Float64 value = std::stod(current_token->GetData().data(), nullptr);
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnFloatLiteral(value, loc);
	}

	UniqueExprPtr Parser::ParseIdentifier()
	{
		OLA_ASSERT(current_token->Is(TokenKind::identifier));
		std::string_view name = current_token->GetData();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnIdentifier(name, loc, current_token->Is(TokenKind::left_round));
	}

	UniqueThisExprPtr Parser::ParseThisExpression()
	{
		OLA_ASSERT(current_token->Is(TokenKind::KW_this));
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnThisExpr(loc, false);
	}

	UniqueSuperExprPtr Parser::ParseSuperExpression()
	{
		OLA_ASSERT(current_token->Is(TokenKind::KW_super));
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnSuperExpr(loc, false);
	}

	UniqueIdentifierExprPtr Parser::ParseMemberIdentifier()
	{
		std::string_view name = current_token->GetData();
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::identifier);
		return sema->ActOnMemberIdentifier(name, loc, current_token->Is(TokenKind::left_round));
	}

	UniqueInitializerListExprPtr Parser::ParseInitializerListExpression()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::left_brace);
		UniqueExprPtrList expr_list;
		if (!Consume(TokenKind::right_brace))
		{
			while (true)
			{
				if (current_token->Is(TokenKind::left_brace)) expr_list.push_back(ParseInitializerListExpression());
				else expr_list.push_back(ParseAssignmentExpression());
				if (Consume(TokenKind::right_brace)) break;
				Expect(TokenKind::comma);
			}
		}
		return sema->ActOnInitializerListExpr(loc, std::move(expr_list));
	}

	void Parser::ParseFunctionAttributes(Uint8& attrs)
	{
		while (current_token->IsFunctionAttribute())
		{
			if (Consume(TokenKind::KW_inline))
			{
				if (!HasAttribute(attrs, FuncAttribute_Inline))
				{
					attrs |= FuncAttribute_Inline;
				}
				else
				{
					Diag(function_attribute_repetition);
					return;
				}
			}
			else if (Consume(TokenKind::KW_noinline))
			{
				if (!HasAttribute(attrs, FuncAttribute_NoInline))
				{
					attrs |= FuncAttribute_NoInline;
				}
				else
				{
					Diag(function_attribute_repetition);
					return;
				}
			}
			else if (Consume(TokenKind::KW_nomangle))
			{
				if (!HasAttribute(attrs, FuncAttribute_NoMangle))
				{
					attrs |= FuncAttribute_NoMangle;
				}
				else
				{
					Diag(function_attribute_repetition);
					return;
				}
			}
		}
	}

	void Parser::ParseMethodAttributes(Uint8& attrs)
	{
		while (current_token->IsMethodAttribute())
		{
			if (Consume(TokenKind::KW_const))
			{
				if (!HasAttribute(attrs, MethodAttribute_Const))
				{
					attrs |= MethodAttribute_Const;
				}
				else
				{
					Diag(method_attribute_repetition);
					return;
				}
			}
			else if (Consume(TokenKind::KW_virtual))
			{
				if (!HasAttribute(attrs, MethodAttribute_Virtual))
				{
					attrs |= MethodAttribute_Virtual;
				}
				else
				{
					Diag(method_attribute_repetition);
					return;
				}
			}
			else if (Consume(TokenKind::KW_pure))
			{
				if (!HasAttribute(attrs, MethodAttribute_Pure))
				{
					attrs |= MethodAttribute_Pure;
				}
				else
				{
					Diag(method_attribute_repetition);
					return;
				}
			}
			else if (Consume(TokenKind::KW_final))
			{
				if (!HasAttribute(attrs, MethodAttribute_Final))
				{
					attrs |= MethodAttribute_Final;
				}
				else
				{
					Diag(method_attribute_repetition);
					return;
				}
			}
		}
	}

	void Parser::ParseTypeQualifier(QualType& type)
	{
		if (Consume(TokenKind::KW_const)) type.AddConst();
	}

	void Parser::ParseTypeSpecifier(QualType& type, Bool array_size_forbidden, Bool allow_ref)
	{
		Bool is_ref = false;
		if(allow_ref) is_ref = Consume(TokenKind::KW_ref);

		switch (current_token->GetKind())
		{
		case TokenKind::KW_auto:   break;
		case TokenKind::KW_void:  type.SetType(VoidType::Get(context));  break;
		case TokenKind::KW_bool:  type.SetType(BoolType::Get(context));  break;
		case TokenKind::KW_char:  type.SetType(CharType::Get(context));  break;
		case TokenKind::KW_int:   type.SetType(IntType::Get(context));   break;
		case TokenKind::KW_float: type.SetType(FloatType::Get(context)); break;
		case TokenKind::identifier:
		{
			std::string_view identifier = current_token->GetData();
			if (TagDecl* tag_decl = sema->sema_ctx.tag_sym_table.LookUp(identifier))
			{
				if (isa<EnumDecl>(tag_decl))
				{
					type.SetType(IntType::Get(context));
				}
				else if (isa<AliasDecl>(tag_decl))
				{
					Bool const is_const = type.IsConst();
					type = tag_decl->GetType();
					if (is_const) type.AddConst();
				}
				else if (isa<ClassDecl>(tag_decl))
				{
					ClassDecl* class_decl = cast<ClassDecl>(tag_decl);
					type.SetType(ClassType::Get(context, class_decl));
				}
				else Diag(invalid_type_specifier);
			}
			else Diag(invalid_type_specifier);
		}
		break;
		default:
			Diag(invalid_type_specifier);
			return;
		}
		++current_token;

		while (Consume(TokenKind::left_square))
		{
			if (isa<VoidType>(type))
			{
				Diag(invalid_type_specifier);
				return;
			}

			if (array_size_forbidden)
			{
				Expect(TokenKind::right_square);
				type.SetType(ArrayType::Get(context, type));
				type.RemoveConst();
			}
			else
			{
				if (Consume(TokenKind::right_square))
				{
					type.SetType(ArrayType::Get(context, type));
					type.RemoveConst();
				}
				else
				{
					UniqueExprPtr array_size_expr = ParseConditionalExpression();
					if (!array_size_expr->IsConstexpr())
					{
						Diag(array_size_not_constexpr);
						return;
					}
					Int64 array_size = array_size_expr->EvaluateConstexpr();
					if (array_size <= 0)
					{
						Diag(array_size_not_positive);
						return;
					}
					Expect(TokenKind::right_square);
					type.SetType(ArrayType::Get(context, type, array_size));
					type.RemoveConst();
				}
			}
		}

		if (is_ref)
		{
			Bool is_const = type.IsConst();
			type.RemoveConst();
			type = QualType(RefType::Get(context, type), is_const ? Qualifier_Const : Qualifier_None);
		}
	}

	Bool Parser::IsFunctionDeclaration()
	{
		TokenPtr token = current_token;

		Consume(TokenKind::KW_public, TokenKind::KW_private);
		if (Consume(TokenKind::KW_inline))
		{
			current_token = token;
			return true;
		}
		if (Consume(TokenKind::KW_noinline)) 
		{
			current_token = token;
			return true;
		}
		if (Consume(TokenKind::KW_nomangle))
		{
			current_token = token;
			return true;
		}

		QualType tmp{};
		ParseTypeQualifier(tmp);
		ParseTypeSpecifier(tmp);
		Expect(TokenKind::identifier);

		Bool is_function = Consume(TokenKind::left_round);
		current_token = token;
		return is_function;
	}

	Bool Parser::IsCurrentTokenTypename()
	{
		return current_token->IsTypename() || sema->sema_ctx.tag_sym_table.LookUp(current_token->GetData()) != nullptr;
	}

	Bool Parser::Consume(TokenKind k)
	{
		if (current_token->Is(k))
		{
			++current_token; return true;
		}
		else return false;
	}
	template<typename... Ts>
	Bool Parser::Consume(TokenKind k, Ts... ts)
	{
		if (current_token->IsOneOf(k, ts...))
		{
			++current_token; return true;
		}
		else return false;
	}

	Bool Parser::Expect(TokenKind k)
	{
		if (!Consume(k))
		{
			Diag(unexpected_token);
			return false;
		}
		return true;
	}
	template<typename... Ts>
	Bool Parser::Expect(TokenKind k, Ts... ts)
	{
		if (!Consume(k, ts...))
		{
			Diag(unexpected_token);
			return false;
		}
		return true;
	}

	Bool Parser::Expect(TokenKind k, DiagCode code)
	{
		if (!Consume(k))
		{
			Diag(code);
			return false;
		}
		return true;
	}

	void Parser::Diag(DiagCode code)
	{
		--current_token;
		diagnostics.Report(current_token->GetLocation(), code);
		++current_token;
	}
	template<typename... Ts>
	void Parser::Diag(DiagCode code, Ts&&... args)
	{
		diagnostics.Report(code, current_token->GetLocation(), std::forward<Ts>(args)...);
	}

}