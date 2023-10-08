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
		PreprocessTokens();
		ParseTranslationUnit();
	}

	bool Parser::Expect(TokenKind k)
	{
		if (!Consume(k))
		{
			Diag(diag::unexpected_token);
			return false;
		}
		return true;
	}

	void Parser::Diag(diag::DiagCode code)
	{
		--current_token;
		diag::Diag(code, current_token->GetLocation());
		++current_token;
	}

	void Parser::PreprocessTokens()
	{
		std::vector<Token> preprocessed_tokens{};
		for (auto const& token : tokens)
		{
			if (!token.IsOneOf(TokenKind::comment, TokenKind::newline)) preprocessed_tokens.push_back(token);
		}
		//resolve import *.wvi 
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

	std::unique_ptr<DeclAST> Parser::ParseGlobalDeclaration()
	{
		while (Consume(TokenKind::semicolon)) Diag(diag::empty_statement);
		if (Consume(TokenKind::KW_extern))
		{
			if (!Consume(TokenKind::KW_fn)) Diag(diag::missing_fn);
			return ParseFunctionDeclaration();
		}
		else if (Consume(TokenKind::KW_fn))
		{
			return ParseFunctionDefinition();
		}
		else Diag(diag::missing_fn);
		return nullptr;
	}

	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDeclaration(bool expect_semicolon)
	{
		if (current_token->IsNot(TokenKind::identifier)) Diag(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		Expect(TokenKind::left_round);
		std::unique_ptr<FunctionDeclAST> function_decl = std::make_unique<FunctionDeclAST>(identifier, current_token->GetLocation());
		QualifiedType function_type{};

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
				if (!param_types.empty() && !Consume(TokenKind::comma)) Diag(diag::function_params_missing_coma);

				QualifiedType param_type{};
				ParseTypeQualifier(param_type);

				if (current_token->IsNot(TokenKind::identifier)) Diag(diag::expected_identifier);
				std::string_view identifier = current_token->GetIdentifier(); ++current_token;

				Expect(TokenKind::colon);
				ParseTypeSpecifier(param_type);
				if (!param_type.HasRawType()) Diag(diag::missing_type_specifier);
				if (param_type->Is(TypeKind::Void)) Diag(diag::void_invalid_context);

				std::unique_ptr<VariableDeclAST> param_decl = ParseVariableDeclaration(true);
				param_decl->SetType(param_type);
				function_decl->AddParamDeclaration(std::move(param_decl));

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
		function_decl->SetType(function_type);

		return function_decl;
	}

	std::unique_ptr<FunctionDeclAST> Parser::ParseFunctionDefinition()
	{
		std::unique_ptr<FunctionDeclAST> function_decl = ParseFunctionDeclaration(false);
		std::unique_ptr<CompoundStmtAST> function_body = ParseCompoundStatement();
		function_decl->SetDefinition(std::move(function_body));
		return function_decl;
	}

	std::unique_ptr<VariableDeclAST> Parser::ParseVariableDeclaration(bool function_param_decl)
	{
		while (Consume(TokenKind::semicolon)) Diag(diag::empty_statement);

		QualifiedType param_type{};
		ParseTypeQualifier(param_type);
		if (current_token->IsNot(TokenKind::identifier)) Diag(diag::expected_identifier);
		std::string_view identifier = current_token->GetIdentifier(); ++current_token;

		std::unique_ptr<VariableDeclAST> variable_decl = std::make_unique<VariableDeclAST>(identifier, current_token->GetLocation());
		if (function_param_decl)
		{
			Expect(TokenKind::colon);
			ParseTypeSpecifier(param_type);
			if (!param_type.HasRawType()) Diag(diag::missing_type_specifier);
			if (param_type->Is(TypeKind::Void)) Diag(diag::void_invalid_context);
		}
		else
		{
			if (Consume(TokenKind::colon)) ParseTypeSpecifier(param_type);
			if (Consume(TokenKind::equal))
			{
				std::unique_ptr<ExprAST> init_expr = ParseExpression();
				variable_decl->SetInitExpression(std::move(init_expr));
			}
			Expect(TokenKind::semicolon);
		}
		variable_decl->SetType(param_type);
		return variable_decl;
	}

	std::unique_ptr<StmtAST> Parser::ParseStatement()
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

	std::unique_ptr<CompoundStmtAST> Parser::ParseCompoundStatement()
	{
		Expect(TokenKind::left_brace);
		std::unique_ptr<CompoundStmtAST> compound_stmt = std::make_unique<CompoundStmtAST>();
		while (current_token->IsNot(TokenKind::right_brace))
		{
			if (Consume(TokenKind::KW_let))
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

	std::unique_ptr<ExprStmtAST> Parser::ParseExpressionStatement()
	{
		if (Consume(TokenKind::semicolon)) return std::make_unique<NullStmtAST>();
		std::unique_ptr<ExprAST> expression = ParseExpression();
		Expect(TokenKind::semicolon);
		return std::make_unique<ExprStmtAST>(std::move(expression));
	}

	std::unique_ptr<ReturnStmtAST> Parser::ParseReturnStatement()
	{
		Expect(TokenKind::KW_return);
		std::unique_ptr<ExprStmtAST> ret_expr_stmt = ParseExpressionStatement();
		return std::make_unique<ReturnStmtAST>(std::move(ret_expr_stmt));
	}

	template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
	std::unique_ptr<ExprAST> Parser::ParseBinaryExpression()
	{
		std::unique_ptr<ExprAST> lhs = (this->*ParseFn)();
		while (Consume(token_kind))
		{
			SourceLocation loc = current_token->GetLocation();
			std::unique_ptr<ExprAST> rhs = (this->*ParseFn)();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
		return lhs;
	}


	std::unique_ptr<ExprAST> Parser::ParseExpression()
	{
		return ParseBinaryExpression<&Parser::ParseAssignmentExpression, TokenKind::comma, BinaryExprKind::Comma>();
	}

	std::unique_ptr<ExprAST> Parser::ParseParenthesizedExpression()
	{
		Expect(TokenKind::left_round);
		std::unique_ptr<ExprAST> expr = ParseExpression();
		Expect(TokenKind::right_round);
		return expr;
	}

	std::unique_ptr<ExprAST> Parser::ParseAssignmentExpression()
	{
		TokenPtr current_token_copy = current_token;
		std::unique_ptr<ExprAST> lhs = ParseConditionalExpression();
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
		std::unique_ptr<ExprAST> rhs = ParseAssignmentExpression();
		if (arith_op_kind != BinaryExprKind::Assign)
		{
			//#todo: remove this hack, add clone to ast nodes
			TokenPtr current_token_copy2 = current_token;
			current_token = current_token_copy;
			std::unique_ptr<ExprAST> lhs_copy = ParseConditionalExpression();
			current_token = current_token_copy2;

			std::unique_ptr<BinaryExprAST> tmp = std::make_unique<BinaryExprAST>(arith_op_kind, loc);
			tmp->SetLHS(std::move(lhs_copy));
			tmp->SetRHS(std::move(rhs));

			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(BinaryExprKind::Assign, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(tmp));
			return parent;
		}
		else
		{
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(arith_op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			return parent;
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseConditionalExpression()
	{
		SourceLocation loc = current_token->GetLocation();
		std::unique_ptr<ExprAST> cond = ParseLogicalOrExpression();
		if (Consume(TokenKind::question))
		{
			std::unique_ptr<TernaryExprAST> ternary_expr = std::make_unique<TernaryExprAST>(loc);
			ternary_expr->SetCondition(std::move(cond));
			ternary_expr->SetTrueExpr(ParseExpression());
			Expect(TokenKind::colon);
			ternary_expr->SetFalseExpr(ParseConditionalExpression());
			return ternary_expr;
		}
		return cond;
	}

	std::unique_ptr<ExprAST> Parser::ParseLogicalOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseLogicalAndExpression, TokenKind::pipe_pipe, BinaryExprKind::LogicalOr>();
	}

	std::unique_ptr<ExprAST> Parser::ParseLogicalAndExpression()
	{
		return ParseBinaryExpression<&Parser::ParseInclusiveOrExpression, TokenKind::amp_amp, BinaryExprKind::LogicalAnd>();
	}

	std::unique_ptr<ExprAST> Parser::ParseInclusiveOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseExclusiveOrExpression, TokenKind::pipe, BinaryExprKind::BitOr>();
	}

	std::unique_ptr<ExprAST> Parser::ParseExclusiveOrExpression()
	{
		return ParseBinaryExpression<&Parser::ParseAndExpression, TokenKind::caret, BinaryExprKind::BitXor>();
	}

	std::unique_ptr<ExprAST> Parser::ParseAndExpression()
	{
		return ParseBinaryExpression<&Parser::ParseEqualityExpression, TokenKind::amp, BinaryExprKind::BitAnd>();
	}

	std::unique_ptr<ExprAST> Parser::ParseEqualityExpression()
	{
		std::unique_ptr<ExprAST> lhs = ParseRelationalExpression();
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
			std::unique_ptr<ExprAST> rhs = ParseRelationalExpression();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseRelationalExpression()
	{
		std::unique_ptr<ExprAST> lhs = ParseShiftExpression();
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
			std::unique_ptr<ExprAST> rhs = ParseShiftExpression();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseShiftExpression()
	{
		std::unique_ptr<ExprAST> lhs = ParseAdditiveExpression();
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
			std::unique_ptr<ExprAST> rhs = ParseAdditiveExpression();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseAdditiveExpression()
	{
		std::unique_ptr<ExprAST> lhs = ParseMultiplicativeExpression();
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
			std::unique_ptr<ExprAST> rhs = ParseMultiplicativeExpression();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseMultiplicativeExpression()
	{
		std::unique_ptr<ExprAST> lhs = ParseCastExpression();
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
			std::unique_ptr<ExprAST> rhs = ParseCastExpression();
			std::unique_ptr<BinaryExprAST> parent = std::make_unique<BinaryExprAST>(op_kind, loc);
			parent->SetLHS(std::move(lhs));
			parent->SetRHS(std::move(rhs));
			lhs = std::move(parent);
		}
	}

	std::unique_ptr<ExprAST> Parser::ParseCastExpression()
	{
		if (current_token->Is(TokenKind::left_round) && (current_token + 1)->IsType())
		{
			Expect(TokenKind::left_round);
			QualifiedType cast_type{};
			ParseTypeSpecifier(cast_type);
			Expect(TokenKind::right_round);

			SourceLocation loc = current_token->GetLocation();
			std::unique_ptr<CastExprAST> cast_expr = std::make_unique<CastExprAST>(loc, cast_type);
			cast_expr->SetOperand(ParseCastExpression());
			return cast_expr;
		}
		else return ParseUnaryExpression();
	}

	std::unique_ptr<ExprAST> Parser::ParseUnaryExpression()
	{
		std::unique_ptr<UnaryExprAST> unary_expr;
		SourceLocation loc = current_token->GetLocation();
		switch (current_token->GetKind())
		{
		case TokenKind::plus_plus:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::PreIncrement, loc);
			break;
		case TokenKind::minus_minus:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::PreDecrement, loc);
			break;
		case TokenKind::plus:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::Plus, loc);
			break;
		case TokenKind::minus:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::Minus, loc);
			break;
		case TokenKind::tilde:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::BitNot, loc);
			break;
		case TokenKind::exclaim:
			unary_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::LogicalNot, loc);
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

	std::unique_ptr<ExprAST> Parser::ParsePostFixExpression()
	{
		std::unique_ptr<ExprAST> expr = ParsePrimaryExpression();

		SourceLocation loc = current_token->GetLocation();
		switch (current_token->GetKind())
		{
		case TokenKind::left_round:
		{
			std::unique_ptr<FunctionCallExprAST> func_call_expr = std::make_unique<FunctionCallExprAST>(std::move(expr), current_token->GetLocation());
			++current_token;

			if (!Consume(TokenKind::right_round))
			{
				while (true)
				{
					std::unique_ptr<ExprAST> arg_expr = ParseAssignmentExpression();
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
			std::unique_ptr<UnaryExprAST> post_inc_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::PostIncrement, loc);
			post_inc_expr->SetOperand(std::move(expr));
			return post_inc_expr;
		}
		case TokenKind::minus_minus:
		{
			++current_token;
			std::unique_ptr<UnaryExprAST> post_dec_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::PostDecrement, loc);
			post_dec_expr->SetOperand(std::move(expr));
			return post_dec_expr;
		}
		case TokenKind::left_square:
		{
			++current_token;
			std::unique_ptr<ExprAST> bracket_expr = ParseExpression();
			Expect(TokenKind::right_square);

			std::unique_ptr<UnaryExprAST> dereference_expr = std::make_unique<UnaryExprAST>(UnaryExprKind::Dereference, loc);
			std::unique_ptr<BinaryExprAST> add_expr = std::make_unique<BinaryExprAST>(BinaryExprKind::Add, loc);
			add_expr->SetLHS(std::move(expr));
			add_expr->SetRHS(std::move(bracket_expr));
			dereference_expr->SetOperand(std::move(add_expr));
			return dereference_expr;
		}
		}
		return expr;
	}

	std::unique_ptr<ExprAST> Parser::ParseSizeofExpression()
	{
		return nullptr;
	}

	std::unique_ptr<IntLiteralAST> Parser::ParseAlignofExpression()
	{
		return nullptr;
	}

	std::unique_ptr<IntLiteralAST> Parser::ParseAlignasExpression()
	{
		return nullptr;
	}

	std::unique_ptr<ExprAST> Parser::ParsePrimaryExpression()
	{
		return nullptr;
	}

	std::unique_ptr<IntLiteralAST> Parser::ParseIntegerLiteral()
	{
		return nullptr;
	}

	std::unique_ptr<StringLiteralAST> Parser::ParseStringLiteral()
	{
		return nullptr;
	}

	std::unique_ptr<ExprAST> Parser::ParseIdentifier()
	{
		return nullptr;
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
			Diag(diag::invalid_type_specifier);
			return;
		}
		++current_token;

		while (Consume(TokenKind::left_square))
		{
			if (type->Is(TypeKind::Void))
			{
				Diag(diag::invalid_type_specifier);
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