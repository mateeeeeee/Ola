#include "Sema.h"
#include "Diagnostics.h"
#include "Type.h"

namespace wave
{
	Sema::Sema(Diagnostics& diagnostics) : diagnostics(diagnostics) {}
	Sema::~Sema() = default;

	UniqueVariableDeclPtr Sema::ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type, 
												  UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		return ActOnVariableDeclCommon<VariableDecl>(name, loc, type, std::move(init_expr), visibility);
	}

	UniqueParamVariableDeclPtr Sema::ActOnParamVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type)
	{
		if (!name.empty() && ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		if (type.IsNull())
		{
			diagnostics.Report(loc, missing_type_specifier);
		}
		if (type->Is(TypeKind::Void))
		{
			diagnostics.Report(loc, void_invalid_context);
		}

		UniqueParamVariableDeclPtr param_decl = MakeUnique<ParamVariableDecl>(name, loc);
		param_decl->SetGlobal(false);
		param_decl->SetVisibility(DeclVisibility::None);
		param_decl->SetType(type);
		if (!name.empty()) ctx.decl_sym_table.Insert(param_decl.get());
		return param_decl;
	}

	UniqueMemberVariableDeclPtr Sema::ActOnMemberVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		return ActOnVariableDeclCommon<MemberVariableDecl>(name, loc, type, std::move(init_expr), visibility);
	}

	UniqueFunctionDeclPtr Sema::ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
												  UniqueParamVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt, DeclVisibility visibility)
	{
		bool is_extern = body_stmt == nullptr;
		if (!is_extern && ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}

		FunctionType const* func_type = dynamic_type_cast<FunctionType>(type);
		WAVE_ASSERT(func_type);
		if (name == "main")
		{
			if (func_type->GetReturnType()->IsNot(TypeKind::Int) || !func_type->GetParameters().empty())
			{
				diagnostics.Report(loc, invalid_main_function_declaration);
			}
		}

		UniqueFunctionDeclPtr function_decl = MakeUnique<FunctionDecl>(name, loc);
		function_decl->SetType(type);
		function_decl->SetVisibility(visibility);
		function_decl->SetParamDecls(std::move(param_decls));
		if (body_stmt)
		{
			function_decl->SetBodyStmt(std::move(body_stmt));
			for (std::string const& goto_label : ctx.gotos)
			{
				if (!ctx.labels.contains(goto_label)) diagnostics.Report(loc, undeclared_label, goto_label);
			}
			ctx.gotos.clear();
			ctx.labels.clear();

			if (!ctx.return_stmt_encountered && func_type->GetReturnType()->IsNot(TypeKind::Void))
			{
				diagnostics.Report(loc, no_return_statement_found_in_non_void_function);
			}
			ctx.return_stmt_encountered = false;
		}

		bool result = ctx.decl_sym_table.Insert(function_decl.get());
		WAVE_ASSERT(result);
		return function_decl;
	}

	UniqueMemberFunctionDeclPtr Sema::ActOnMemberFunctionDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueParamVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt, DeclVisibility visibility, bool is_const)
	{
		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		FunctionType const* func_type = dynamic_type_cast<FunctionType>(type);
		WAVE_ASSERT(func_type);

		UniqueMemberFunctionDeclPtr member_function_decl = MakeUnique<MemberFunctionDecl>(name, loc);
		member_function_decl->SetType(type);
		member_function_decl->SetConst(is_const);
		member_function_decl->SetVisibility(visibility);
		member_function_decl->SetParamDecls(std::move(param_decls));
		WAVE_ASSERT(body_stmt);
		{
			member_function_decl->SetBodyStmt(std::move(body_stmt));
			for (std::string const& goto_label : ctx.gotos)
			{
				if (!ctx.labels.contains(goto_label)) diagnostics.Report(loc, undeclared_label, goto_label);
			}
			ctx.gotos.clear();
			ctx.labels.clear();

			if (!ctx.return_stmt_encountered && func_type->GetReturnType()->IsNot(TypeKind::Void))
			{
				diagnostics.Report(loc, no_return_statement_found_in_non_void_function);
			}
			ctx.return_stmt_encountered = false;
		}

		bool result = ctx.decl_sym_table.Insert(member_function_decl.get());
		return member_function_decl;
	}

	UniqueEnumDeclPtr Sema::ActOnEnumDecl(std::string_view name, SourceLocation const& loc, UniqueEnumMemberDeclPtrList&& enum_members)
	{
		if (!name.empty() && ctx.tag_sym_table.LookUpCurrentScope(name)) diagnostics.Report(loc, redefinition_of_identifier, name);
		UniqueEnumDeclPtr enum_decl = MakeUnique<EnumDecl>(name, loc);
		enum_decl->SetEnumMembers(std::move(enum_members));
		if (!name.empty()) ctx.tag_sym_table.Insert(enum_decl.get());
		return enum_decl;
	}

	UniqueEnumMemberDeclPtr Sema::ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, UniqueExprPtr&& enum_value_expr)
	{
		if (!enum_value_expr->IsConstexpr()) diagnostics.Report(loc, enumerator_value_not_constexpr, name);
		return ActOnEnumMemberDecl(name, loc, enum_value_expr->EvaluateConstexpr());
	}

	UniqueEnumMemberDeclPtr Sema::ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, int64 enum_value)
	{
		if (name.empty()) diagnostics.Report(loc, expected_identifier);
		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		UniqueEnumMemberDeclPtr enum_member = MakeUnique<EnumMemberDecl>(name, loc);
		enum_member->SetValue(enum_value);
		ctx.decl_sym_table.Insert(enum_member.get());
		return enum_member;
	}

	UniqueAliasDeclPtr Sema::ActOnAliasDecl(std::string_view name, SourceLocation const& loc, QualType const& type)
	{
		if (ctx.tag_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		if (type.IsNull())
		{
			diagnostics.Report(loc, aliasing_var_forbidden);
		}
		UniqueAliasDeclPtr alias_decl = MakeUnique<AliasDecl>(name, loc, type);

		ctx.tag_sym_table.Insert(alias_decl.get());
		return alias_decl;
	}

	UniqueClassDeclPtr Sema::ActOnClassDecl(std::string_view name, SourceLocation const& loc, UniqueMemberVariableDeclPtrList&& member_variables, UniqueMemberFunctionDeclPtrList&& member_functions)
	{
		//todo semantic analysis
		if (ctx.tag_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		UniqueClassDeclPtr class_decl = MakeUnique<ClassDecl>(name, loc);
		class_decl->SetMemberVariables(std::move(member_variables));
		class_decl->SetMemberFunctions(std::move(member_functions));
		ctx.tag_sym_table.Insert(class_decl.get());
		return class_decl;
	}

	UniqueCompoundStmtPtr Sema::ActOnCompoundStmt(UniqueStmtPtrList&& stmts)
	{
		return MakeUnique<CompoundStmt>(std::move(stmts));
	}

	UniqueExprStmtPtr Sema::ActOnExprStmt(UniqueExprPtr&& expr)
	{
		return MakeUnique<ExprStmt>(std::move(expr));
	}

	UniqueDeclStmtPtr Sema::ActOnDeclStmt(UniqueDeclPtr&& decl)
	{
		return MakeUnique<DeclStmt>(std::move(decl));
	}

	UniqueDeclStmtPtr Sema::ActOnDeclStmt(UniqueDeclPtrList&& decls)
	{
		return MakeUnique<DeclStmt>(std::move(decls));
	}

	UniqueReturnStmtPtr Sema::ActOnReturnStmt(UniqueExprStmtPtr&& expr_stmt)
	{
		WAVE_ASSERT(ctx.current_func);
		ctx.return_stmt_encountered = true;
		FunctionType const& func_type = type_cast<FunctionType>(*ctx.current_func);
		QualType const& return_type = func_type.GetReturnType();

		Expr const* ret_expr = expr_stmt->GetExpr();
		SourceLocation loc = ret_expr ? ret_expr->GetLocation() : SourceLocation{};

		QualType const& ret_expr_type = ret_expr ? ret_expr->GetType() : builtin_types::Void;
		if (!return_type->IsAssignableFrom(ret_expr_type))
		{
			diagnostics.Report(loc, incompatible_return_stmt_type);
		}
		else if (!return_type->IsSameAs(ret_expr_type))
		{
			UniqueExprPtr casted_ret_expr(expr_stmt->ReleaseExpr());
			casted_ret_expr = ActOnImplicitCastExpr(loc, return_type, std::move(casted_ret_expr));
			expr_stmt.reset(new ExprStmt(std::move(casted_ret_expr)));
		}
		return MakeUnique<ReturnStmt>(std::move(expr_stmt));
	}

	UniqueIfStmtPtr Sema::ActOnIfStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& then_stmt, UniqueStmtPtr&& else_stmt)
	{
		UniqueIfStmtPtr if_stmt = MakeUnique<IfStmt>();
		if_stmt->SetConditionExpr(std::move(cond_expr));
		if_stmt->SetThenStmt(std::move(then_stmt));
		if_stmt->SetElseStmt(std::move(else_stmt));
		return if_stmt;
	}

	UniqueBreakStmtPtr Sema::ActOnBreakStmt(SourceLocation const& loc)
	{	
		if (ctx.stmts_using_break_count == 0) diagnostics.Report(loc, stray_break);
		
		UniqueBreakStmtPtr break_stmt = MakeUnique<BreakStmt>();
		return break_stmt;
	}

	UniqueContinueStmtPtr Sema::ActOnContinueStmt(SourceLocation const& loc)
	{
		if (ctx.stmts_using_continue_count == 0) diagnostics.Report(loc, stray_continue);

		UniqueContinueStmtPtr continue_stmt = MakeUnique<ContinueStmt>();
		return continue_stmt;
	}

	UniqueForStmtPtr Sema::ActOnForStmt(UniqueStmtPtr&& init_stmt, UniqueExprPtr&& cond_expr, UniqueExprPtr&& iter_expr, UniqueStmtPtr&& body_stmt)
	{
		UniqueForStmtPtr for_stmt = MakeUnique<ForStmt>();
		for_stmt->SetInitStmt(std::move(init_stmt));
		for_stmt->SetCondExpr(std::move(cond_expr));
		for_stmt->SetIterExpr(std::move(iter_expr));
		for_stmt->SetBodyStmt(std::move(body_stmt));
		return for_stmt;
	}

	UniqueForStmtPtr Sema::ActOnForeachStmt(SourceLocation const& loc, UniqueVariableDeclPtr&& var_decl, UniqueIdentifierExprPtr&& array_identifier, UniqueStmtPtr&& body_stmt)
	{
		QualType arr_type = array_identifier->GetType();
		ArrayType const* array_type = dynamic_type_cast<ArrayType>(arr_type);
		if (!array_type)
		{
			diagnostics.Report(loc, non_array_expr_in_foreach);
			return nullptr;
		}

		static uint64 foreach_id = 0;
		std::string foreach_index_name = "__foreach_index" + std::to_string(foreach_id++);
		UniqueVariableDeclPtr foreach_index_decl = ActOnVariableDecl(foreach_index_name, loc, builtin_types::Int, ActOnConstantInt(0, loc), DeclVisibility::None);
		
		UniqueIdentifierExprPtr foreach_index_identifier = MakeUnique<DeclRefExpr>(foreach_index_decl.get(), loc);
		UniqueExprPtr cond_expr = ActOnBinaryExpr(BinaryExprKind::Less, loc, std::move(foreach_index_identifier), ActOnConstantInt(array_type->GetArraySize(), loc));
		foreach_index_identifier = MakeUnique<DeclRefExpr>(foreach_index_decl.get(), loc);
		UniqueExprPtr iter_expr = ActOnUnaryExpr(UnaryExprKind::PostIncrement, loc, std::move(foreach_index_identifier));
		foreach_index_identifier = MakeUnique<DeclRefExpr>(foreach_index_decl.get(), loc);

		QualType var_type = var_decl->GetType();
		if (!var_type.IsNull())
		{
			if (!var_type->IsSameAs(array_type->GetBaseType()))
			{
				diagnostics.Report(var_decl->GetLocation(), foreach_loop_type_mismatch);
			}
		}
		else var_decl->SetType(array_type->GetBaseType());
		WAVE_ASSERT(var_decl->GetInitExpr() == nullptr);
		var_decl->SetInitExpr(ActOnArrayAccessExpr(loc, std::move(array_identifier), MakeUnique<DeclRefExpr>(foreach_index_decl.get(), loc)));

		UniqueStmtPtr init_stmt = MakeUnique<DeclStmt>(std::move(foreach_index_decl));
		UniqueStmtPtr array_access_stmt = MakeUnique<DeclStmt>(std::move(var_decl));
		if (CompoundStmt* compound_stmt = dynamic_ast_cast<CompoundStmt>(body_stmt.get()))
		{
			compound_stmt->AddBeginStmt(std::move(array_access_stmt));
		}
		else
		{
			UniqueStmtPtrList stmts = {};
			stmts.push_back(std::move(array_access_stmt));
			stmts.push_back(std::move(body_stmt));
			body_stmt = ActOnCompoundStmt(std::move(stmts));
		}

		UniqueForStmtPtr foreach_stmt = MakeUnique<ForStmt>();
		foreach_stmt->SetInitStmt(std::move(init_stmt));
		foreach_stmt->SetCondExpr(std::move(cond_expr));
		foreach_stmt->SetIterExpr(std::move(iter_expr));
		foreach_stmt->SetBodyStmt(std::move(body_stmt));
		return foreach_stmt;
	}

	UniqueWhileStmtPtr Sema::ActOnWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt)
	{
		UniqueWhileStmtPtr while_stmt = MakeUnique<WhileStmt>();
		while_stmt->SetCondExpr(std::move(cond_expr));
		while_stmt->SetBodyStmt(std::move(body_stmt));
		return while_stmt;
	}

	UniqueDoWhileStmtPtr Sema::ActOnDoWhileStmt(UniqueExprPtr&& cond_expr, UniqueStmtPtr&& body_stmt)
	{
		UniqueDoWhileStmtPtr do_while_stmt = MakeUnique<DoWhileStmt>();
		do_while_stmt->SetCondExpr(std::move(cond_expr));
		do_while_stmt->SetBodyStmt(std::move(body_stmt));
		return do_while_stmt;
	}

	UniqueCaseStmtPtr Sema::ActOnCaseStmt(SourceLocation const& loc, UniqueExprPtr&& case_expr)
	{
		if (ctx.case_callback_stack.empty()) diagnostics.Report(loc, case_stmt_outside_switch);

		UniqueCaseStmtPtr case_stmt = nullptr;
		if (!case_expr)
		{
			case_stmt = MakeUnique<CaseStmt>();
		}
		else
		{
			if (!case_expr->IsConstexpr()) diagnostics.Report(case_value_not_constexpr);
			case_stmt = MakeUnique<CaseStmt>(case_expr->EvaluateConstexpr());
		}
		ctx.case_callback_stack.back()(case_stmt.get());
		return case_stmt;
	}

	UniqueSwitchStmtPtr Sema::ActOnSwitchStmt(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueStmtPtr body_stmt, CaseStmtPtrList&& case_stmts)
	{
		bool default_found = false;
		std::unordered_map<int64, bool> case_value_found;
		for (CaseStmt* case_stmt : case_stmts)
		{
			if (case_stmt->IsDefault())
			{
				if (default_found) diagnostics.Report(loc, duplicate_default_case);
				else default_found = true;
			}
			else
			{
				int64 case_value = case_stmt->GetValue();
				if (case_value_found[case_value]) diagnostics.Report(loc, duplicate_case_value, case_value);
				else case_value_found[case_value] = true;
			}
		}

		UniqueSwitchStmtPtr switch_stmt = MakeUnique<SwitchStmt>();
		switch_stmt->SetCondExpr(std::move(cond_expr));
		switch_stmt->SetBodyStmt(std::move(body_stmt));

		return switch_stmt;
	}

	UniqueGotoStmtPtr Sema::ActOnGotoStmt(SourceLocation const& loc, std::string_view label_name)
	{
		ctx.gotos.push_back(std::string(label_name));
		return MakeUnique<GotoStmt>(label_name);
	}

	UniqueLabelStmtPtr Sema::ActOnLabelStmt(SourceLocation const& loc, std::string_view label_name)
	{
		std::string label(label_name);
		if (ctx.labels.contains(label)) diagnostics.Report(loc, redefinition_of_label, label_name);
		ctx.labels.insert(label);
		return MakeUnique<LabelStmt>(label_name);
	}

	UniqueUnaryExprPtr Sema::ActOnUnaryExpr(UnaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& operand)
	{
		switch (op)
		{
		case UnaryExprKind::PreIncrement:
		case UnaryExprKind::PreDecrement:
		case UnaryExprKind::PostIncrement:
		case UnaryExprKind::PostDecrement:
			if (IsBoolType(operand->GetType()))
			{
				diagnostics.Report(loc, bool_forbidden_in_increment);
			}
			break;
		case UnaryExprKind::Plus:
			break;
		case UnaryExprKind::Minus:
			break;
		case UnaryExprKind::BitNot:
			break;
		case UnaryExprKind::LogicalNot:
			if (!IsBoolType(operand->GetType()))
			{
				operand = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(operand));
			}
			break;
		default:
			break;
		}
		UniqueUnaryExprPtr unary_expr = MakeUnique<UnaryExpr>(op, loc);
		unary_expr->SetType(operand->GetType());
		unary_expr->SetOperand(std::move(operand));

		return unary_expr;
	}

	UniqueBinaryExprPtr Sema::ActOnBinaryExpr(BinaryExprKind op, SourceLocation const& loc, UniqueExprPtr&& lhs, UniqueExprPtr&& rhs)
	{
		QualType type{};
		QualType const& lhs_type = lhs->GetType();
		QualType const& rhs_type = rhs->GetType();
		switch (op)
		{
		case BinaryExprKind::Assign:
		{
			if (lhs->IsLValue())
			{
				if (lhs_type.IsConst()) diagnostics.Report(loc, invalid_assignment_to_const);
			}
			else diagnostics.Report(loc, invalid_assignment_to_rvalue);

			if (!lhs_type->IsAssignableFrom(rhs->GetType()))
			{
				diagnostics.Report(loc, incompatible_initializer);
			}
			else if (!lhs_type->IsSameAs(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, lhs_type, std::move(rhs));
			}
			type = lhs_type;
		}
		break;
		case BinaryExprKind::Add:
		case BinaryExprKind::Subtract:
		case BinaryExprKind::Multiply:
		case BinaryExprKind::Divide:
		{
			if (lhs_type->IsOneOf(TypeKind::Void, TypeKind::Array, TypeKind::Function) ||
				rhs_type->IsOneOf(TypeKind::Void, TypeKind::Array, TypeKind::Function))
			{
				diagnostics.Report(loc, invalid_operands);
				return nullptr;
			}

			TypeKind lhs_type_kind = lhs_type->GetKind();
			TypeKind rhs_type_kind = rhs_type->GetKind();
			if (lhs_type_kind == rhs_type_kind)
			{
				type = *lhs_type;
			}
			else if (lhs_type_kind > rhs_type_kind)
			{
				type = *lhs_type;
				rhs = ActOnImplicitCastExpr(loc, type, std::move(rhs));
			}
			else
			{
				type = *rhs_type;
				lhs = ActOnImplicitCastExpr(loc, type, std::move(lhs));
			}
		}
		break;
		case BinaryExprKind::Modulo:
		{
			if (!IsIntegralType(lhs_type) || !IsIntegralType(rhs_type))
			{
				diagnostics.Report(loc, modulo_operands_not_integral);
			}
			if (!IsIntegerType(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!IsIntegerType(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(rhs));
			}
			type = builtin_types::Int;
		}
		break;
		case BinaryExprKind::ShiftLeft:
		case BinaryExprKind::ShiftRight:
		{
			if (!IsIntegralType(lhs_type) || !IsIntegralType(rhs_type))
			{
				diagnostics.Report(loc, shift_operands_not_integral);
			}
			if (!IsIntegerType(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!IsIntegerType(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(rhs));
			}
			type = builtin_types::Int;
		}
		break;
		case BinaryExprKind::BitAnd:
		case BinaryExprKind::BitOr:
		case BinaryExprKind::BitXor:
		{
			if (!IsIntegralType(lhs_type) || !IsIntegralType(rhs_type))
			{
				diagnostics.Report(loc, bitwise_operands_not_integral);
			}
			if (!IsIntegerType(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!IsIntegerType(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(rhs));
			}
			type = builtin_types::Int;
		}
		break;
		case BinaryExprKind::LogicalAnd:
		case BinaryExprKind::LogicalOr:
		{
			if (!IsBoolType(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(lhs));
			}
			if (!IsBoolType(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(rhs));
			}
			type = builtin_types::Bool;
		}
		break;
		case BinaryExprKind::Equal:
		case BinaryExprKind::NotEqual:
		case BinaryExprKind::Less:
		case BinaryExprKind::Greater:
		case BinaryExprKind::LessEqual:
		case BinaryExprKind::GreaterEqual:
		{
			if (lhs_type->IsOneOf(TypeKind::Void, TypeKind::Array, TypeKind::Function) ||
				rhs_type->IsOneOf(TypeKind::Void, TypeKind::Array, TypeKind::Function))
			{
				diagnostics.Report(loc, invalid_operands);
				return nullptr;
			}

			TypeKind lhs_type_kind = lhs_type->GetKind();
			TypeKind rhs_type_kind = rhs_type->GetKind();
			if (lhs_type_kind > rhs_type_kind)
			{
				type = *lhs_type;
				rhs = ActOnImplicitCastExpr(loc, type, std::move(rhs));
			}
			else if (lhs_type_kind < rhs_type_kind)
			{
				type = *rhs_type;
				lhs = ActOnImplicitCastExpr(loc, type, std::move(lhs));
			}

			type = builtin_types::Bool;
		}
		break;
		case BinaryExprKind::Comma:
		{
			type = rhs_type;
		}
		break;
		case BinaryExprKind::Invalid:
		default:
			WAVE_ASSERT(false);
		}

		UniqueBinaryExprPtr binary_expr = MakeUnique<BinaryExpr>(op, loc);
		binary_expr->SetType(type);
		binary_expr->SetLHS(std::move(lhs));
		binary_expr->SetRHS(std::move(rhs));
		return binary_expr;
	}

	UniqueTernaryExprPtr Sema::ActOnTernaryExpr(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueExprPtr&& true_expr, UniqueExprPtr&& false_expr)
	{
		QualType const& true_type = true_expr->GetType();
		QualType const& false_type = false_expr->GetType();

		if (!builtin_types::Bool.IsAssignableFrom(cond_expr->GetType()))
		{
			diagnostics.Report(loc, used_nonboolean_type);
		}
		else if(!cond_expr->GetType()->IsSameAs(builtin_types::Bool))
		{
			cond_expr = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(cond_expr));
		}

		QualType expr_type{};
		if (true_type->IsSameAs(false_type)) expr_type = true_type;
		else diagnostics.Report(loc, ternary_expr_types_incompatible);

		UniqueTernaryExprPtr ternary_expr = MakeUnique<TernaryExpr>(loc);
		ternary_expr->SetType(expr_type);
		ternary_expr->SetCondExpr(std::move(cond_expr));
		ternary_expr->SetTrueExpr(std::move(true_expr));
		ternary_expr->SetFalseExpr(std::move(false_expr));
		return ternary_expr;
	}

	UniqueFunctionCallExprPtr Sema::ActOnFunctionCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args)
	{
		if (func_expr->GetExprKind() != ExprKind::DeclRef)
		{
			diagnostics.Report(loc, invalid_function_call);
			return nullptr;
		}

		DeclRefExpr const* decl_ref = ast_cast<DeclRefExpr>(func_expr.get());
		Decl const* decl = decl_ref->GetDecl();
		if (decl->GetDeclKind() != DeclKind::Function && decl->GetDeclKind() != DeclKind::MemberFunction)
		{
			diagnostics.Report(loc, invalid_function_call);
			return nullptr;
		}

		QualType const& func_expr_type = decl->GetType();
		WAVE_ASSERT(IsFunctionType(func_expr_type));
		FunctionType const& func_type = type_cast<FunctionType>(func_expr_type);
		std::span<FunctionParameter const> func_params = func_type.GetParameters();
		if (args.size() != func_params.size())
		{
			if (args.size() > func_params.size()) diagnostics.Report(loc, too_many_args_to_function_call);
			else diagnostics.Report(loc, too_few_args_to_function_call);
			return nullptr;
		}

		for (uint64 i = 0; i < func_params.size(); ++i)
		{
			UniqueExprPtr& arg = args[i];
			FunctionParameter const& func_param = func_params[i];
			
			if (!func_param.type->IsAssignableFrom(arg->GetType()))
			{
				diagnostics.Report(loc, incompatible_function_argument);
				return nullptr;
			}
			else if (!func_param.type->IsSameAs(arg->GetType()))
			{
				arg = ActOnImplicitCastExpr(loc, func_param.type, std::move(arg));
			}
		}

		std::string_view func_name = decl->GetName();
		UniqueFunctionCallExprPtr func_call_expr = MakeUnique<FunctionCallExpr>(loc, func_name);
		func_call_expr->SetType(func_type.GetReturnType());
		func_call_expr->SetArgs(std::move(args));
		return func_call_expr;
	}

	UniqueConstantIntPtr Sema::ActOnConstantInt(int64 value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantInt>(value, loc);
	}

	UniqueConstantIntPtr Sema::ActOnLengthOperator(QualType const& type, SourceLocation const& loc)
	{
		if (!IsArrayType(type))
		{
			diagnostics.Report(loc, length_operand_not_array);
			return nullptr;
		}
		ArrayType const& array_type = type_cast<ArrayType>(type);
		if (array_type.GetArraySize() == 0)
		{
			diagnostics.Report(loc, length_operand_incomplete_array);
			return nullptr;
		}
		return ActOnConstantInt(array_type.GetArraySize(), loc);
	}

	UniqueConstantCharPtr Sema::ActOnConstantChar(std::string_view str, SourceLocation const& loc)
	{
		if (str.size() != 1)
		{
			diagnostics.Report(loc, invalid_char_literal);
			return nullptr;
		}
		return MakeUnique<ConstantChar>(str[0], loc);
	}

	UniqueConstantStringPtr Sema::ActOnConstantString(std::string_view str, SourceLocation const& loc)
	{
		return MakeUnique<ConstantString>(str, loc);
	}

	UniqueConstantBoolPtr Sema::ActOnConstantBool(bool value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantBool>(value, loc);
	}

	UniqueConstantFloatPtr Sema::ActOnConstantFloat(double value, SourceLocation const& loc)
	{
		return MakeUnique<ConstantFloat>(value, loc);
	}

	UniqueIdentifierExprPtr Sema::ActOnIdentifier(std::string_view name, SourceLocation const& loc)
	{
		if (Decl* decl = ctx.decl_sym_table.LookUp(name))
		{
			UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(decl, loc);
			return decl_ref;
		}
		else if (Expr const* current_class_expr = ctx.current_class_expr)
		{
			QualType const& class_expr_type = current_class_expr->GetType();
			ClassType const* class_type = dynamic_type_cast<ClassType>(class_expr_type);
			if (!class_type)
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}
			ClassDecl const* class_decl = class_type->GetClassDecl();
			if (Decl* class_member_decl = class_decl->FindDecl(name))
			{
				UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(class_member_decl, loc);
				return decl_ref;
			}
			else
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}
		}
		else
		{
			diagnostics.Report(loc, undeclared_identifier, name);
			return nullptr;
		}
	}

	UniqueInitializerListExprPtr Sema::ActOnInitializerListExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtrList&& expr_list)
	{
		if(type.IsNull() && expr_list.empty())
		{
			diagnostics.Report(loc, invalid_init_list_expression);
			return nullptr;
		}

		QualType expr_type{};
		if (!type.IsNull())
		{
			WAVE_ASSERT(type->Is(TypeKind::Array));
			ArrayType const& array_type = type_cast<ArrayType>(type);
			WAVE_ASSERT(array_type.GetArraySize() > 0);
			if (array_type.GetArraySize() < expr_list.size())
			{
				diagnostics.Report(loc, array_size_not_positive);
				return nullptr;
			}
			QualType const& base_type = array_type.GetBaseType();
			expr_type = base_type;
		}
		else
		{
			expr_type = expr_list.front()->GetType();
			QualType base_type(expr_type);
			ArrayType arr_type(base_type, expr_list.size());
			const_cast<QualType&>(type).SetType(arr_type);
		}

		for (auto const& expr : expr_list)
		{
			if (!expr->GetType()->IsSameAs(expr_type))
			{
				diagnostics.Report(loc, init_list_element_expressions_type_mismatch);
				return nullptr;
			}
		}

		UniqueInitializerListExprPtr init_list_expr = MakeUnique<InitializerListExpr>(loc);
		init_list_expr->SetType(type);
		init_list_expr->SetInitList(std::move(expr_list));
		return init_list_expr;
	}

	UniqueArrayAccessExprPtr Sema::ActOnArrayAccessExpr(SourceLocation const& loc, UniqueExprPtr&& array_expr, UniqueExprPtr&& index_expr)
	{
		if (!IsArrayType(array_expr->GetType()))
		{
			diagnostics.Report(loc, subscripted_value_not_array);
			return nullptr;
		}
		if (!IsIntegerType(index_expr->GetType()))
		{
			diagnostics.Report(loc, array_subscript_not_integer);
			return nullptr;
		}

		ArrayType const& array_type = type_cast<ArrayType>(array_expr->GetType());
		if (index_expr->IsConstexpr())
		{
			int64 bracket_value = index_expr->EvaluateConstexpr();
			if (array_type.GetArraySize() > 0 && (bracket_value < 0 || bracket_value >= array_type.GetArraySize()))
			{
				diagnostics.Report(loc, array_index_outside_of_bounds, bracket_value);
				return nullptr;
			}
		}

		UniqueArrayAccessExprPtr array_access_expr = MakeUnique<ArrayAccessExpr>(loc);
		array_access_expr->SetArrayExpr(std::move(array_expr));
		array_access_expr->SetIndexExpr(std::move(index_expr));
		array_access_expr->SetType(array_type.GetBaseType());
		return array_access_expr;
	}

	UniqueMemberExprPtr Sema::ActOnMemberExpr(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueExprPtr&& member_expr)
	{
		if (!IsClassType(class_expr->GetType()))
		{
			diagnostics.Report(loc, subscripted_value_not_array);
			return nullptr;
		}

		ClassType const& class_type = type_cast<ClassType>(class_expr->GetType());
		ClassDecl const* class_decl = class_type.GetClassDecl();
		QualType const& member_type = member_expr->GetType();

		UniqueMemberExprPtr array_access_expr = MakeUnique<MemberExpr>(loc);
		array_access_expr->SetClassExpr(std::move(class_expr));
		array_access_expr->SetType(member_type);
		return array_access_expr;
	}

	UniqueImplicitCastExprPtr Sema::ActOnImplicitCastExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtr&& expr)
	{
		QualType const& cast_type = type;
		QualType const& operand_type = expr->GetType();

		if (IsArrayType(cast_type) || IsArrayType(operand_type)) diagnostics.Report(loc, invalid_cast);
		if (IsVoidType(cast_type)) diagnostics.Report(loc, invalid_cast);
		if (!cast_type->IsAssignableFrom(operand_type)) diagnostics.Report(loc, invalid_cast);

		UniqueImplicitCastExprPtr cast_expr = MakeUnique<ImplicitCastExpr>(loc, type);
		cast_expr->SetOperand(std::move(expr));
		return cast_expr;
	}

	template<typename Decl> requires std::is_base_of_v<VariableDecl, Decl>
	UniquePtr<Decl> Sema::ActOnVariableDeclCommon(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		bool const has_init = (init_expr != nullptr);
		bool const has_type_specifier = !type.IsNull();
		bool const init_expr_is_decl_ref = has_init && init_expr->GetExprKind() == ExprKind::DeclRef;

		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}

		if (has_init && has_type_specifier)
		{
			if (!type->IsAssignableFrom(init_expr->GetType()))
			{
				diagnostics.Report(loc, incompatible_initializer);
			}
			else if (!type->IsSameAs(init_expr->GetType()))
			{
				init_expr = ActOnImplicitCastExpr(loc, type, std::move(init_expr));
			}
		}
		else if (!has_init && !has_type_specifier)
		{
			diagnostics.Report(loc, missing_type_specifier_or_init_expr);
		}

		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		if (has_type_specifier && type->Is(TypeKind::Void))
		{
			diagnostics.Report(loc, void_invalid_context);
		}

		UniquePtr<Decl> var_decl = MakeUnique<Decl>(name, loc);
		var_decl->SetGlobal(ctx.decl_sym_table.IsGlobal());
		var_decl->SetVisibility(visibility);
		WAVE_ASSERT(var_decl->IsGlobal() || !var_decl->IsExtern());

		if (var_decl->IsGlobal() && init_expr && !init_expr->IsConstexpr())
		{
			diagnostics.Report(loc, global_variable_initializer_not_constexpr, name);
		}
		var_decl->SetInitExpr(std::move(init_expr));

		bool is_array = (has_type_specifier && IsArrayType(type)) || (has_init && IsArrayType(var_decl->GetInitExpr()->GetType()));
		if (is_array)
		{
			ArrayType const& init_expr_type = type_cast<ArrayType>(var_decl->GetInitExpr()->GetType());
			QualType base_type{};
			if (has_type_specifier)
			{
				ArrayType const& decl_type = type_cast<ArrayType>(type);
				if (!decl_type.GetBaseType().IsConst() && init_expr_type.GetBaseType().IsConst())
				{
					diagnostics.Report(loc, assigning_const_array_to_non_const_array, name);
				}
				base_type = decl_type.GetBaseType();
			}
			else
			{
				base_type = init_expr_type.GetBaseType();
			}
			if (type.IsConst()) base_type.AddConst();
			uint64 array_size = init_expr_is_decl_ref ? 0 : init_expr_type.GetArraySize();
			QualType var_type(ArrayType(base_type, array_size));
			var_decl->SetType(var_type);
		}
		else if ((has_init && !has_type_specifier))
		{
			QualType var_type(var_decl->GetInitExpr()->GetType());
			if (type.IsConst()) var_type.AddConst();
			var_decl->SetType(var_type);
		}
		else
		{
			var_decl->SetType(type);
		}

		ctx.decl_sym_table.Insert(var_decl.get());
		return var_decl;
	}

}

