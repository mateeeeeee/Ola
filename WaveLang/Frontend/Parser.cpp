#include "Parser.h"
#include "Diagnostics.h"
#include "AST.h"
#include "Sema.h"

namespace wave
{

	Parser::Parser(Diagnostics& diagnostics, std::vector<Token> const& _tokens) 
		: diagnostics(diagnostics), tokens(_tokens), current_token(tokens.begin()) {}
	Parser::~Parser() = default;

	void Parser::Parse()
	{
		sema = MakeUnique<Sema>(diagnostics);
		ast = MakeUnique<AST>();
		PreprocessTokens();
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

	void Parser::PreprocessTokens()
	{
		std::vector<Token> preprocessed_tokens{};
		for (auto const& token : tokens)
		{
			if (!token.IsOneOf(TokenKind::comment, TokenKind::newline)) preprocessed_tokens.push_back(token);
		}
		//#todo resolve import *.wvi 
		std::swap(preprocessed_tokens, tokens);
		current_token = tokens.begin();
	}

	void Parser::ParseTranslationUnit()
	{
		while (current_token->IsNot(TokenKind::eof))
		{
			ast->translation_unit->AddDeclaration(ParseGlobalDeclaration());
		}
	}

	UniqueDeclPtr Parser::ParseGlobalDeclaration()
	{
		while (Consume(TokenKind::semicolon)) Diag(empty_statement);
		if (Consume(TokenKind::KW_extern))
		{
			if (!Consume(TokenKind::KW_fn)) Diag(missing_fn);
			return ParseFunctionDeclaration();
		}
		else if (Consume(TokenKind::KW_fn))
		{
			return ParseFunctionDefinition();
		}
		else Diag(missing_fn);
		return nullptr;
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDeclaration(bool expect_semicolon)
	{
		if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = current_token->GetIdentifier(); ++current_token;
		Expect(TokenKind::left_round);
		QualifiedType function_type{};
		UniqueVariableDeclPtrList param_decls;
		if (Consume(TokenKind::right_round))
		{
			if (Consume(TokenKind::arrow))
			{
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
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(function_params_missing_coma);

				QualifiedType param_type{};
				ParseTypeQualifier(param_type);

				if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
				std::string_view identifier = current_token->GetIdentifier(); ++current_token;

				Expect(TokenKind::colon);
				ParseTypeSpecifier(param_type);
				if (!param_type.HasRawType()) Diag(missing_type_specifier);
				if (param_type->Is(TypeKind::Void)) Diag(void_invalid_context);

				UniqueVariableDeclPtr param_decl = ParseVariableDeclaration(true);
				param_decl->SetType(param_type);
				param_decls.push_back(std::move(param_decl));
				param_types.emplace_back(std::string(identifier), param_type);
			}

			QualifiedType return_type{};
			if (Consume(TokenKind::arrow))
			{
				ParseTypeSpecifier(return_type);
			}
			else return_type = builtin_types::Void;
			function_type.SetRawType(FunctionType(return_type, param_types));
		}
		if (expect_semicolon) Expect(TokenKind::semicolon);
		return sema->ActOnFunctionDecl(name, function_type, loc, std::move(param_decls));
	}

	UniqueFunctionDeclPtr Parser::ParseFunctionDefinition()
	{
		SCOPE_STACK_GUARD(sema->ctx.decl_scope_stack);
		UniqueFunctionDeclPtr function_decl = ParseFunctionDeclaration(false);
		sema->ctx.current_func = &function_decl->GetType();
		UniqueCompoundStmtPtr function_body = ParseCompoundStatement();
		sema->ctx.current_func = nullptr;
		sema->ActOnFunctionDecl(function_decl, std::move(function_body));
		return function_decl;
	}

	UniqueVariableDeclPtr Parser::ParseVariableDeclaration(bool function_param_decl)
	{
		while (Consume(TokenKind::semicolon)) Diag(empty_statement);

		QualifiedType variable_type{};
		ParseTypeQualifier(variable_type);
		if (current_token->IsNot(TokenKind::identifier)) Diag(expected_identifier);
		SourceLocation const& loc = current_token->GetLocation();
		std::string_view name = current_token->GetIdentifier(); ++current_token;
		UniqueExprPtr init_expr = nullptr;
		if (function_param_decl)
		{
			Expect(TokenKind::colon);
			ParseTypeSpecifier(variable_type);
			if (!variable_type.HasRawType()) Diag(missing_type_specifier);
			if (variable_type->Is(TypeKind::Void)) Diag(void_invalid_context);
		}
		else
		{
			if (Consume(TokenKind::colon)) ParseTypeSpecifier(variable_type);
			if (Consume(TokenKind::equal)) init_expr = ParseExpression();
			Expect(TokenKind::semicolon);
		}
		return sema->ActOnVariableDecl(name, variable_type, loc, std::move(init_expr));
	}

	UniqueStmtPtr Parser::ParseStatement()
	{
		switch (current_token->GetKind())
		{
		case TokenKind::left_brace: return ParseCompoundStatement();
		case TokenKind::KW_return: return ParseReturnStatement();
		//case TokenKind::KW_if: return ParseIfStatement();
		//case TokenKind::KW_while: return ParseWhileStatement();
		//case TokenKind::KW_for: return ParseForStatement();
		//case TokenKind::KW_do: return ParseDoWhileStatement();
		//case TokenKind::KW_continue: return ParseContinueStatement();
		//case TokenKind::KW_break: return ParseBreakStatement();
		//case TokenKind::KW_goto: return ParseGotoStatement();
		//case TokenKind::KW_switch: return ParseSwitchStatement();
		//case TokenKind::KW_case:
		//case TokenKind::KW_default: return ParseCaseStatement();
		//case TokenKind::identifier:
		//	if ((current_token + 1)->Is(TokenKind::colon)) return ParseLabelStatement();
		default:
			return ParseExpressionStatement();
		}
		return nullptr;
	}

	UniqueCompoundStmtPtr Parser::ParseCompoundStatement()
	{
		SCOPE_STACK_GUARD(sema->ctx.decl_scope_stack);
		Expect(TokenKind::left_brace);
		UniqueCompoundStmtPtr compound_stmt = MakeUnique<CompoundStmtAST>();
		while (current_token->IsNot(TokenKind::right_brace))
		{
			if (Consume(TokenKind::KW_let))
			{
				UniqueVariableDeclPtr decl = ParseVariableDeclaration(false);
				compound_stmt->AddStatement(MakeUnique<DeclStmtAST>(std::move(decl)));
			}
			else
			{
				UniqueStmtPtr stmt = ParseStatement();
				compound_stmt->AddStatement(std::move(stmt));
			}
		}
		Expect(TokenKind::right_brace);
		return compound_stmt;
	}

	UniqueExprStmtPtr Parser::ParseExpressionStatement()
	{
		if (Consume(TokenKind::semicolon)) return MakeUnique<NullStmtAST>();
		UniqueExprPtr expression = ParseExpression();
		Expect(TokenKind::semicolon);
		return MakeUnique<ExprStmtAST>(std::move(expression));
	}

	UniqueReturnStmtPtr Parser::ParseReturnStatement()
	{
		Expect(TokenKind::KW_return);
		UniqueExprStmtPtr ret_expr_stmt = ParseExpressionStatement();
		UniqueReturnStmtPtr return_stmt = MakeUnique<ReturnStmtAST>(std::move(ret_expr_stmt));
		return return_stmt;
	}

	template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
	UniqueExprPtr Parser::ParseBinaryExpression()
	{
		UniqueExprPtr lhs = (this->*ParseFn)();
		while (Consume(token_kind))
		{
			SourceLocation loc = current_token->GetLocation();
			UniqueExprPtr rhs = (this->*ParseFn)();
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
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

			UniqueBinaryExprPtr tmp = MakeUnique<BinaryExprAST>(arith_op_kind, loc);
			tmp->SetLHS(std::move(lhs_copy));
			tmp->SetRHS(std::move(rhs));

			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(BinaryExprKind::Assign, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(tmp));
			return parent;
		}
		else
		{
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(arith_op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			return parent;
		}
	}

	UniqueExprPtr Parser::ParseConditionalExpression()
	{
		SourceLocation loc = current_token->GetLocation();
		UniqueExprPtr cond = ParseLogicalOrExpression();
		if (Consume(TokenKind::question))
		{
			UniqueTernaryExprPtr ternary_expr = MakeUnique<TernaryExprAST>(loc);
			ternary_expr->SetCondition(std::move(cond));
			ternary_expr->SetTrueExpr(ParseExpression());
			Expect(TokenKind::colon);
			ternary_expr->SetFalseExpr(ParseConditionalExpression());
			return ternary_expr;
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
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
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
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
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
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
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
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseMultiplicativeExpression()
	{
		UniqueExprPtr lhs = ParseCastExpression();
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
			UniqueExprPtr rhs = ParseCastExpression();
			UniqueBinaryExprPtr parent = MakeUnique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	UniqueExprPtr Parser::ParseCastExpression()
	{
		if (current_token->Is(TokenKind::left_round) && (current_token + 1)->IsType())
		{
			Expect(TokenKind::left_round);
			QualifiedType cast_type{};
			ParseTypeSpecifier(cast_type);
			Expect(TokenKind::right_round);

			SourceLocation loc = current_token->GetLocation();
			UniqueCastExprPtr cast_expr = MakeUnique<CastExprAST>(loc, cast_type);
			cast_expr->SetOperand(ParseCastExpression());
			return cast_expr;
		}
		else return ParseUnaryExpression();
	}

	UniqueExprPtr Parser::ParseUnaryExpression()
	{
		UniqueUnaryExprPtr unary_expr;
		SourceLocation loc = current_token->GetLocation();
		switch (current_token->GetKind())
		{
		case TokenKind::plus_plus:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::PreIncrement, loc);
			break;
		case TokenKind::minus_minus:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::PreDecrement, loc);
			break;
		case TokenKind::plus:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::Plus, loc);
			break;
		case TokenKind::minus:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::Minus, loc);
			break;
		case TokenKind::tilde:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::BitNot, loc);
			break;
		case TokenKind::exclaim:
			unary_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::LogicalNot, loc);
			break;
		case TokenKind::KW_sizeof: return ParseSizeofExpression();
		case TokenKind::KW_alignof: return ParseAlignofExpression();
		case TokenKind::KW_alignas: return ParseAlignasExpression();
		default:
			return ParsePostFixExpression();
		}
		++current_token;
		unary_expr->SetOperand(ParseUnaryExpression());
		return unary_expr;
	}

