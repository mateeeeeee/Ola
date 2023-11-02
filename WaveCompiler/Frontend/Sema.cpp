#include "Sema.h"
#include "Diagnostics.h"
#include "Type.h"

namespace wave
{
	Sema::Sema(Diagnostics& diagnostics) : diagnostics(diagnostics) {}
	Sema::~Sema() = default;

	UniqueVariableDeclPtr Sema::ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type, 
												  UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		bool const has_init = (init_expr != nullptr);
		bool const has_type_specifier = type.HasRawType();

		if (!name.empty() && ctx.decl_sym_table.LookUpCurrentScope(name))
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
		else if(!has_init && !has_type_specifier)
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

		std::unique_ptr<VariableDecl> var_decl = MakeUnique<VariableDecl>(name, loc);
		var_decl->SetGlobal(ctx.decl_sym_table.IsGlobal());
		var_decl->SetVisibility(visibility);
		WAVE_ASSERT(var_decl->IsGlobal() || !var_decl->IsExtern());

		if (var_decl->IsGlobal() && init_expr && !init_expr->IsConstexpr())
		{
			diagnostics.Report(loc, global_variable_initializer_not_constexpr, name);
		}
		var_decl->SetInitExpr(std::move(init_expr));

		if ((has_init && !has_type_specifier) || type->Is(TypeKind::Array))
		{
			QualifiedType var_type(var_decl->GetInitExpr()->GetType());
			if (type.IsConst()) var_type.AddConst();
			var_decl->SetType(var_type);
		}
		else
		{
			var_decl->SetType(type);
		}

		if(!name.empty()) ctx.decl_sym_table.Insert(var_decl.get());
		return var_decl;
	}

	UniqueVariableDeclPtr Sema::ActOnFunctionParamDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type)
	{
		if (!name.empty() && ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}
		if (!type.HasRawType())
		{
			diagnostics.Report(loc, missing_type_specifier);
		}
		if (type->Is(TypeKind::Void))
		{
			diagnostics.Report(loc, void_invalid_context);
		}

		std::unique_ptr<VariableDecl> param_decl = MakeUnique<VariableDecl>(name, loc);
		param_decl->SetGlobal(false);
		param_decl->SetVisibility(DeclVisibility::None);
		param_decl->SetType(type);
		if (!name.empty()) ctx.decl_sym_table.Insert(param_decl.get());
		return param_decl;

	}

	UniqueFunctionDeclPtr Sema::ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualifiedType const& type,
												  UniqueVariableDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt, DeclVisibility visibility)
	{
		bool is_extern = body_stmt == nullptr;
		if (!is_extern && ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
		}

		if (name == "main")
		{
			FunctionType const* func_type = dynamic_type_cast<FunctionType>(type);
			WAVE_ASSERT(func_type);
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
		}

		bool result = ctx.decl_sym_table.Insert(function_decl.get());
		WAVE_ASSERT(result);
		return function_decl;
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
		QualifiedType const& return_type = func_type.GetReturnType();

		Expr const* ret_expr = expr_stmt->GetExpr();
		SourceLocation loc = ret_expr ? ret_expr->GetLocation() : SourceLocation{};

		QualifiedType const& ret_expr_type = ret_expr ? ret_expr->GetType() : builtin_types::Void;
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
		QualifiedType arr_type = array_identifier->GetType();
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

		QualifiedType var_type = var_decl->GetType();
		if (var_type.HasRawType())
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
			UniqueStmtPtrList _stmts = std::move(compound_stmt->TakeStmts());
			_stmts.insert(std::begin(_stmts), std::move(array_access_stmt));
			body_stmt = ActOnCompoundStmt(std::move(_stmts));
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
		QualifiedType type{};
		QualifiedType const& lhs_type = lhs->GetType();
		QualifiedType const& rhs_type = rhs->GetType();
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
		case BinaryExprKind::Modulo:
		{
			type = lhs_type;
		}
		break;
		case BinaryExprKind::ShiftLeft:
		case BinaryExprKind::ShiftRight:
		{
			type = lhs_type;
		}
		break;
		case BinaryExprKind::BitAnd:
		case BinaryExprKind::BitOr:
		case BinaryExprKind::BitXor:
		{
			type = lhs_type;
		}
		break;
		case BinaryExprKind::LogicalAnd:
		case BinaryExprKind::LogicalOr:
		{
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
		QualifiedType const& true_type = true_expr->GetType();
		QualifiedType const& false_type = false_expr->GetType();

		if (!builtin_types::Bool.IsAssignableFrom(cond_expr->GetType()))
		{
			diagnostics.Report(loc, used_nonboolean_type);
		}
		else if(!cond_expr->GetType()->IsSameAs(builtin_types::Bool))
		{
			cond_expr = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(cond_expr));
		}

		QualifiedType expr_type{};
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
		if (decl->GetDeclKind() != DeclKind::Function)
		{
			diagnostics.Report(loc, invalid_function_call);
			return nullptr;
		}

		QualifiedType const& func_expr_type = decl->GetType();
		WAVE_ASSERT(IsFunctionType(func_expr_type));
		FunctionType const& func_type = type_cast<FunctionType>(func_expr_type);

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

	UniqueConstantIntPtr Sema::ActOnLengthOperator(QualifiedType const& type, SourceLocation const& loc)
	{
		if (!IsArrayType(type))
		{
			diagnostics.Report(loc, length_operand_not_array);
			return nullptr;
		}
		ArrayType const& array_type = type_cast<ArrayType>(type);
		return ActOnConstantInt(array_type.GetArraySize(), loc);
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
		else
		{
			diagnostics.Report(loc, undeclared_identifier, name);
			return nullptr;
		}
	}

	UniqueInitializerListExprPtr Sema::ActOnInitializerListExpr(SourceLocation const& loc, QualifiedType const& type, UniqueExprPtrList&& expr_list)
	{
		if(!type.HasRawType() && expr_list.empty())
		{
			diagnostics.Report(loc, invalid_init_list_expression);
			return nullptr;
		}

		QualifiedType expr_type{};
		if (type.HasRawType())
		{
			WAVE_ASSERT(type->Is(TypeKind::Array));
			ArrayType const& array_type = type_cast<ArrayType>(type);
			WAVE_ASSERT(array_type.GetArraySize() > 0);
			if (array_type.GetArraySize() < expr_list.size())
			{
				diagnostics.Report(loc, array_size_not_positive);
				return nullptr;
			}
			QualifiedType const& base_type = array_type.GetBaseType();
			expr_type = base_type;
		}
		else
		{
			expr_type = expr_list.front()->GetType();
			QualifiedType base_type(expr_type);
			ArrayType arr_type(base_type, expr_list.size());
			const_cast<QualifiedType&>(type).SetRawType(arr_type);
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
			if (bracket_value < 0 || bracket_value > array_type.GetArraySize())
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

	UniqueImplicitCastExprPtr Sema::ActOnImplicitCastExpr(SourceLocation const& loc, QualifiedType const& type, UniqueExprPtr&& expr)
	{
		QualifiedType const& cast_type = type;
		QualifiedType const& operand_type = expr->GetType();

		if (IsArrayType(cast_type) || IsArrayType(operand_type)) diagnostics.Report(loc, invalid_cast);
		if (IsVoidType(cast_type)) diagnostics.Report(loc, invalid_cast);
		if (!cast_type->IsAssignableFrom(operand_type)) diagnostics.Report(loc, invalid_cast);

		UniqueImplicitCastExprPtr cast_expr = MakeUnique<ImplicitCastExpr>(loc, type);
		cast_expr->SetOperand(std::move(expr));
		return cast_expr;
	}
}

