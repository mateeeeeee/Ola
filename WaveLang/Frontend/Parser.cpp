#include "Parser.h"
#include "Diagnostics.h"
#include "AST.h"
#include "Sema.h"

namespace wave
{

	Parser::Parser(Diagnostics& diagnostics) 
		: diagnostics(diagnostics) {}
	Parser::~Parser() = default;

	void Parser::Parse(std::vector<Token>&& _tokens)
	{
		tokens = std::move(_tokens);
		current_token = tokens.begin();
		sema = MakeUnique<Sema>(diagnostics);
		ast = MakeUnique<AST>();
		ParseTranslationUnit();
	}

	void Parser::Parse(std::vector<Token> const& _tokens)
	{
		tokens = _tokens;
		current_token = tokens.begin();
		sema = MakeUnique<Sema>(diagnostics);
		ast = MakeUnique<AST>();
		ParseTranslationUnit();
	}

	bool Parser::Expect(TokenKind k)
	{
		if (!Consume(k))
		{
			Diag(unexpected_token);
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

	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof))
		{
			UniqueDeclPtrList decls = ParseGlobalDeclaration();
			for(auto&& decl : decls) ast->translation_unit->AddDecl(std::move(decl));
		}
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
			if (IsFunctionDeclaration()) global_decl_list.push_back(ParseFunctionDefinition());
			else global_decl_list = ParseVariableDeclaration();
		}
		return global_decl_list;
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDeclaration()
	{
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualifiedType function_type{};
		UniqueVariableDeclPtrList param_decls;
		{
			SYM_TABLE_GUARD(sema->ctx.decl_sym_table);
			QualifiedType return_type{};
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);

			name = current_token->GetIdentifier(); ++current_token;
			Expect(TokenKind::left_round);

			std::vector<FunctionParameter> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueVariableDeclPtr param_decl = ParseParamDeclaration();
				param_types.emplace_back(std::string(param_decl->GetName()), param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetRawType(FunctionType(return_type, param_types));
			Expect(TokenKind::semicolon);
		}
		return sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls));
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDefinition()
	{
		DeclVisibility visibility = DeclVisibility::Private;
		if (Consume(TokenKind::KW_public)) visibility = DeclVisibility::Public;
		else if (Consume(TokenKind::KW_private)) visibility = DeclVisibility::Private;

		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		QualifiedType function_type{};
		UniqueVariableDeclPtrList param_decls;
		UniqueCompoundStmtPtr function_body;
		{
			SYM_TABLE_GUARD(sema->ctx.decl_sym_table);
			QualifiedType return_type{};
			ParseTypeSpecifier(return_type);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);

			SourceLocation const& loc = current_token->GetLocation();
			name = current_token->GetIdentifier(); ++current_token;
			Expect(TokenKind::left_round);

			std::vector<FunctionParameter> param_types{};
			while (!Consume(TokenKind::right_round))
			{
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				UniqueVariableDeclPtr param_decl = ParseParamDeclaration();
				param_types.emplace_back(std::string(param_decl->GetName()), param_decl->GetType());
				param_decls.push_back(std::move(param_decl));
			}
			function_type.SetRawType(FunctionType(return_type, param_types));

			sema->ctx.current_func = &function_type;
			function_body = ParseCompoundStatement();
			sema->ctx.current_func = nullptr;
		}
		return sema->ActOnFunctionDecl(name, loc, function_type, std::move(param_decls), std::move(function_body), visibility);
	}

	UniqueVariableDeclPtr Parser::ParseParamDeclaration()
	{
		QualifiedType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);

		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = "";
		if (current_token->Is(TokenKind::identifier))
		{
			name = current_token->GetIdentifier(); 
			++current_token;
		}

		if (!variable_type.HasRawType()) Diag(missing_type_specifier);
		if (variable_type->Is(TypeKind::Void)) Diag(void_invalid_context);

		return sema->ActOnVariableDecl(name, loc, variable_type, nullptr, DeclVisibility::None);
	}

	UniqueDeclPtrList Parser::ParseVariableDeclaration()
	{
		DeclVisibility visibility = DeclVisibility::None;
		if (Consume(TokenKind::KW_public)) visibility = DeclVisibility::Public;
		else if (Consume(TokenKind::KW_private)) visibility = DeclVisibility::Private;

		UniqueDeclPtrList var_decl_list;
		QualifiedType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do 
		{
			if (!var_decl_list.empty()) Expect(TokenKind::comma);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetIdentifier(); ++current_token;

			UniqueExprPtr init_expr = nullptr;
			if (Consume(TokenKind::equal)) init_expr = ParseAssignmentExpression();

			UniqueVariableDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, std::move(init_expr), visibility, false);
			var_decl_list.push_back(std::move(var_decl));

		} while (!Consume(TokenKind::semicolon));

		return var_decl_list;
	}

	UniqueDeclPtrList Parser::ParseExternVariableDeclaration()
	{
		UniqueDeclPtrList var_decl_list;
		QualifiedType variable_type{};
		ParseTypeQualifier(variable_type);
		ParseTypeSpecifier(variable_type);
		do
		{
			if (!var_decl_list.empty()) Expect(TokenKind::comma);
			if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
			SourceLocation const& loc = current_token->GetLocation();
			std::string_view name = current_token->GetIdentifier(); ++current_token;

			UniqueVariableDeclPtr var_decl = sema->ActOnVariableDecl(name, loc, variable_type, nullptr, DeclVisibility::Public, true);
			var_decl_list.push_back(std::move(var_decl));

		} while (!Consume(TokenKind::semicolon));

		return var_decl_list;
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
		case TokenKind::KW_while: return ParseWhileStatement();
		case TokenKind::KW_do: return ParseDoWhileStatement();
		case TokenKind::KW_switch: return ParseSwitchStatement();
		case TokenKind::KW_case:
		case TokenKind::KW_default: return ParseCaseStatement();
		case TokenKind::KW_goto: return ParseGotoStatement();
		case TokenKind::identifier:
			if ((current_token + 1)->Is(TokenKind::colon)) return ParseLabelStatement();
			return ParseExpressionStatement();
		}
		return nullptr;
	}

	UniqueCompoundStmtPtr Parser::ParseCompoundStatement()
	{
		SYM_TABLE_GUARD(sema->ctx.decl_sym_table);
		Expect(TokenKind::left_brace);
		UniqueStmtPtrList stmts;
		while (current_token->IsNot(TokenKind::right_brace))
		{
			if (current_token->IsTypename())
			{
				UniqueDeclPtrList decl_list = ParseVariableDeclaration();
				stmts.push_back(sema->ActOnDeclStmt(std::move(decl_list)));
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

		SYM_TABLE_GUARD(sema->ctx.decl_sym_table);
		UniqueStmtPtr init_stmt = nullptr;
		if (current_token->IsTypename())
		{
			UniqueDeclPtrList decl_list = ParseVariableDeclaration();
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

		sema->ctx.stmts_using_break_count++;
		sema->ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->ctx.stmts_using_continue_count--;
		sema->ctx.stmts_using_break_count--;

		return sema->ActOnForStmt(std::move(init_stmt), std::move(cond_expr), std::move(iter_expr), std::move(body_stmt));
	}

	UniqueWhileStmtPtr Parser::ParseWhileStatement()
	{
		Expect(TokenKind::KW_while);
		UniqueExprPtr cond_expr = ParseParenthesizedExpression();
		sema->ctx.stmts_using_break_count++;
		sema->ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->ctx.stmts_using_continue_count--;
		sema->ctx.stmts_using_break_count--;
		return sema->ActOnWhileStmt(std::move(cond_expr), std::move(body_stmt));
	}

	UniqueDoWhileStmtPtr Parser::ParseDoWhileStatement()
	{
		Expect(TokenKind::KW_do);
		sema->ctx.stmts_using_break_count++;
		sema->ctx.stmts_using_continue_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->ctx.stmts_using_continue_count--;
		sema->ctx.stmts_using_break_count--;
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
		CaseStmtPtrList case_stmts{};
		sema->ctx.case_callback_stack.push_back([&](CaseStmt* case_stmt) {case_stmts.push_back(case_stmt); });
		sema->ctx.stmts_using_break_count++;
		UniqueStmtPtr body_stmt = ParseStatement();
		sema->ctx.stmts_using_break_count--;
		sema->ctx.case_callback_stack.pop_back();
		return sema->ActOnSwitchStmt(loc, std::move(case_expr), std::move(body_stmt), {});
	}

	UniqueGotoStmtPtr Parser::ParseGotoStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		Expect(TokenKind::KW_goto);
		std::string_view label_name = current_token->GetIdentifier();
		Expect(TokenKind::identifier);
		Expect(TokenKind::semicolon);
		return sema->ActOnGotoStmt(loc, label_name);
	}

	UniqueLabelStmtPtr Parser::ParseLabelStatement()
	{
		SourceLocation loc = current_token->GetLocation();
		std::string_view label_name = current_token->GetIdentifier();
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
			return sema->ActOnFunctionCallExpr(loc, std::move(expr), std::move(args));
		}
		case TokenKind::plus_plus:
		{
			++current_token;
			return sema->ActOnUnaryExpr(UnaryExprKind::PostIncrement, loc, std::move(expr));
		}
		case TokenKind::minus_minus:
		{
			++current_token;
			return sema->ActOnUnaryExpr(UnaryExprKind::PostDecrement, loc, std::move(expr));
		}
		case TokenKind::left_square:
		{
			WAVE_ASSERT_MSG(false, "For now...");
		}
		}
		return expr;
	}

	UniqueExprPtr Parser::ParseSizeofExpression()
	{
		Expect(TokenKind::KW_sizeof);
		Expect(TokenKind::left_round);
		
		SourceLocation loc = current_token->GetLocation();
		QualifiedType type{};
		if (current_token->IsTypename() && current_token->IsNot(TokenKind::KW_var))
		{
			ParseTypeQualifier(type);
			ParseTypeSpecifier(type);
		}
		else
		{
			UniqueExprPtr sizeof_expr = ParseExpression();
			type = sizeof_expr->GetType();
		}
		Expect(TokenKind::right_round);
		return sema->ActOnConstantInt(type->GetSize(), loc);
	}

	UniqueExprPtr Parser::ParsePrimaryExpression()
	{
		switch (current_token->GetKind())
		{
		case TokenKind::left_round: return ParseParenthesizedExpression();
		case TokenKind::identifier: return ParseIdentifier(); 
		case TokenKind::int_number: return ParseConstantInt();
		case TokenKind::float_number: return ParseConstantFloat();
		case TokenKind::string_literal: return ParseConstantString(); 
		case TokenKind::KW_true:
		case TokenKind::KW_false:  return ParseConstantBool();

		default:
			Diag(unexpected_token);
		}
		WAVE_ASSERT(false);
		return nullptr;
	}

	UniqueConstantIntPtr Parser::ParseConstantInt()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::int_number));
		std::string_view string_number = current_token->GetIdentifier();
		int64 value = std::stoll(current_token->GetIdentifier().data(), nullptr, 0);
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnConstantInt(value, loc);
	}

	UniqueConstantStringPtr Parser::ParseConstantString()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::string_literal));
		std::string_view str = current_token->GetIdentifier();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnConstantString(str, loc);
	}

	UniqueConstantBoolPtr Parser::ParseConstantBool()
	{
		WAVE_ASSERT(current_token->IsOneOf(TokenKind::KW_true, TokenKind::KW_false));
		bool value = false;
		if (current_token->Is(TokenKind::KW_false)) value = false;
		else if (current_token->Is(TokenKind::KW_true)) value = true;
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnConstantBool(value, loc);
	}

	UniqueConstantFloatPtr Parser::ParseConstantFloat()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::float_number));
		std::string_view string_number = current_token->GetIdentifier();
		double value = std::stod(current_token->GetIdentifier().data(), nullptr);
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnConstantFloat(value, loc);
	}

	UniqueIdentifierExprPtr Parser::ParseIdentifier()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::identifier));
		std::string_view name = current_token->GetIdentifier();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return sema->ActOnIdentifier(name, loc);
	}

	void Parser::ParseTypeQualifier(QualifiedType& type)
	{
		if (Consume(TokenKind::KW_const))
		{
			type.AddConst();
		}
	}

	void Parser::ParseTypeSpecifier(QualifiedType& type)
	{
		switch (current_token->GetKind())
		{
		case TokenKind::KW_var:   break;
		case TokenKind::KW_void:  type.SetRawType(builtin_types::Void);  break;
		case TokenKind::KW_bool:  type.SetRawType(builtin_types::Bool);	 break;
		case TokenKind::KW_char:  type.SetRawType(builtin_types::Char);	 break;
		case TokenKind::KW_int:   type.SetRawType(builtin_types::Int);   break;
		case TokenKind::KW_float: type.SetRawType(builtin_types::Float); break;
		case TokenKind::identifier:
		{
			std::string_view identifier = current_token->GetIdentifier();
			WAVE_ASSERT(false); //#todo : check if it's enum or class
		}
		break;
		default:
			Diag(invalid_type_specifier);
			return;
		}
		++current_token;

		while (Consume(TokenKind::left_square))
		{
			if (type->Is(TypeKind::Void))
			{
				Diag(invalid_type_specifier);
				return;
			}

			if (Consume(TokenKind::right_square))
			{
				ArrayType array_type(type);
				type.SetRawType(array_type);
			}
			else
			{
				Expect(TokenKind::right_square);
			}
		}
	}

	bool Parser::IsFunctionDeclaration()
	{
		TokenPtr token = current_token;

		if (Consume(TokenKind::KW_public)) {}
		else if (Consume(TokenKind::KW_private)) {}

		QualifiedType tmp{};
		ParseTypeQualifier(tmp);
		ParseTypeSpecifier(tmp);
		Expect(TokenKind::identifier);

		bool is_function = false;
		if (Consume(TokenKind::left_round)) is_function = true;
		current_token = token;
		return is_function;
	}

}