	UniqueExprPtr Parser::ParsePostFixExpression()
	{
		UniqueExprPtr expr = ParsePrimaryExpression();

		SourceLocation loc = current_token->GetLocation();
		switch (current_token->GetKind())
		{
		case TokenKind::left_round:
		{
			UniqueFunctionCallExprPtr func_call_expr = MakeUnique<FunctionCallExprAST>(std::move(expr), current_token->GetLocation());
			++current_token;

			if (!Consume(TokenKind::right_round))
			{
				while (true)
				{
					UniqueExprPtr arg_expr = ParseAssignmentExpression();
					func_call_expr->AddArgument(std::move(arg_expr));
					if (Consume(TokenKind::right_round)) break;
					Expect(TokenKind::comma);
				}
			}
			return func_call_expr;
		}
		case TokenKind::plus_plus:
		{
			++current_token;
			UniqueUnaryExprPtr post_inc_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::PostIncrement, loc);
			post_inc_expr->SetOperand(std::move(expr));
			return post_inc_expr;
		}
		case TokenKind::minus_minus:
		{
			++current_token;
			UniqueUnaryExprPtr post_dec_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::PostDecrement, loc);
			post_dec_expr->SetOperand(std::move(expr));
			return post_dec_expr;
		}
		case TokenKind::left_square:
		{
			++current_token;
			UniqueExprPtr bracket_expr = ParseExpression();
			Expect(TokenKind::right_square);

			UniqueUnaryExprPtr dereference_expr = MakeUnique<UnaryExprAST>(UnaryExprKind::Dereference, loc);
			UniqueBinaryExprPtr add_expr = MakeUnique<BinaryExprAST>(BinaryExprKind::Add, loc);
			add_expr->SetLHS(std::move(expr));
			add_expr->SetRHS(std::move(bracket_expr));
			dereference_expr->SetOperand(std::move(add_expr));
			return dereference_expr;
		}
		}
		return expr;
	}

	UniqueExprPtr Parser::ParseSizeofExpression()
	{
		return nullptr;
	}

	UniqueIntLiteralPtr Parser::ParseAlignofExpression()
	{
		return nullptr;
	}

	UniqueIntLiteralPtr Parser::ParseAlignasExpression()
	{
		return nullptr;
	}

	UniqueExprPtr Parser::ParsePrimaryExpression()
	{
		switch (current_token->GetKind())
		{
		case TokenKind::left_round: return ParseParenthesizedExpression();
		case TokenKind::identifier: return ParseIdentifier(); break;
		case TokenKind::number: return ParseIntegerLiteral();
		case TokenKind::string_literal: return ParseStringLiteral(); break;
		default:
			Diag(unexpected_token);
		}
		WAVE_ASSERT(false);
		return nullptr;
	}

	UniqueIntLiteralPtr Parser::ParseIntegerLiteral()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::number));
		std::string_view string_number = current_token->GetIdentifier();
		int64 value = std::stoll(current_token->GetIdentifier().data(), nullptr, 0);
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return MakeUnique<IntLiteralAST>(value, loc);
	}

	UniqueStringLiteralPtr Parser::ParseStringLiteral()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::string_literal));
		std::string_view str = current_token->GetIdentifier();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		return MakeUnique<StringLiteralAST>(str, loc);
	}

	UniqueIdentifierPtr Parser::ParseIdentifier()
	{
		WAVE_ASSERT(current_token->Is(TokenKind::identifier));
		std::string_view name = current_token->GetIdentifier();
		SourceLocation loc = current_token->GetLocation();
		++current_token;
		UniqueIdentifierPtr identifier = MakeUnique<IdentifierAST>(name, loc);
		return identifier;
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
				//#todo parse constant-expression
				Expect(TokenKind::right_square);
			}
		}
	}
}