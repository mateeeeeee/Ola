#include "Parser.h"
#include "Diagnostics.h"
#include "FrontendContext.h"
#include "AST/AST.h"
#include "AST/Type.h"
#include "Sema.h"

namespace ola
{
	namespace
	{
		std::string GetTypeNameForTemplate(QualType const& type)
		{
			Type const* t = type.GetTypePtr();
			if (!t) return "?";
			if (isa<IntType>(t)) 	return "int";
			if (isa<FloatType>(t)) 	return "float";
			if (isa<BoolType>(t)) 	return "bool";
			if (isa<CharType>(t)) 	return "char";
			if (isa<VoidType>(t)) 	return "void";
			if (isa<ClassType>(t))
			{
				ClassDecl const* cd = cast<ClassType>(t)->GetClassDecl();
				return std::string(cd->GetName());
			}
			if (isa<ArrayType>(t))
			{
				ArrayType const* arr = cast<ArrayType>(t);
				return GetTypeNameForTemplate(arr->GetElementType()) + "[]";
			}
			if (isa<PtrType>(t))
			{
				PtrType const* ptr = cast<PtrType>(t);
				return GetTypeNameForTemplate(ptr->GetPointeeType()) + "*";
			}
			return "?";
		}
	}

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
		if (diagnostics.HasErrors()) 
		{
			ast.reset();
		}
	}

	void Parser::ParseImported(std::vector<Token> const& _tokens)
	{
		tokens = _tokens;
		current_token = tokens.begin();
		sema = MakeUnique<Sema>(context, diagnostics);
		ast = MakeUnique<AST>();
		ParseTranslationUnit();
		if (diagnostics.HasErrors()) 
		{
			ast.reset();
		}
	}

	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof) && !diagnostics.HasErrors())
		{
			UniqueDeclPtrList decls = ParseGlobalDeclaration();
			for(auto&& decl : decls) 
			{
				ast->translation_unit->AddDecl(std::move(decl));
			}
		}
	}

	void Parser::AddBuiltinDecls(UniqueTranslationUnitPtr& TU)
	{
		UniqueAliasDeclPtr string_alias = sema->ActOnAliasDecl("string", SourceLocation{}, ArrayType::Get(context, CharType::Get(context), 0));
		if (string_alias)
		{
			TU->AddDecl(std::move(string_alias));
		}
	}

	UniqueDeclPtrList Parser::ParseGlobalDeclaration()
	{
		while (Consume(TokenKind::semicolon)) 
		{
			Diag(empty_statement);
		}

		UniqueDeclPtrList global_decl_list;
		if (Consume(TokenKind::KW_extern))
		{
			if (IsFunctionDeclaration())
			{
				UniqueFunctionDeclPtr function_decl = ParseFunctionDeclaration();
				if (function_decl)
				{
					global_decl_list.push_back(std::move(function_decl));
				}
			}
			else
			{
				global_decl_list = ParseExternVariableDeclaration();
			}
		}
		else
		{
			DeclVisibility visibility = DeclVisibility::Private;
			if (Consume(TokenKind::KW_public))
			{
				visibility = DeclVisibility::Public;
			}
			else if (Consume(TokenKind::KW_private))
			{
				visibility = DeclVisibility::Private;
			}

			if (current_token->Is(TokenKind::KW_static))
			{
				Diag(static_outside_class);
				return global_decl_list;
			}

			if (Consume(TokenKind::KW_class))
			{
				UniqueDeclPtr class_decl = ParseClassDeclaration();
				if (class_decl)
				{
					global_decl_list.push_back(std::move(class_decl));
				}
			}
			else if (Consume(TokenKind::KW_interface))
			{
				UniqueClassDeclPtr interface_decl = ParseInterfaceDeclaration();
				if (interface_decl)
				{
					global_decl_list.push_back(std::move(interface_decl));
				}
			}
			else if (Consume(TokenKind::KW_enum))
			{
				UniqueEnumDeclPtr enum_decl = ParseEnumDeclaration();
				if (enum_decl)
				{
					global_decl_list.push_back(std::move(enum_decl));
				}
			}
			else if (Consume(TokenKind::KW_alias))
			{
				UniqueAliasDeclPtr alias_decl = ParseAliasDeclaration();
				if (alias_decl)
				{
					global_decl_list.push_back(std::move(alias_decl));
				}
			}
			else
			{
				if (IsFunctionDeclaration())
				{
					UniqueDeclPtr function_decl = ParseFunctionDefinition(visibility);
					if (function_decl)
					{
						global_decl_list.push_back(std::move(function_decl));
					}
				}
				else
				{
					UniqueVarDeclPtrList variable_decls = ParseVariableDeclaration(visibility);
					for (auto& variable_decl : variable_decls)
					{
						if (variable_decl)
						{
							global_decl_list.push_back(std::move(variable_decl));
						}
					}
				}
			}

			if (!global_decl_list.empty()) 
			{
				global_decl_list.back()->SetVisibility(visibility);
			}
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
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
				return nullptr;
			}

			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);

			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (current_token->Is(TokenKind::eof) || current_token->Is(TokenKind::left_brace))
				{
					Diag(unexpected_token);
					break;
				}
				if (!param_types.empty() && !Consume(TokenKind::comma))
				{
					Diag(function_params_missing_coma);
				}

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				if (!param_decl)
				{
					Diag(unexpected_token);
					break;
				}
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			Expect(TokenKind::semicolon, function_def_cannot_be_extern);
		}
		return sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls), DeclVisibility::Extern, attrs);
	}

	UniqueDeclPtr Parser::ParseFunctionDefinition(DeclVisibility visibility, Bool is_template_instantiation)
	{
		Uint64 start_token_pos = current_token - tokens.begin();
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

			// Check for template function with unknown return type: identifier identifier <
			if (!is_template_instantiation &&
				current_token->Is(TokenKind::identifier) &&
				(current_token + 1)->Is(TokenKind::identifier) &&
				(current_token + 2)->Is(TokenKind::less) &&
				!sema->sema_ctx.tag_sym_table.Lookup(current_token->GetData()))
			{
				++current_token; 
			}
			else
			{
				ParseTypeSpecifier(return_type);
			}

			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
				return nullptr;
			}

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;

			if (is_template_instantiation && Consume(TokenKind::less))
			{
				Int32 angle_count = 1;
				while (angle_count != 0)
				{
					if (current_token->Is(TokenKind::less)) ++angle_count;
					else if (current_token->Is(TokenKind::greater)) --angle_count;
					++current_token;
				}
			}

			std::vector<std::string> type_params;
			if (!is_template_instantiation && Consume(TokenKind::less))
			{
				do
				{
					if (current_token->IsNot(TokenKind::identifier))
					{
						Diag(expected_identifier);
						return nullptr;
					}
					type_params.push_back(std::string(current_token->GetData()));
					++current_token;
				} while (Consume(TokenKind::comma));
				Expect(TokenKind::greater);
			}

			if (!type_params.empty())
			{
				Uint64 body_token_begin = start_token_pos;
				Expect(TokenKind::left_round);
				Int32 paren_count = 1;
				while (paren_count != 0)
				{
					if (current_token->Is(TokenKind::left_round)) ++paren_count;
					else if (current_token->Is(TokenKind::right_round)) --paren_count;
					if (paren_count != 0) ++current_token;
				}
				Expect(TokenKind::right_round);

				Expect(TokenKind::left_brace);
				Int32 brace_count = 1;
				while (brace_count != 0)
				{
					if (current_token->Is(TokenKind::left_brace)) ++brace_count;
					else if (current_token->Is(TokenKind::right_brace)) --brace_count;
					if (brace_count != 0) ++current_token;
				}
				++current_token;
				Uint64 body_token_end = current_token - tokens.begin();

				return sema->ActOnTemplateFunctionDecl(name, loc, std::move(type_params), attrs, visibility, body_token_begin, body_token_end);
			}

			Expect(TokenKind::left_round);

			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (current_token->Is(TokenKind::eof) || current_token->Is(TokenKind::left_brace))
				{
					Diag(unexpected_token);
					break;
				}
				if (!param_types.empty() && !Consume(TokenKind::comma))
				{
					Diag(function_params_missing_coma);
				}

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				if (!param_decl)
				{
					Diag(unexpected_token);
					break;
				}
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			func_decl = sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls), visibility, attrs);
			if (!func_decl)
			{
				return nullptr;
			}
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

	UniqueMethodDeclPtr Parser::ParseMethodDeclaration()
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public))
		{
			visibility = DeclVisibility::Public;
		}
		else if (Consume(TokenKind::KW_private))
		{
			visibility = DeclVisibility::Private;
		}

		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		FuncAttributes func_attrs = FuncAttribute_None;
		MethodAttributes method_attrs = MethodAttribute_None;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			ParseFunctionAttributes(func_attrs);
			if (current_token->IsOneOf(TokenKind::KW_virtual, TokenKind::KW_pure, TokenKind::KW_final, TokenKind::KW_const))
			{
				Diag(method_attr_before_return_type);
				return nullptr;
			}
			QualType return_type{};
			ParseTypeQualifier(return_type);
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
				return nullptr;
			}

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);
			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (current_token->Is(TokenKind::eof) || current_token->Is(TokenKind::left_brace))
				{
					Diag(unexpected_token);
					break;
				}
				if (!param_types.empty() && !Consume(TokenKind::comma))
				{
					Diag(function_params_missing_coma);
				}

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				if (!param_decl)
				{
					Diag(unexpected_token);
					break;
				}
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			ParseMethodAttributes(method_attrs);
			method_attrs |= MethodAttribute_Pure;	//method declarations can appear only in interfaces, and they are always pure and virtual
			method_attrs |= MethodAttribute_Virtual; 
			Expect(TokenKind::semicolon);
		}
		return sema->ActOnMethodDecl(name, loc, function_type, std::move(param_decls), nullptr, visibility, func_attrs, method_attrs);
	}

	UniqueMethodDeclPtr Parser::ParseMethodDefinition(MethodParseMode mode, MethodDecl* existing_stub)
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public))
		{
			visibility = DeclVisibility::Public;
		}
		else if (Consume(TokenKind::KW_private))
		{
			visibility = DeclVisibility::Private;
		}

		Bool is_static = Consume(TokenKind::KW_static);

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
			if (current_token->IsOneOf(TokenKind::KW_virtual, TokenKind::KW_pure, TokenKind::KW_final, TokenKind::KW_const))
			{
				Diag(method_attr_before_return_type);
				return nullptr;
			}
			QualType return_type{};
			ParseTypeQualifier(return_type);
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
				return nullptr;
			}

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);
			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (current_token->Is(TokenKind::eof) || current_token->Is(TokenKind::left_brace))
				{
					Diag(unexpected_token);
					break;
				}
				if (!param_types.empty() && !Consume(TokenKind::comma))
				{
					Diag(function_params_missing_coma);
				}

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				if (!param_decl)
				{
					Diag(unexpected_token);
					break;
				}
				param_types.emplace_back(param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetType(FuncType::Get(context, return_type, param_types));
			ParseMethodAttributes(method_attrs);
			if (is_static)
			{
				method_attrs |= MethodAttribute_Static;
			}
			if (mode == MethodParseMode::Declarations)
			{
				if (!Consume(TokenKind::semicolon))
				{
					Int32 brace_count = 0;
					Expect(TokenKind::left_brace); ++brace_count;
					while (brace_count != 0)
					{
						if (Consume(TokenKind::left_brace))
						{
							++brace_count;
						}
						else if (Consume(TokenKind::right_brace))
						{
							--brace_count;
						}
						else current_token++;
					}
				}
			}
			else
			{
				if (!Consume(TokenKind::semicolon))
				{
					sema->sema_ctx.current_func = &function_type;
					sema->sema_ctx.is_method_const = HasAttribute(method_attrs, MethodAttribute_Const);
					sema->sema_ctx.is_static_method = is_static;
					function_body = ParseCompoundStatement();
					sema->sema_ctx.is_static_method = false;
					sema->sema_ctx.is_method_const = false;
					sema->sema_ctx.current_func = nullptr;
				}
			}
		}
		if (mode == MethodParseMode::Declarations)
		{
			return sema->ActOnMethodDecl(name, loc, function_type, std::move(param_decls), nullptr, visibility, func_attrs, method_attrs, /*pre_registration=*/true);
		}
		else 
		{
			if (existing_stub)
			{
				sema->ActOnAttachMethodBody(existing_stub, std::move(param_decls), std::move(function_body));
			}
			return nullptr;
		}
	}

	UniqueConstructorDeclPtr Parser::ParseConstructorDefinition(MethodParseMode mode, MethodDecl* existing_stub)
	{
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualType function_type{};
		UniqueParamVarDeclPtrList param_decls;
		UniqueCompoundStmtPtr constructor_body;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
				return nullptr;
			}
			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetData(); ++current_token;
			Expect(TokenKind::left_round);
			std::vector<QualType> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (current_token->Is(TokenKind::eof) || current_token->Is(TokenKind::left_brace))
				{
					Diag(unexpected_token);
					break;
				}
				if (!param_types.empty() && !Consume(TokenKind::comma))
				{
					Diag(function_params_missing_coma);
				}

				UniqueParamVarDeclPtr param_decl = ParseParamVariableDeclaration();
				if (param_decl)
				{
					param_types.emplace_back(param_decl->GetType());
					param_decls.push_back(std::move(param_decl));
				}
			}
			function_type.SetType(FuncType::Get(context, VoidType::Get(context), param_types));
			if (mode == MethodParseMode::Declarations)
			{
				if (!Consume(TokenKind::semicolon))
				{
					Int32 brace_count = 0;
					Expect(TokenKind::left_brace); ++brace_count;
					while (brace_count != 0)
					{
						if (Consume(TokenKind::left_brace))
						{
							++brace_count;
						}
						else if (Consume(TokenKind::right_brace))
						{
							--brace_count;
						}
						else current_token++;
					}
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
		if (mode == MethodParseMode::Declarations)
		{
			return sema->ActOnConstructorDecl(name, loc, function_type, std::move(param_decls), nullptr);
		}
		else 
		{
			if (existing_stub)
			{
				sema->ActOnAttachMethodBody(existing_stub, std::move(param_decls), std::move(constructor_body));
			}
			return nullptr;
		}
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
			if (!var_decl_list.empty())
			{
				Expect(TokenKind::comma);
			}
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
			}
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueExprPtr init_expr = nullptr;
			if (Consume(TokenKind::equal))
			{
				init_expr = (current_token->Is(TokenKind::left_brace)) ? ParseInitializerListExpression() : ParseAssignmentExpression();
				if (!init_expr)
				{
					break;
				}
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
						if (Consume(TokenKind::right_round))
						{
							break;
						}
						Expect(TokenKind::comma);
					}
				}
				init_expr = sema->ActOnConstructorExpr(loc, variable_type, std::move(args));
			}
			UniqueVarDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, std::move(init_expr), visibility);
			if (var_decl) 
			{
				var_decl_list.push_back(std::move(var_decl));
			}

		} while (!Consume(TokenKind::semicolon) && !diagnostics.HasErrors());
		return var_decl_list;
	}

	UniqueFieldDeclPtrList Parser::ParseFieldDeclaration(Bool first_pass)
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public))
		{
			visibility = DeclVisibility::Public;
		}
		else if (Consume(TokenKind::KW_private))
		{
			visibility = DeclVisibility::Private;
		}

		Bool is_static = Consume(TokenKind::KW_static);

		UniqueFieldDeclPtrList member_var_decl_list;
		QualType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do
		{
			if (!member_var_decl_list.empty())
			{
				Expect(TokenKind::comma);
			}
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
			}
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueExprPtr init_expr = nullptr;
			if (Consume(TokenKind::equal))
			{
				init_expr = current_token->Is(TokenKind::left_brace) ? ParseInitializerListExpression() : ParseAssignmentExpression();
				if (!init_expr)
				{
					break;
				}
			}
			if (first_pass)
			{
				UniqueFieldDeclPtr var_decl = sema->ActOnFieldDecl(name, loc, variable_type, std::move(init_expr), visibility, is_static);
				if (var_decl)
				{
					member_var_decl_list.push_back(std::move(var_decl));
				}
			}
		} while (!Consume(TokenKind::semicolon) && !diagnostics.HasErrors());
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
			if (!var_decl_list.empty())
			{
				Expect(TokenKind::comma);
			}
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
			}
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetData(); ++current_token;

			UniqueVarDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, nullptr, DeclVisibility::Extern);
			if (var_decl) 
			{
				var_decl_list.push_back(std::move(var_decl));
			}
		} while (!Consume(TokenKind::semicolon) && !diagnostics.HasErrors());
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
			if (current_token->Is(TokenKind::right_brace) || current_token->Is(TokenKind::eof))
			{
				Diag(empty_enum_declaration);
				Consume(TokenKind::right_brace);
				break;
			}
			std::string enum_value_name;
			if (current_token->IsNot(TokenKind::identifier))
			{
				Diag(expected_identifier);
			}
			SourceLocation loc = current_token->GetLocation();
			enum_value_name = current_token->GetData(); ++current_token;
			if (Consume(TokenKind::equal))
			{
				UniqueExprPtr enum_value_expr = ParseAssignmentExpression();
				UniqueEnumMemberDeclPtr enum_member = sema->ActOnEnumMemberDecl(enum_value_name, loc, std::move(enum_value_expr));
				if (enum_member) 
				{ 
					val = enum_member->GetValue() + 1; 
					enum_members.push_back(std::move(enum_member)); 
				}
			}
			else
			{
				UniqueEnumMemberDeclPtr enum_member = sema->ActOnEnumMemberDecl(enum_value_name, loc, val++);
				if (enum_member) 
				{
					enum_members.push_back(std::move(enum_member));
				}
			}
			if (Consume(TokenKind::right_brace))
			{
				break;
			}
			Expect(TokenKind::comma);
		}
		Expect(TokenKind::semicolon);

		return sema->ActOnEnumDecl(enum_tag, loc, std::move(enum_members));
	}

	UniqueAliasDeclPtr Parser::ParseAliasDeclaration()
	{
		std::string alias_name = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->IsNot(TokenKind::identifier))
		{
			Diag(expected_identifier);
		}
		alias_name = current_token->GetData();
		++current_token;

		Expect(TokenKind::equal);

		QualType aliased_type{};
		ParseTypeQualifier(aliased_type);
		ParseTypeSpecifier(aliased_type);
		Expect(TokenKind::semicolon);

		return sema->ActOnAliasDecl(alias_name, loc, aliased_type);
	}

	UniqueDeclPtr Parser::ParseClassDeclaration()
	{
		std::string class_name = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->Is(TokenKind::identifier))
		{
			class_name = current_token->GetData();
			++current_token;
		}
		else
		{
			Expect(TokenKind::identifier);
		}

		std::vector<std::string> type_params;
		if (Consume(TokenKind::less))
		{
			do
			{
				if (current_token->IsNot(TokenKind::identifier))
				{
					Diag(expected_identifier);
					return nullptr;
				}
				type_params.push_back(std::string(current_token->GetData()));
				++current_token;
			} while (Consume(TokenKind::comma));
			Expect(TokenKind::greater);
		}

		if (!type_params.empty())
		{
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

			Uint64 body_token_begin = current_token - tokens.begin();
			Int32 brace_count = 0;
			Expect(TokenKind::left_brace); ++brace_count;
			while (brace_count != 0)
			{
				if (Consume(TokenKind::left_brace))
				{
					++brace_count;
				}
				else if (Consume(TokenKind::right_brace))
				{
					--brace_count;
				}
				else ++current_token;
			}
			Expect(TokenKind::semicolon);
			Uint64 body_token_end = current_token - tokens.begin();

			return sema->ActOnTemplateClassDecl(class_name, loc, std::move(type_params), base_class, final, body_token_begin, body_token_end);
		}

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
		UniqueFieldDeclPtrList static_member_variables;
		UniqueMethodDeclPtrList static_member_functions;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);

			sema->sema_ctx.current_base_class = base_class;
			sema->sema_ctx.current_class_name = class_name;
			{
				std::vector<MethodDecl*> body_stubs;
				Uint64 body_stub_idx = 0;
				auto ParseClassMembers = [&](MethodParseMode mode)
					{
						Expect(TokenKind::left_brace);
						while (!Consume(TokenKind::right_brace))
						{
							Bool next_is_static = current_token->Is(TokenKind::KW_static)
								|| ((current_token->Is(TokenKind::KW_public) || current_token->Is(TokenKind::KW_private))
									&& (current_token + 1)->Is(TokenKind::KW_static));

							if (!next_is_static && current_token->Is(TokenKind::identifier) && (current_token + 1)->Is(TokenKind::left_round))
							{
								if (mode == MethodParseMode::Declarations)
								{
									UniqueConstructorDeclPtr stub = ParseConstructorDefinition(MethodParseMode::Declarations);
									body_stubs.push_back(stub.get());
									if (stub)
									{
										member_functions.push_back(std::move(stub));
									}
								}
								else
								{
									MethodDecl* stub = body_stub_idx < body_stubs.size() ? body_stubs[body_stub_idx++] : nullptr;
									(void)ParseConstructorDefinition(MethodParseMode::Bodies, stub);
								}
								continue;
							}

							Bool is_function_declaration = IsFunctionDeclaration();
							if (is_function_declaration)
							{
								if (mode == MethodParseMode::Declarations)
								{
									UniqueMethodDeclPtr stub = ParseMethodDefinition(MethodParseMode::Declarations);
									body_stubs.push_back(stub.get());
									if (stub)
									{
										if (stub->IsStatic())
										{
											static_member_functions.push_back(std::move(stub));
										}
										else
										{
											member_functions.push_back(std::move(stub));
										}
									}
								}
								else
								{
									MethodDecl* stub = body_stub_idx < body_stubs.size() ? body_stubs[body_stub_idx++] : nullptr;
									(void)ParseMethodDefinition(MethodParseMode::Bodies, stub);
								}
							}
							else
							{
								UniqueFieldDeclPtrList var_decls = ParseFieldDeclaration(mode == MethodParseMode::Declarations);
								if (mode == MethodParseMode::Declarations)
								{
									for (auto& var_decl : var_decls)
									{
										if (var_decl)
										{
											if (var_decl->IsStatic())
											{
												static_member_variables.push_back(std::move(var_decl));
											}
											else
											{
												member_variables.push_back(std::move(var_decl));
											}
										}
									}
								}
							}
						}
						Expect(TokenKind::semicolon);
					};

				TokenPtr start_token = current_token;
				ParseClassMembers(MethodParseMode::Declarations);
				current_token = start_token;
				ParseClassMembers(MethodParseMode::Bodies);
			}
			sema->sema_ctx.current_class_name = "";
			sema->sema_ctx.current_base_class = nullptr;
		}
		return sema->ActOnClassDecl(class_name, base_class, loc, std::move(member_variables), std::move(member_functions),
			std::move(static_member_variables), std::move(static_member_functions), final);
	}

	UniqueClassDeclPtr Parser::ParseInterfaceDeclaration()
	{
		std::string class_name = "";
		SourceLocation loc = current_token->GetLocation();
		if (current_token->Is(TokenKind::identifier))
		{
			class_name = current_token->GetData();
			++current_token;
		}
		else
		{
			Expect(TokenKind::identifier);
		}
		UniqueFieldDeclPtrList member_variables;
		UniqueMethodDeclPtrList member_functions;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);

			sema->sema_ctx.current_base_class = nullptr;
			sema->sema_ctx.current_class_name = class_name;
			Expect(TokenKind::left_brace);
			while (!Consume(TokenKind::right_brace))
			{
				if (current_token->Is(TokenKind::eof))
				{
					Diag(unexpected_token);
					break;
				}
				UniqueMethodDeclPtr member_function = ParseMethodDeclaration();
				if (!member_function)
				{
					// Skip tokens until we find ';', '}', or EOF to recover
					while (!current_token->IsOneOf(TokenKind::semicolon, TokenKind::right_brace, TokenKind::eof))
					{
						++current_token;
					}
					Consume(TokenKind::semicolon);
					continue;
				}
				member_functions.push_back(std::move(member_function));
			}
			Expect(TokenKind::semicolon);
			sema->sema_ctx.current_class_name = "";
			sema->sema_ctx.current_base_class = nullptr;
		}
		return sema->ActOnClassDecl(class_name, nullptr, loc, std::move(member_variables), std::move(member_functions),
			{}, {}, false);
	}

	ClassDecl* Parser::ParseTemplateInstantiation(TemplateClassDecl* tmpl, SourceLocation const& loc)
	{
		Expect(TokenKind::less);
		std::vector<QualType> args;
		do
		{
			QualType arg{};
			ParseTypeQualifier(arg);
			ParseTypeSpecifier(arg);
			args.push_back(arg);
		} while (Consume(TokenKind::comma));
		Expect(TokenKind::greater);

		auto const& type_params = tmpl->GetTypeParams();
		if (args.size() != type_params.size())
		{
			diagnostics.Report(loc, template_arg_count_mismatch, tmpl->GetName(), type_params.size(), args.size());
			return nullptr;
		}

		if (ClassDecl* cached = context->GetInstantiation(tmpl, args))
		{
			return cached;
		}

		std::string specialized_name(tmpl->GetName());
		specialized_name += '<';
		for (Uint64 i = 0; i < args.size(); ++i)
		{
			if (i > 0) specialized_name += ',';
			specialized_name += GetTypeNameForTemplate(args[i]);
		}
		specialized_name += '>';

		UniqueClassDeclPtr result = MakeUnique<ClassDecl>(specialized_name, loc);
		ClassDecl* raw_result = result.get();
		result->SetType(ClassType::Get(context, raw_result));
		result->SetBaseClass(tmpl->GetBaseClass());
		context->RegisterInstantiation(tmpl, args, raw_result);

		TokenPtr saved_token = current_token;

		Uint64 body_begin = tmpl->GetBodyTokenBegin();
		Uint64 body_end = tmpl->GetBodyTokenEnd();
		current_token = tokens.begin() + body_begin;

		UniqueFieldDeclPtrList member_variables;
		UniqueMethodDeclPtrList member_functions;
		UniqueFieldDeclPtrList static_member_variables;
		UniqueMethodDeclPtrList static_member_functions;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);

			std::vector<UniqueAliasDeclPtr> type_aliases;
			for (Uint64 i = 0; i < type_params.size(); ++i)
			{
				type_aliases.push_back(sema->ActOnAliasDecl(type_params[i], loc, args[i]));
			}

			std::string saved_class_name = sema->sema_ctx.current_class_name;
			ClassDecl const* saved_base_class = sema->sema_ctx.current_base_class;
			QualType const* saved_current_func = sema->sema_ctx.current_func;
			Bool saved_return_stmt = sema->sema_ctx.return_stmt_encountered;
			Bool saved_is_method_const = sema->sema_ctx.is_method_const;
			Bool saved_is_static_method = sema->sema_ctx.is_static_method;
			Bool saved_is_constructor = sema->sema_ctx.is_constructor;
			sema->sema_ctx.current_class_name = std::string(tmpl->GetName());
			sema->sema_ctx.current_base_class = tmpl->GetBaseClass();
			sema->sema_ctx.current_func = nullptr;

			{
				std::vector<MethodDecl*> body_stubs;
				Uint64 body_stub_idx = 0;
				auto ParseClassMembers = [&](MethodParseMode mode)
					{
						Expect(TokenKind::left_brace);
						while (!Consume(TokenKind::right_brace))
						{
							Bool next_is_static = current_token->Is(TokenKind::KW_static)
								|| ((current_token->Is(TokenKind::KW_public) || current_token->Is(TokenKind::KW_private))
									&& (current_token + 1)->Is(TokenKind::KW_static));

							if (!next_is_static && current_token->Is(TokenKind::identifier) && (current_token + 1)->Is(TokenKind::left_round))
							{
								if (mode == MethodParseMode::Declarations)
								{
									UniqueConstructorDeclPtr stub = ParseConstructorDefinition(MethodParseMode::Declarations);
									body_stubs.push_back(stub.get());
									if (stub)
									{
										member_functions.push_back(std::move(stub));
									}
								}
								else
								{
									MethodDecl* stub = body_stub_idx < body_stubs.size() ? body_stubs[body_stub_idx++] : nullptr;
									(void)ParseConstructorDefinition(MethodParseMode::Bodies, stub);
								}
								continue;
							}

							Bool is_function_declaration = IsFunctionDeclaration();
							if (is_function_declaration)
							{
								if (mode == MethodParseMode::Declarations)
								{
									UniqueMethodDeclPtr stub = ParseMethodDefinition(MethodParseMode::Declarations);
									body_stubs.push_back(stub.get());
									if (stub)
									{
										if (stub->IsStatic())
										{
											static_member_functions.push_back(std::move(stub));
										}
										else
										{
											member_functions.push_back(std::move(stub));
										}
									}
								}
								else
								{
									MethodDecl* stub = body_stub_idx < body_stubs.size() ? body_stubs[body_stub_idx++] : nullptr;
									(void)ParseMethodDefinition(MethodParseMode::Bodies, stub);
								}
							}
							else
							{
								UniqueFieldDeclPtrList var_decls = ParseFieldDeclaration(mode == MethodParseMode::Declarations);
								if (mode == MethodParseMode::Declarations)
								{
									for (auto& var_decl : var_decls)
									{
										if (var_decl)
										{
											if (var_decl->IsStatic())
											{
												static_member_variables.push_back(std::move(var_decl));
											}
											else
											{
												member_variables.push_back(std::move(var_decl));
											}
										}
									}
								}
							}
						}
						Expect(TokenKind::semicolon);
					};

				TokenPtr start_token = current_token;
				ParseClassMembers(MethodParseMode::Declarations);
				current_token = start_token;
				ParseClassMembers(MethodParseMode::Bodies);
			}

			sema->sema_ctx.current_class_name = saved_class_name;
			sema->sema_ctx.current_base_class = saved_base_class;
			sema->sema_ctx.current_func = saved_current_func;
			sema->sema_ctx.return_stmt_encountered = saved_return_stmt;
			sema->sema_ctx.is_method_const = saved_is_method_const;
			sema->sema_ctx.is_static_method = saved_is_static_method;
			sema->sema_ctx.is_constructor = saved_is_constructor;
		}

		raw_result->SetFields(std::move(member_variables));
		raw_result->SetMethods(std::move(member_functions));
		raw_result->SetStaticFields(std::move(static_member_variables));
		raw_result->SetStaticMethods(std::move(static_member_functions));
		raw_result->SetFinal(tmpl->IsFinal());

		MethodDecl const* error_decl = nullptr;
		BuildVTableResult build_result = raw_result->BuildVTable(error_decl);
		if (build_result == BuildVTableResult::Error_OverrideFinal)
		{
			diagnostics.Report(error_decl->GetLocation(), cannot_override_final_function, error_decl->GetName());
		}

		sema->sema_ctx.tag_sym_table.Insert(raw_result);
		ast->translation_unit->AddDecl(std::move(result));

		current_token = saved_token;
		return raw_result;
	}

	FunctionDecl* Parser::ParseTemplateFunctionInstantiation(TemplateFunctionDecl* tmpl, SourceLocation const& loc)
	{
		Expect(TokenKind::less);
		std::vector<QualType> args;
		do
		{
			QualType arg{};
			ParseTypeQualifier(arg);
			ParseTypeSpecifier(arg);
			args.push_back(arg);
		} while (Consume(TokenKind::comma));
		Expect(TokenKind::greater);

		auto const& type_params = tmpl->GetTypeParams();
		if (args.size() != type_params.size())
		{
			diagnostics.Report(loc, template_arg_count_mismatch, tmpl->GetName(), type_params.size(), args.size());
			return nullptr;
		}

		if (FunctionDecl* cached = context->GetFuncInstantiation(tmpl, args))
		{
			return cached;
		}

		TokenPtr saved_token = current_token;

		Uint64 body_begin = tmpl->GetBodyTokenBegin();
		current_token = tokens.begin() + body_begin;

		QualType const* saved_current_func = sema->sema_ctx.current_func;
		Bool saved_return_stmt = sema->sema_ctx.return_stmt_encountered;
		UniqueDeclPtr instantiated;
		{
			SYM_TABLE_GUARD(sema->sema_ctx.decl_sym_table);
			SYM_TABLE_GUARD(sema->sema_ctx.tag_sym_table);

			std::vector<UniqueAliasDeclPtr> type_aliases;
			for (Uint64 i = 0; i < type_params.size(); ++i)
			{
				type_aliases.push_back(sema->ActOnAliasDecl(type_params[i], loc, args[i]));
			}
			instantiated = ParseFunctionDefinition(tmpl->IsPublic() ? DeclVisibility::Public : DeclVisibility::Private, true);
		}

		current_token = saved_token;
		sema->sema_ctx.current_func = saved_current_func;
		sema->sema_ctx.return_stmt_encountered = saved_return_stmt;
		if (!instantiated || !isa<FunctionDecl>(instantiated.get()))
		{
			return nullptr;
		}

		FunctionDecl* raw_func = cast<FunctionDecl>(instantiated.get());

		std::string specialized_name(tmpl->GetName());
		specialized_name += '<';
		for (Uint64 i = 0; i < args.size(); ++i)
		{
			if (i > 0) specialized_name += ',';
			specialized_name += GetTypeNameForTemplate(args[i]);
		}
		specialized_name += '>';

		context->RegisterFuncInstantiation(tmpl, args, raw_func);
		ast->translation_unit->AddDecl(std::move(instantiated));

		return raw_func;
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
			if ((current_token + 1)->Is(TokenKind::colon))
			{
				return ParseLabelStatement();
			}
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
		while (current_token->IsNot(TokenKind::right_brace) && !diagnostics.HasErrors())
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
				else if (current_token->Is(TokenKind::identifier) && (current_token + 1)->Is(TokenKind::period))
				{
					UniqueStmtPtr stmt = ParseExpressionStatement();
					stmts.push_back(std::move(stmt));
				}
				else
				{
					UniqueVarDeclPtrList variable_decls = ParseVariableDeclaration(DeclVisibility::None);
					for (auto& variable_decl : variable_decls)
					{
						if (variable_decl) 
						{
							stmts.push_back(sema->ActOnDeclStmt(std::move(variable_decl)));
						}
					}
				}
			}
			else
			{
				UniqueStmtPtr stmt = ParseStatement();
				if (stmt) stmts.push_back(std::move(stmt));
			}
		}
		Expect(TokenKind::right_brace);
		return sema->ActOnCompoundStmt(std::move(stmts));
	}

	UniqueExprStmtPtr Parser::ParseExpressionStatement()
	{
		if (Consume(TokenKind::semicolon))
		{
			return MakeUnique<NullStmt>();
		}
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
		if (Consume(TokenKind::KW_else))
		{
			else_stmt = ParseStatement();
		}
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
			for (auto& variable_decl : variable_decls)
			{
				decl_list.push_back(std::move(variable_decl));
			}
			init_stmt = MakeUnique<DeclStmt>(std::move(decl_list));
		}
		else
		{
			init_stmt = ParseExpressionStatement();
		}

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
			else
			{
				Diag(expected_identifier);
			}
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
		if (Consume(TokenKind::KW_case))
		{
			case_value = ParseExpression();
		}
		else
		{
			Expect(TokenKind::KW_default);
		}
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

	template<ExprParseFn ParseFn, TokenKind TK, BinaryExprKind OpK>
	UniqueExprPtr Parser::ParseBinaryExpression()
	{
		UniqueExprPtr lhs = (this->*ParseFn)();
		while (Consume(TK))
		{
			SourceLocation loc = current_token->GetLocation();
			UniqueExprPtr rhs = (this->*ParseFn)();
			UniqueBinaryExprPtr parent = sema->ActOnBinaryExpr(OpK, loc, std::move(lhs), std::move(rhs));
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
		if (diagnostics.HasErrors())
		{
			return nullptr;
		}
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
		case TokenKind::star:
			unary_kind = UnaryExprKind::Dereference;
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
						if (Consume(TokenKind::right_round))
						{
							break;
						}
						Expect(TokenKind::comma);
					}
				}
				if (expr && isa<IdentifierExpr>(expr.get()) && isa<ClassType>(expr->GetType()))
				{
					expr = sema->ActOnConstructorExpr(loc, expr->GetType(), std::move(args));
				}
				else
				{
					expr = sema->ActOnCallExpr(loc, std::move(expr), std::move(args));
				}
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
				if (!expr)
				{
					return nullptr;
				}
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
							if (Consume(TokenKind::right_round))
							{
								break;
							}
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
			case TokenKind::arrow:
			{
				++current_token;
				UniqueExprPtr zero_index = sema->ActOnIntLiteral(0, loc);
				expr = sema->ActOnArrayAccessExpr(loc, std::move(expr), std::move(zero_index));
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
							if (Consume(TokenKind::right_round))
							{
								break;
							}
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
		case TokenKind::KW_null:  return ParseNullExpression();
		case TokenKind::KW_new:    return ParseNewExpression();
		case TokenKind::KW_delete: return ParseDeleteExpression();
		default:
			Diag(unexpected_token);
			return nullptr;
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
		if ((current_token->IsTypename() && current_token->IsNot(TokenKind::KW_auto)) || 
			(current_token->Is(TokenKind::identifier) && sema->sema_ctx.tag_sym_table.Lookup(identifier) != nullptr))
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
		Int64 value = 0;
		if (string_number.size() > 2 && string_number[0] == '0' && (string_number[1] == 'b' || string_number[1] == 'B'))
		{
			value = std::stoll(std::string(string_number.substr(2)), nullptr, 2);
		}
		else
		{
			value = std::stoll(current_token->GetData().data(), nullptr, 0);
		}
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
		if (current_token->Is(TokenKind::KW_false))
		{
			value = false;
		}
		else if (current_token->Is(TokenKind::KW_true))
		{
			value = true;
		}
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

		if (current_token->Is(TokenKind::less))
		{
			std::vector<Decl*>& overloads = sema->sema_ctx.decl_sym_table.LookupOverload(name);
			TemplateFunctionDecl* tmpl = nullptr;
			for (Decl* d : overloads)
			{
				if (isa<TemplateFunctionDecl>(d)) 
				{ 
					tmpl = cast<TemplateFunctionDecl>(d); 
					break; 
				}
			}
			if (tmpl)
			{
				FunctionDecl* instantiated = ParseTemplateFunctionInstantiation(tmpl, loc);
				if (instantiated)
				{
					return MakeUnique<DeclRefExpr>(instantiated, loc);
				}
				return nullptr;
			}
		}

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

	UniqueExprPtr Parser::ParseNullExpression()
	{
		OLA_ASSERT(current_token->Is(TokenKind::KW_null));
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnNullLiteral(loc);
	}

	UniqueExprPtr Parser::ParseNewExpression()
	{
		OLA_ASSERT(current_token->Is(TokenKind::KW_new));
		SourceLocation loc = current_token->GetLocation();
		++current_token;

		QualType alloc_type{};
		ParseBaseType(alloc_type);

		UniqueExprPtr count_expr;
		UniqueExprPtrList ctor_args;
		Bool has_ctor_args = false;
		if (Consume(TokenKind::left_square))
		{
			count_expr = ParseAssignmentExpression();
			Expect(TokenKind::right_square);
			if (current_token->Is(TokenKind::left_round))
			{
				++current_token;
				has_ctor_args = true;
				if (!Consume(TokenKind::right_round))
				{
					while (true)
					{
						UniqueExprPtr arg_expr = ParseAssignmentExpression();
						ctor_args.push_back(std::move(arg_expr));
						if (Consume(TokenKind::right_round))
						{
							break;
						}
						Expect(TokenKind::comma);
					}
				}
			}
		}
		else if (current_token->Is(TokenKind::left_round))
		{
			++current_token;
			has_ctor_args = true;
			if (!Consume(TokenKind::right_round))
			{
				while (true)
				{
					UniqueExprPtr arg_expr = ParseAssignmentExpression();
					ctor_args.push_back(std::move(arg_expr));
					if (Consume(TokenKind::right_round))
					{
						break;
					}
					Expect(TokenKind::comma);
				}
			}
			count_expr = sema->ActOnIntLiteral(1, loc);
		}
		else
		{
			count_expr = sema->ActOnIntLiteral(1, loc);
		}

		return sema->ActOnNewExpr(loc, alloc_type, std::move(count_expr), has_ctor_args, std::move(ctor_args));
	}

	UniqueExprPtr Parser::ParseDeleteExpression()
	{
		OLA_ASSERT(current_token->Is(TokenKind::KW_delete));
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		UniqueExprPtr ptr_expr = ParseUnaryExpression();

		return sema->ActOnDeleteExpr(loc, std::move(ptr_expr));
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
				if (current_token->Is(TokenKind::left_brace))
				{
					expr_list.push_back(ParseInitializerListExpression());
				}
				else
				{
					expr_list.push_back(ParseAssignmentExpression());
				}

				if (Consume(TokenKind::right_brace))
				{
					break;
				}
				Expect(TokenKind::comma);
			}
		}
		return sema->ActOnInitializerListExpr(loc, std::move(expr_list));
	}

	void Parser::ParseFunctionAttributes(Uint8& attrs)
	{
		auto FunctionAttributeParseHelper = [this](Uint8& attrs, FuncAttribute attr) 
		{
			if (!HasAttribute(attrs, attr))
			{
				attrs |= attr;
			}
			else
			{
				Diag(function_attribute_repetition);
				return false;
			}
			return true;
		};

		while (current_token->IsFunctionAttribute())
		{
			if (Consume(TokenKind::KW_inline))
			{
				if (!FunctionAttributeParseHelper(attrs, FuncAttribute_Inline))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_noinline))
			{
				if (!FunctionAttributeParseHelper(attrs, FuncAttribute_NoInline))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_nomangle))
			{
				if (!FunctionAttributeParseHelper(attrs, FuncAttribute_NoMangle))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_noopt))
			{
				if (!FunctionAttributeParseHelper(attrs, FuncAttribute_NoOpt))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_deprecated))
			{
				if (!FunctionAttributeParseHelper(attrs, FuncAttribute_Deprecated))
				{
					return;
				}
			}
		}
	}

	void Parser::ParseMethodAttributes(Uint8& attrs)
	{
		auto MethodAttributeParseHelper = [this](Uint8& attrs, MethodAttribute attr)
		{
			if (!HasAttribute(attrs, attr))
			{
				attrs |= attr;
			}
			else
			{
				Diag(method_attribute_repetition);
				return false;
			}
			return true;
		};

		while (current_token->IsMethodAttribute())
		{
			if (Consume(TokenKind::KW_const))
			{
				if (!MethodAttributeParseHelper(attrs, MethodAttribute_Const))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_virtual))
			{
				if (!MethodAttributeParseHelper(attrs, MethodAttribute_Virtual))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_pure))
			{
				if (!MethodAttributeParseHelper(attrs, MethodAttribute_Pure))
				{
					return;
				}
			}
			else if (Consume(TokenKind::KW_final))
			{
				if (!MethodAttributeParseHelper(attrs, MethodAttribute_Final))
				{
					return;
				}
			}
		}
	}

	void Parser::ParseTypeQualifier(QualType& type)
	{
		if (Consume(TokenKind::KW_const))
		{
			type.AddConst();
		}
	}

	void Parser::ParseTypeSpecifier(QualType& type, Bool array_size_forbidden, Bool allow_ref)
	{
		Bool is_ref = false;
		if (allow_ref)
		{
			is_ref = Consume(TokenKind::KW_ref);
		}

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
			if (TagDecl* tag_decl = sema->sema_ctx.tag_sym_table.Lookup(identifier))
			{
				if (isa<EnumDecl>(tag_decl))
				{
					type.SetType(IntType::Get(context));
				}
				else if (isa<AliasDecl>(tag_decl))
				{
					Bool const is_const = type.IsConst();
					type = tag_decl->GetType();
					if (is_const)
					{
						type.AddConst();
					}
				}
				else if (isa<ClassDecl>(tag_decl))
				{
					ClassDecl* class_decl = cast<ClassDecl>(tag_decl);
					type.SetType(ClassType::Get(context, class_decl));
				}
				else if (isa<TemplateClassDecl>(tag_decl))
				{
					TemplateClassDecl* tmpl = cast<TemplateClassDecl>(tag_decl);
					++current_token;
					ClassDecl* specialized = ParseTemplateInstantiation(tmpl, current_token->GetLocation());
					if (specialized)
					{
						type.SetType(ClassType::Get(context, specialized));
					}

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

					if (Consume(TokenKind::star))
					{
						if (isa<VoidType>(type))
						{
							Diag(invalid_type_specifier);
							return;
						}
						type.SetType(PtrType::Get(context, type));
					}

					if (is_ref)
					{
						Bool is_const = type.IsConst();
						type.RemoveConst();
						type = QualType(RefType::Get(context, type), is_const ? Qualifier_Const : Qualifier_None);
					}
					return;
				}
				else
				{
					Diag(invalid_type_specifier);
				}
			}
			else
			{
				Diag(invalid_type_specifier);
			}
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

		if (Consume(TokenKind::star))
		{
			if (isa<VoidType>(type))
			{
				Diag(invalid_type_specifier);
				return;
			}
			type.SetType(PtrType::Get(context, type));
		}

		if (is_ref)
		{
			Bool is_const = type.IsConst();
			type.RemoveConst();
			type = QualType(RefType::Get(context, type), is_const ? Qualifier_Const : Qualifier_None);
		}
	}

	void Parser::ParseBaseType(QualType& type)
	{
		switch (current_token->GetKind())
		{
		case TokenKind::KW_bool:  type.SetType(BoolType::Get(context));  break;
		case TokenKind::KW_char:  type.SetType(CharType::Get(context));  break;
		case TokenKind::KW_int:   type.SetType(IntType::Get(context));   break;
		case TokenKind::KW_float: type.SetType(FloatType::Get(context)); break;
		case TokenKind::identifier:
		{
			std::string_view identifier = current_token->GetData();
			TagDecl* tag_decl = sema->sema_ctx.tag_sym_table.Lookup(identifier);
			if (tag_decl && isa<AliasDecl>(tag_decl))
			{
				type = tag_decl->GetType();
			}
			else if (tag_decl && isa<ClassDecl>(tag_decl))
			{
				type.SetType(ClassType::Get(context, cast<ClassDecl>(tag_decl)));
			}
			else if (tag_decl && isa<TemplateClassDecl>(tag_decl))
			{
				TemplateClassDecl* tmpl = cast<TemplateClassDecl>(tag_decl);
				++current_token;
				ClassDecl* specialized = ParseTemplateInstantiation(tmpl, current_token->GetLocation());
				if (specialized)
				{
					type.SetType(ClassType::Get(context, specialized));
				}
				return;
			}
			else
			{
				Diag(invalid_type_specifier);
			}
		}
		break;
		default:
			Diag(invalid_type_specifier);
			return;
		}
		++current_token;
	}

	Bool Parser::IsFunctionDeclaration()
	{
		TokenPtr token = current_token;

		Consume(TokenKind::KW_public, TokenKind::KW_private);
		Consume(TokenKind::KW_static);
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
		if (Consume(TokenKind::KW_noopt))
		{
			current_token = token;
			return true;
		}
		if (Consume(TokenKind::KW_deprecated))
		{
			current_token = token;
			return true;
		}

		QualType tmp{};
		ParseTypeQualifier(tmp);

		// Check for template function with unknown return type: identifier identifier <
		if (current_token->Is(TokenKind::identifier) &&
			(current_token + 1)->Is(TokenKind::identifier) &&
			(current_token + 2)->Is(TokenKind::less))
		{
			current_token = token;
			return true;
		}

		ParseTypeSpecifier(tmp);
		Expect(TokenKind::identifier);

		Bool is_function = Consume(TokenKind::left_round) || Consume(TokenKind::less);
		current_token = token;
		return is_function;
	}

	Bool Parser::IsCurrentTokenTypename()
	{
		return current_token->IsTypename() || sema->sema_ctx.tag_sym_table.Lookup(current_token->GetData()) != nullptr;
	}

	Bool Parser::Consume(TokenKind k)
	{
		if (current_token->Is(k))
		{
			++current_token; return true;
		}
		return false;
	}
	template<typename... Ts>
	Bool Parser::Consume(TokenKind k, Ts... ts)
	{
		if (current_token->IsOneOf(k, ts...))
		{
			++current_token; return true;
		}
		return false;
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
		diagnostics.Report(current_token->GetLocation(), code);
	}
	template<typename... Ts>
	void Parser::Diag(DiagCode code, Ts&&... args)
	{
		diagnostics.Report(code, current_token->GetLocation(), std::forward<Ts>(args)...);
	}
}