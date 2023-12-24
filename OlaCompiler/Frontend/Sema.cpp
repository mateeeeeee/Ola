#include "Sema.h"
#include "Diagnostics.h"
#include "AST/Type.h"

namespace ola
{
	Sema::Sema(Diagnostics& diagnostics) : diagnostics(diagnostics) {}
	Sema::~Sema() = default;

	UniqueVarDeclPtr Sema::ActOnVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
		UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		return ActOnVariableDeclCommon<VarDecl>(name, loc, type, std::move(init_expr), visibility);
	}

	UniqueParamVarDeclPtr Sema::ActOnParamVariableDecl(std::string_view name, SourceLocation const& loc, QualType const& type)
	{
		if (!name.empty() && ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
		}
		if (type.IsNull())
		{
			diagnostics.Report(loc, missing_type_specifier);
			return nullptr;
		}
		if (isa<VoidType>(type))
		{
			diagnostics.Report(loc, void_invalid_context);
			return nullptr;
		}

		if (isa<RefType>(type))
		{
			RefType const& ref_type = type_cast<RefType>(type);
			if (ref_type.GetReferredType().IsNull())
			{
				diagnostics.Report(loc, missing_type_specifier);
				return nullptr;
			}
			if (isa<ArrayType>(ref_type.GetReferredType()))
			{
				diagnostics.Report(loc, arrays_cannot_be_refs);
				return nullptr;
			}
		}
		if (isa<ClassType>(type))
		{
			ClassDecl const* class_decl = type_cast<ClassType>(type).GetClassDecl();
			if (class_decl->IsAbstract())
			{
				diagnostics.Report(loc, variable_type_abstract, class_decl->GetName());
				return nullptr;
			}
		}

		UniqueParamVarDeclPtr param_decl = MakeUnique<ParamVarDecl>(name, loc);
		param_decl->SetGlobal(false);
		param_decl->SetVisibility(DeclVisibility::None);
		param_decl->SetType(type);
		if (!name.empty()) ctx.decl_sym_table.Insert(param_decl.get());
		return param_decl;
	}

	UniqueFieldDeclPtr Sema::ActOnFieldDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		return ActOnVariableDeclCommon<FieldDecl>(name, loc, type, std::move(init_expr), visibility);
	}

	UniqueFunctionDeclPtr Sema::ActOnFunctionDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
		UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt,
		DeclVisibility visibility, FuncAttributes attributes)
	{
		FuncType const* func_type = dyn_type_cast<FuncType>(type);
		OLA_ASSERT(func_type);
		if (name == "main")
		{
			if (!isa<IntType>(func_type->GetReturnType()) || !func_type->GetParams().empty())
			{
				diagnostics.Report(loc, invalid_main_function_declaration);
				return nullptr;
			}
		}
		if (HasAttribute(attributes, FuncAttribute_Inline) && HasAttribute(attributes, FuncAttribute_NoInline))
		{
			diagnostics.Report(loc, incompatible_function_attributes);
			return nullptr;
		}

		UniqueFunctionDeclPtr function_decl = MakeUnique<FunctionDecl>(name, loc);
		function_decl->SetFuncAttributes(attributes);
		function_decl->SetType(type);
		function_decl->SetVisibility(visibility);
		function_decl->SetParamDecls(std::move(param_decls));
		if (body_stmt)
		{
			function_decl->SetBodyStmt(std::move(body_stmt));
			for (std::string const& goto_label : ctx.gotos)
			{
				if (!ctx.labels.contains(goto_label))
				{
					diagnostics.Report(loc, undeclared_label, goto_label);
					return nullptr;
				}
			}
			ctx.gotos.clear();
			ctx.labels.clear();

			if (!ctx.return_stmt_encountered && !isa<VoidType>(func_type->GetReturnType()))
			{
				diagnostics.Report(loc, no_return_statement_found_in_non_void_function);
			}
			ctx.return_stmt_encountered = false;
		}

		bool result = ctx.decl_sym_table.Insert_Overload(function_decl.get());
		OLA_ASSERT(result);
		return function_decl;
	}

	UniqueMethodDeclPtr Sema::ActOnMethodDecl(std::string_view name, SourceLocation const& loc, QualType const& type,
		UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt,
		DeclVisibility visibility, FuncAttributes func_attrs, MethodAttributes method_attrs)
	{
		if (name == ctx.current_class_name)
		{
			diagnostics.Report(loc, constructor_return_type_error);
			return nullptr;
		}

		bool is_const = HasAttribute(method_attrs, MethodAttribute_Const);
		FuncType const* func_type = dyn_type_cast<FuncType>(type);
		OLA_ASSERT(func_type);

		if (isa<RefType>(func_type->GetReturnType()) && !func_type->GetReturnType().IsConst() && is_const)
		{
			diagnostics.Report(loc, const_methods_cannot_return_nonconst_refs);
			return nullptr;
		}
		if (HasAttribute(func_attrs, FuncAttribute_Inline) && HasAttribute(func_attrs, FuncAttribute_NoInline))
		{
			diagnostics.Report(loc, incompatible_function_attributes);
			return nullptr;
		}
		if (HasAttribute(func_attrs, FuncAttribute_NoMangling))
		{
			diagnostics.Report(loc, method_cannot_be_nomangling);
			return nullptr;
		}
		if (HasAttribute(method_attrs, MethodAttribute_Final))
		{
			if (!HasAttribute(method_attrs, MethodAttribute_Virtual))
			{
				diagnostics.Report(loc, final_must_be_virtual);
				return nullptr;
			}
		}
		if (HasAttribute(method_attrs, MethodAttribute_Pure))
		{
			if (!HasAttribute(method_attrs, MethodAttribute_Virtual))
			{
				diagnostics.Report(loc, pure_must_be_virtual);
				return nullptr;
			}
			if (HasAttribute(method_attrs, MethodAttribute_Final))
			{
				diagnostics.Report(loc, pure_cannot_be_final);
				return nullptr;
			}
			if (body_stmt != nullptr)
			{
				diagnostics.Report(loc, pure_method_cannot_have_body);
				return nullptr;
			}
		}

		UniqueMethodDeclPtr member_function_decl = MakeUnique<MethodDecl>(name, loc);
		member_function_decl->SetType(type);
		member_function_decl->SetVisibility(visibility);
		member_function_decl->SetFuncAttributes(func_attrs);
		member_function_decl->SetMethodAttributes(method_attrs);
		member_function_decl->SetParamDecls(std::move(param_decls));
		if (body_stmt)
		{
			member_function_decl->SetBodyStmt(std::move(body_stmt));
			for (std::string const& goto_label : ctx.gotos)
			{
				if (!ctx.labels.contains(goto_label))
				{
					diagnostics.Report(loc, undeclared_label, goto_label);
					return nullptr;
				}
			}
			ctx.gotos.clear();
			ctx.labels.clear();

			if (!ctx.return_stmt_encountered && !isa<VoidType>(func_type->GetReturnType()))
			{
				diagnostics.Report(loc, no_return_statement_found_in_non_void_function);
				return nullptr;
			}
			ctx.return_stmt_encountered = false;
		}

		bool result = ctx.decl_sym_table.Insert_Overload(member_function_decl.get());
		return member_function_decl;
	}

	UniqueConstructorDeclPtr Sema::ActOnConstructorDecl(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueParamVarDeclPtrList&& param_decls, UniqueCompoundStmtPtr&& body_stmt)
	{
		if (name != ctx.current_class_name)
		{
			diagnostics.Report(loc, missing_method_return_type_error);
			return nullptr;
		}

		FuncType const* func_type = dyn_type_cast<FuncType>(type);
		OLA_ASSERT(func_type);

		UniqueConstructorDeclPtr constructor_decl = MakeUnique<ConstructorDecl>(name, loc);
		constructor_decl->SetType(type);
		constructor_decl->SetVisibility(DeclVisibility::Public);
		constructor_decl->SetParamDecls(std::move(param_decls));
		if (body_stmt)
		{
			constructor_decl->SetBodyStmt(std::move(body_stmt));
			for (std::string const& goto_label : ctx.gotos)
			{
				if (!ctx.labels.contains(goto_label))
				{
					diagnostics.Report(loc, undeclared_label, goto_label);
					return nullptr;
				}
			}
			ctx.gotos.clear();
			ctx.labels.clear();
		}

		bool result = ctx.decl_sym_table.Insert_Overload(constructor_decl.get());
		return constructor_decl;
	}

	UniqueEnumDeclPtr Sema::ActOnEnumDecl(std::string_view name, SourceLocation const& loc, UniqueEnumMemberDeclPtrList&& enum_members)
	{
		if (!name.empty() && ctx.tag_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
		}
		UniqueEnumDeclPtr enum_decl = MakeUnique<EnumDecl>(name, loc);
		enum_decl->SetEnumMembers(std::move(enum_members));
		if (!name.empty()) ctx.tag_sym_table.Insert(enum_decl.get());
		return enum_decl;
	}

	UniqueEnumMemberDeclPtr Sema::ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, UniqueExprPtr&& enum_value_expr)
	{
		if (!enum_value_expr->IsConstexpr())
		{
			diagnostics.Report(loc, enumerator_value_not_constexpr, name);
			return nullptr;
		}
		return ActOnEnumMemberDecl(name, loc, enum_value_expr->EvaluateConstexpr());
	}

	UniqueEnumMemberDeclPtr Sema::ActOnEnumMemberDecl(std::string_view name, SourceLocation const& loc, int64 enum_value)
	{
		if (name.empty())
		{
			diagnostics.Report(loc, expected_identifier);
			return nullptr;
		}
		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
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
			return nullptr;
		}
		if (type.IsNull())
		{
			diagnostics.Report(loc, aliasing_var_forbidden);
			return nullptr;
		}
		UniqueAliasDeclPtr alias_decl = MakeUnique<AliasDecl>(name, loc, type);

		ctx.tag_sym_table.Insert(alias_decl.get());
		return alias_decl;
	}

	ClassDecl const* Sema::ActOnBaseClassSpecifier(std::string_view base_name, SourceLocation const& loc)
	{
		if (!base_name.empty())
		{
			if (TagDecl* base_tag_decl = ctx.tag_sym_table.LookUpCurrentScope(base_name))
			{
				if (ClassDecl* base_class_decl = dyn_cast<ClassDecl>(base_tag_decl))
				{
					if (base_class_decl->IsFinal())
					{
						diagnostics.Report(loc, base_final_error, base_class_decl->GetName());
						return nullptr;
					}
					return base_class_decl;
				}
				else
				{
					diagnostics.Report(loc, base_specifier_not_class);
					return nullptr;
				}
			}
			else
			{
				diagnostics.Report(loc, undeclared_identifier, base_name);
				return nullptr;
			}
		}
		return nullptr;
	}

	UniqueClassDeclPtr Sema::ActOnClassDecl(std::string_view name, ClassDecl const* base_class, SourceLocation const& loc, UniqueFieldDeclPtrList&& member_variables, UniqueMethodDeclPtrList&& member_functions, bool final)
	{
		if (ctx.tag_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
		}

		UniqueClassDeclPtr class_decl = MakeUnique<ClassDecl>(name, loc);
		class_decl->SetBaseClass(base_class);
		class_decl->SetFields(std::move(member_variables));
		class_decl->SetMethods(std::move(member_functions));
		class_decl->SetFinal(final);

		MethodDecl const* error_decl = nullptr;
		BuildVTableResult build_result = class_decl->BuildVTable(error_decl);
		if (build_result == BuildVTableResult::Error_OverrideFinal)
		{
			diagnostics.Report(error_decl->GetLocation(), cannot_override_final_function, error_decl->GetName());
			return nullptr;
		}
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
		OLA_ASSERT(ctx.current_func);
		ctx.return_stmt_encountered = true;
		FuncType const& func_type = type_cast<FuncType>(*ctx.current_func);
		QualType const& return_type = func_type.GetReturnType();

		Expr const* ret_expr = expr_stmt->GetExpr();
		SourceLocation loc = ret_expr ? ret_expr->GetLocation() : SourceLocation{};

		QualType const& ret_expr_type = ret_expr ? ret_expr->GetType() : builtin_types::Void;
		if (!return_type->IsAssignableFrom(ret_expr_type))
		{
			diagnostics.Report(loc, incompatible_return_stmt_type);
			return nullptr;
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
		if (ctx.stmts_using_break_count == 0)
		{
			diagnostics.Report(loc, stray_break);
			return nullptr;
		}

		UniqueBreakStmtPtr break_stmt = MakeUnique<BreakStmt>();
		return break_stmt;
	}

	UniqueContinueStmtPtr Sema::ActOnContinueStmt(SourceLocation const& loc)
	{
		if (ctx.stmts_using_continue_count == 0)
		{
			diagnostics.Report(loc, stray_continue);
			return nullptr;
		}

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

	UniqueForStmtPtr Sema::ActOnForeachStmt(SourceLocation const& loc, UniqueVarDeclPtr&& var_decl, UniqueExprPtr&& array_identifier, UniqueStmtPtr&& body_stmt)
	{
		QualType arr_type = array_identifier->GetType();
		ArrayType const* array_type = dyn_type_cast<ArrayType>(arr_type);
		if (!array_type)
		{
			diagnostics.Report(loc, non_array_expr_in_foreach);
			return nullptr;
		}

		static uint64 foreach_id = 0;
		std::string foreach_index_name = "__foreach_index" + std::to_string(foreach_id++);
		UniqueVarDeclPtr foreach_index_decl = ActOnVariableDecl(foreach_index_name, loc, builtin_types::Int, ActOnConstantInt(0, loc), DeclVisibility::None);

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
				return nullptr;
			}
		}
		else var_decl->SetType(array_type->GetBaseType());
		var_decl->SetInitExpr(ActOnArrayAccessExpr(loc, std::move(array_identifier), MakeUnique<DeclRefExpr>(foreach_index_decl.get(), loc)));

		UniqueStmtPtr init_stmt = MakeUnique<DeclStmt>(std::move(foreach_index_decl));
		UniqueStmtPtr array_access_stmt = MakeUnique<DeclStmt>(std::move(var_decl));
		if (CompoundStmt* compound_stmt = dyn_cast<CompoundStmt>(body_stmt.get()))
		{
			compound_stmt->AddBeginStmt(std::move(array_access_stmt));
		}
		else
		{
			UniqueStmtPtrList stmts{};
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

	UniqueSwitchStmtPtr Sema::ActOnSwitchStmt(SourceLocation const& loc, UniqueExprPtr&& cond_expr, UniqueStmtPtr body_stmt, std::vector<CaseStmt*>&& case_stmts)
	{
		bool default_found = false;
		std::unordered_map<int64, bool> case_value_found;
		for (CaseStmt* case_stmt : case_stmts)
		{
			if (case_stmt->IsDefault())
			{
				if (default_found)
				{
					diagnostics.Report(loc, duplicate_default_case);
					return nullptr;
				}
				else default_found = true;
			}
			else
			{
				int64 case_value = case_stmt->GetValue();
				if (case_value_found[case_value])
				{
					diagnostics.Report(loc, duplicate_case_value, case_value);
					return nullptr;
				}
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
		if (ctx.labels.contains(label))
		{
			diagnostics.Report(loc, redefinition_of_label, label_name);
			return nullptr;
		}
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
			if (isa<BoolType>(operand->GetType()))
			{
				diagnostics.Report(loc, bool_forbidden_in_increment);
				return nullptr;
			}
			if (operand->IsLValue())
			{
				if (operand->GetType().IsConst())
				{
					diagnostics.Report(loc, modifying_const_expr);
					return nullptr;
				}
			}
			else
			{
				diagnostics.Report(loc, modifying_rvalue_expr);
				return nullptr;
			}
			break;
		case UnaryExprKind::Plus:
			break;
		case UnaryExprKind::Minus:
			break;
		case UnaryExprKind::BitNot:
			break;
		case UnaryExprKind::LogicalNot:
			if (!isa<BoolType>(operand->GetType()))
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
				if (lhs_type.IsConst())
				{
					diagnostics.Report(loc, modifying_const_expr);
					return nullptr;
				}
			}
			else
			{
				diagnostics.Report(loc, modifying_rvalue_expr);
				return nullptr;
			}

			if (!lhs_type->IsAssignableFrom(rhs->GetType()))
			{
				diagnostics.Report(loc, incompatible_initializer);
				return nullptr;
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
			if (isoneof<VoidType, ArrayType, FuncType>(lhs_type) ||
				isoneof<VoidType, ArrayType, FuncType>(rhs_type))
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
			if (!isoneof<IntType, BoolType>(lhs_type) || !isoneof<IntType, BoolType>(rhs_type))
			{
				diagnostics.Report(loc, modulo_operands_not_integral);
				return nullptr;
			}
			if (!isa<IntType>(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!isa<IntType>(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(rhs));
			}
			type = builtin_types::Int;
		}
		break;
		case BinaryExprKind::ShiftLeft:
		case BinaryExprKind::ShiftRight:
		{
			if (!isoneof<IntType, BoolType>(lhs_type) || !isoneof<IntType, BoolType>(rhs_type))
			{
				diagnostics.Report(loc, shift_operands_not_integral);
				return nullptr;
			}
			if (!isa<IntType>(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!isa<IntType>(rhs_type))
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
			if (!isoneof<IntType, BoolType>(lhs_type) || !isoneof<IntType, BoolType>(rhs_type))
			{
				diagnostics.Report(loc, bitwise_operands_not_integral);
				return nullptr;
			}
			if (!isa<IntType>(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(lhs));
			}
			if (!isa<IntType>(rhs_type))
			{
				rhs = ActOnImplicitCastExpr(loc, builtin_types::Int, std::move(rhs));
			}
			type = builtin_types::Int;
		}
		break;
		case BinaryExprKind::LogicalAnd:
		case BinaryExprKind::LogicalOr:
		{
			if (!isa<BoolType>(lhs_type))
			{
				lhs = ActOnImplicitCastExpr(loc, builtin_types::Bool, std::move(lhs));
			}
			if (!isa<BoolType>(rhs_type))
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
			if (isoneof<VoidType, ArrayType, FuncType>(lhs_type) ||
				isoneof<VoidType, ArrayType, FuncType>(rhs_type))
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
			OLA_ASSERT(false);
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
			return nullptr;
		}
		else if (!cond_expr->GetType()->IsSameAs(builtin_types::Bool))
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

	UniqueCallExprPtr Sema::ActOnCallExpr(SourceLocation const& loc, UniqueExprPtr&& func_expr, UniqueExprPtrList&& args)
	{
		if (isa<IdentifierExpr>(func_expr.get()))
		{
			IdentifierExpr const* func_identifier = cast<IdentifierExpr>(func_expr.get());
			std::vector<Decl*>& candidate_decls = ctx.decl_sym_table.LookUp_Overload(func_identifier->GetName());

			std::vector<FunctionDecl*> match_decls{};
			uint32 match_conversions_needed = UINT32_MAX;
			for (Decl* decl : candidate_decls)
			{
				if (isoneof<FunctionDecl, MethodDecl>(decl))
				{
					FunctionDecl* func_decl = cast<FunctionDecl>(decl);
					FuncType const& func_type = func_decl->GetFuncType();
					std::span<QualType const> param_types = func_type.GetParams();
					if (args.size() != param_types.size()) continue;

					bool incompatible_arg = false;
					for (uint64 i = 0; i < param_types.size(); ++i)
					{
						UniqueExprPtr& arg = args[i];
						QualType const& func_param_type = param_types[i];

						if (isa<RefType>(func_param_type) && !arg->IsLValue())
						{
							incompatible_arg = true;
							break;
						}
						if (!func_param_type->IsAssignableFrom(arg->GetType()))
						{
							incompatible_arg = true;
							break;
						}
					}
					if (incompatible_arg) continue;

					uint32 current_conversions_needed = 0;
					for (uint64 i = 0; i < param_types.size(); ++i)
					{
						UniqueExprPtr& arg = args[i];
						QualType const& func_param_type = param_types[i];
						if (!func_param_type->IsSameAs(arg->GetType()))
						{
							++current_conversions_needed;
						}
					}

					if (match_conversions_needed == current_conversions_needed)
					{
						match_decls.push_back(func_decl);
					}
					else if (current_conversions_needed < match_conversions_needed)
					{
						match_conversions_needed = current_conversions_needed;
						match_decls.clear();
						match_decls.push_back(func_decl);
					}
				}
			}

			if (match_decls.empty())
			{
				diagnostics.Report(loc, matching_function_not_found);
				return nullptr;
			}
			if (match_decls.size() > 1)
			{
				diagnostics.Report(loc, matching_function_ambiguous);
				return nullptr;
			}

			FunctionDecl* match_decl = match_decls[0];
			FuncType const& match_func_type = match_decl->GetFuncType();

			std::span<QualType const> param_types = match_func_type.GetParams();
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (!func_param_type->IsSameAs(arg->GetType()))
				{
					arg = ActOnImplicitCastExpr(loc, func_param_type, std::move(arg));
				}
			}

			if (isa<MethodDecl>(match_decl))
			{
				UniqueMemberExprPtr member_expr = MakeUnique<MemberExpr>(loc);
				member_expr->SetClassExpr(ActOnThisExpr(loc, true));
				member_expr->SetMemberDecl(cast<MethodDecl>(match_decl));
				member_expr->SetType(match_func_type);

				UniqueMethodCallExprPtr method_call_expr = MakeUnique<MethodCallExpr>(loc, cast<MethodDecl>(match_decl));
				method_call_expr->SetType(match_func_type.GetReturnType());
				method_call_expr->SetArgs(std::move(args));
				method_call_expr->SetCallee(std::move(member_expr));
				if (isa<RefType>(method_call_expr->GetType())) method_call_expr->SetLValue();
				return method_call_expr;
			}
			else
			{
				UniqueCallExprPtr func_call_expr = MakeUnique<CallExpr>(loc, match_decl);
				func_call_expr->SetType(match_func_type.GetReturnType());
				func_call_expr->SetArgs(std::move(args));
				func_call_expr->SetCallee(MakeUnique<DeclRefExpr>(match_decl, loc));
				if (isa<RefType>(func_call_expr->GetType())) func_call_expr->SetLValue();
				return func_call_expr;
			}
		}
		else if (isa<ThisExpr>(func_expr.get()))
		{

		}
		else if (isa<SuperExpr>(func_expr.get()))
		{
			if (!ctx.is_constructor)
			{
				diagnostics.Report(loc, base_ctor_call_outside_ctor);
				return nullptr;
			}
			if (!ctx.current_base_class)
			{
				diagnostics.Report(loc, base_ctor_call_without_base_class);
				return nullptr;
			}

			ctx.current_base_class->FindConstructors();
		}
		diagnostics.Report(loc, invalid_function_call);
		return nullptr;
	}

	UniqueIntLiteralPtr Sema::ActOnConstantInt(int64 value, SourceLocation const& loc)
	{
		return MakeUnique<IntLiteral>(value, loc);
	}

	UniqueIntLiteralPtr Sema::ActOnLengthOperator(QualType const& type, SourceLocation const& loc)
	{
		if (!isa<ArrayType>(type))
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

	UniqueCharLiteralPtr Sema::ActOnConstantChar(std::string_view str, SourceLocation const& loc)
	{
		if (str.size() != 1)
		{
			diagnostics.Report(loc, invalid_char_literal);
			return nullptr;
		}
		return MakeUnique<CharLiteral>(str[0], loc);
	}

	UniqueStringLiteralPtr Sema::ActOnConstantString(std::string_view str, SourceLocation const& loc)
	{
		return MakeUnique<StringLiteral>(str, loc);
	}

	UniqueBoolLiteralPtr Sema::ActOnConstantBool(bool value, SourceLocation const& loc)
	{
		return MakeUnique<BoolLiteral>(value, loc);
	}

	UniqueFloatLiteralPtr Sema::ActOnConstantFloat(double value, SourceLocation const& loc)
	{
		return MakeUnique<FloatLiteral>(value, loc);
	}

	UniqueExprPtr Sema::ActOnIdentifier(std::string_view name, SourceLocation const& loc, bool overloaded_symbol)
	{
		if (overloaded_symbol)
		{
			std::vector<Decl*>& decls = ctx.decl_sym_table.LookUp_Overload(name);
			if (!decls.empty()) return MakeUnique<IdentifierExpr>(name, loc);

			if (ClassDecl const* base_class_decl = ctx.current_base_class)
			{
				std::vector<MethodDecl const*> method_decls = base_class_decl->FindMethodDecls(name);
				if (!method_decls.empty()) return MakeUnique<IdentifierExpr>(name, loc);
			}
		}
		else
		{
			if (Decl* decl = ctx.decl_sym_table.LookUp(name))
			{
				UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(decl, loc);
				if (decl->IsMember()) return ActOnFieldAccess(loc, ActOnThisExpr(loc, true), std::move(decl_ref));
				else return decl_ref;
			}
			else if (ClassDecl const* base_class_decl = ctx.current_base_class)
			{
				if (Decl* class_member_decl = base_class_decl->FindFieldDecl(name))
				{
					UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(class_member_decl, loc);
					return ActOnFieldAccess(loc, ActOnSuperExpr(loc, true), std::move(decl_ref));
				}
			}
		}
		diagnostics.Report(loc, undeclared_identifier, name);
		return nullptr;
	}

	UniqueIdentifierExprPtr Sema::ActOnMemberIdentifier(std::string_view name, SourceLocation const& loc, bool overloaded_symbol)
	{
		if (!ctx.current_class_expr_stack.empty())
		{
			Expr const* current_class_expr = ctx.current_class_expr_stack.back();
			if (!isoneof<ThisExpr, SuperExpr>(current_class_expr))
			{
				QualType const& class_expr_type = current_class_expr->GetType();
				ClassType const* class_type = nullptr;
				if (isa<ClassType>(class_expr_type))
				{
					class_type = &type_cast<ClassType>(class_expr_type);
				}
				else if (isa<RefType>(class_expr_type))
				{
					RefType const& ref_type = type_cast<RefType>(class_expr_type);
					if (isa<ClassType>(ref_type.GetReferredType()))
					{
						class_type = &type_cast<ClassType>(ref_type.GetReferredType());
					}
				}

				if (!class_type)
				{
					diagnostics.Report(loc, invalid_member_access);
					return nullptr;
				}
				ClassDecl const* class_decl = class_type->GetClassDecl();
				if (overloaded_symbol)
				{
					std::vector<MethodDecl const*> method_decls = class_decl->FindMethodDecls(name);
					if (!method_decls.empty()) return MakeUnique<IdentifierExpr>(name, loc);
				}
				else
				{
					if (FieldDecl* class_member_decl = class_decl->FindFieldDecl(name))
					{
						UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(class_member_decl, loc);
						return decl_ref;
					}
				}
			}
			else if (isa<ThisExpr>(current_class_expr))
			{
				if (overloaded_symbol)
				{
					std::vector<Decl*> decls = ctx.decl_sym_table.LookUpMember_Overload(name);
					if (!decls.empty()) return MakeUnique<IdentifierExpr>(name, loc);
				}
				else
				{
					Decl* decl = ctx.decl_sym_table.LookUpMember(name);
					return MakeUnique<DeclRefExpr>(decl, loc);
				}
			}
			else if (isa<SuperExpr>(current_class_expr))
			{
				OLA_ASSERT(ctx.current_base_class);
				ClassDecl const* base_class_decl = ctx.current_base_class;

				if (overloaded_symbol)
				{
					std::vector<MethodDecl const*> decls = base_class_decl->FindMethodDecls(name);
					if (!decls.empty()) return MakeUnique<IdentifierExpr>(name, loc);
				}
				else
				{
					if (Decl* class_member_decl = base_class_decl->FindFieldDecl(name))
					{
						UniqueDeclRefExprPtr decl_ref = MakeUnique<DeclRefExpr>(class_member_decl, loc);
						return decl_ref;
					}
				}
			}
		}
		diagnostics.Report(loc, undeclared_identifier, name);
		return nullptr;
	}

	UniqueInitializerListExprPtr Sema::ActOnInitializerListExpr(SourceLocation const& loc, UniqueExprPtrList&& expr_list)
	{
		QualType expr_type{};
		expr_type = expr_list.front()->GetType();
		QualType base_type(expr_type);
		ArrayType arr_type(base_type, expr_list.size());

		for (auto const& expr : expr_list)
		{
			if (!expr->GetType()->IsSameAs(expr_type))
			{
				diagnostics.Report(loc, init_list_element_expressions_type_mismatch);
				return nullptr;
			}
		}
		UniqueInitializerListExprPtr init_list_expr = MakeUnique<InitializerListExpr>(loc);
		init_list_expr->SetType(arr_type);
		init_list_expr->SetInitList(std::move(expr_list));
		return init_list_expr;
	}

	UniqueArrayAccessExprPtr Sema::ActOnArrayAccessExpr(SourceLocation const& loc, UniqueExprPtr&& array_expr, UniqueExprPtr&& index_expr)
	{
		if (!isa<ArrayType>(array_expr->GetType()))
		{
			diagnostics.Report(loc, subscripted_value_not_array);
			return nullptr;
		}
		if (!isa<IntType>(index_expr->GetType()))
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

	UniqueMemberExprPtr Sema::ActOnFieldAccess(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueIdentifierExprPtr&& field_name)
	{
		QualType const& class_expr_type = class_expr->GetType();
		if (!isa<ClassType>(class_expr_type))
		{
			if (!isa<RefType>(class_expr_type))
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}

			RefType const& ref_type = type_cast<RefType>(class_expr_type);
			if (!isa<ClassType>(ref_type.GetReferredType()))
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}
		}

		OLA_ASSERT(isa<DeclRefExpr>(field_name.get()));
		DeclRefExpr const* member_decl_ref = cast<DeclRefExpr>(field_name.get());
		Decl const* member_decl = member_decl_ref->GetDecl();

		if (!isoneof<ThisExpr, SuperExpr>(class_expr.get()) && member_decl->IsPrivate())
		{
			diagnostics.Report(loc, private_member_access);
			return nullptr;
		}

		bool const class_type_is_const = class_expr->GetType().IsConst();
		QualType expr_type = field_name->GetType();
		if (class_type_is_const) expr_type.AddConst();

		UniqueMemberExprPtr member_expr = MakeUnique<MemberExpr>(loc);
		member_expr->SetClassExpr(std::move(class_expr));
		member_expr->SetMemberDecl(member_decl);
		member_expr->SetType(expr_type);
		return member_expr;
	}

	UniqueMethodCallExprPtr Sema::ActOnMethodCall(SourceLocation const& loc, UniqueExprPtr&& class_expr, UniqueIdentifierExprPtr&& member_identifier, UniqueExprPtrList&& args)
	{
		QualType const& class_expr_type = class_expr->GetType();
		ClassDecl const* class_decl = nullptr;
		if (!isa<ClassType>(class_expr_type))
		{
			if (!isa<RefType>(class_expr_type))
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}

			RefType const& ref_type = type_cast<RefType>(class_expr_type);
			if (!isa<ClassType>(ref_type.GetReferredType()))
			{
				diagnostics.Report(loc, invalid_member_access);
				return nullptr;
			}
			else
			{
				class_decl = type_cast<ClassType>(ref_type.GetReferredType()).GetClassDecl();
			}
		}
		else
		{
			class_decl = type_cast<ClassType>(class_expr_type).GetClassDecl();
		}
		OLA_ASSERT(class_decl);

		std::vector<MethodDecl const*> candidate_decls = class_decl->FindMethodDecls(member_identifier->GetName());
		std::vector<MethodDecl const*> match_decls{};
		uint32 match_conversions_needed = UINT32_MAX;
		for (MethodDecl const* method_decl : candidate_decls)
		{
			FuncType const& func_type = method_decl->GetFuncType();
			std::span<QualType const> param_types = func_type.GetParams();
			if (args.size() != param_types.size()) continue;

			bool incompatible_arg = false;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];

				if (isa<RefType>(func_param_type) && !arg->IsLValue())
				{
					incompatible_arg = true;
					break;
				}
				if (!func_param_type->IsAssignableFrom(arg->GetType()))
				{
					incompatible_arg = true;
					break;
				}
			}
			if (incompatible_arg) continue;

			uint32 current_conversions_needed = 0;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (!func_param_type->IsSameAs(arg->GetType()))
				{
					++current_conversions_needed;
				}
			}

			if (match_conversions_needed == current_conversions_needed)
			{
				match_decls.push_back(method_decl);
			}
			else if (current_conversions_needed < match_conversions_needed)
			{
				match_conversions_needed = current_conversions_needed;
				match_decls.clear();
				match_decls.push_back(method_decl);
			}
		}

		if (match_decls.empty())
		{
			diagnostics.Report(loc, matching_function_not_found);
			return nullptr;
		}
		if (match_decls.size() > 1)
		{
			diagnostics.Report(loc, matching_function_ambiguous);
			return nullptr;
		}

		MethodDecl const* match_decl = match_decls[0];
		FuncType const& match_decl_type = match_decl->GetFuncType();
		if (!isoneof<ThisExpr, SuperExpr>(class_expr.get()) && match_decl->IsPrivate())
		{
			diagnostics.Report(loc, private_member_access);
			return nullptr;
		}

		std::span<QualType const> param_types = match_decl_type.GetParams();
		for (uint64 i = 0; i < param_types.size(); ++i)
		{
			UniqueExprPtr& arg = args[i];
			QualType const& func_param_type = param_types[i];
			if (!func_param_type->IsSameAs(arg->GetType()))
			{
				arg = ActOnImplicitCastExpr(loc, func_param_type, std::move(arg));
			}
		}

		bool is_method_const = match_decl->IsConst();
		if (!is_method_const)
		{
			if (class_expr->GetType().IsConst())
			{
				diagnostics.Report(loc, invalid_function_call);
				return nullptr;
			}
		}

		UniqueMemberExprPtr member_expr = MakeUnique<MemberExpr>(loc);
		member_expr->SetClassExpr(std::move(class_expr));
		member_expr->SetMemberDecl(match_decl);
		member_expr->SetType(match_decl_type);

		UniqueMethodCallExprPtr method_call_expr = MakeUnique<MethodCallExpr>(loc, match_decl);
		method_call_expr->SetType(match_decl_type.GetReturnType());
		method_call_expr->SetArgs(std::move(args));
		method_call_expr->SetCallee(std::move(member_expr));
		if (isa<RefType>(method_call_expr->GetType())) method_call_expr->SetLValue();
		return method_call_expr;
	}

	UniqueThisExprPtr Sema::ActOnThisExpr(SourceLocation const& loc, bool implicit)
	{
		UniqueThisExprPtr this_expr = MakeUnique<ThisExpr>(loc);
		this_expr->SetImplicit(implicit);
		QualType this_type(ClassType(nullptr), ctx.is_method_const ? Qualifier_Const : Qualifier_None);
		this_expr->SetType(this_type);
		return this_expr;
	}

	UniqueSuperExprPtr Sema::ActOnSuperExpr(SourceLocation const& loc, bool implicit)
	{
		if (!ctx.current_base_class)
		{
			diagnostics.Report(loc, super_used_in_wrong_context);
			return nullptr;
		}
		UniqueSuperExprPtr super_expr = MakeUnique<SuperExpr>(loc);
		super_expr->SetImplicit(implicit);
		QualType super_type(ClassType(ctx.current_base_class), ctx.is_method_const ? Qualifier_Const : Qualifier_None);
		super_expr->SetType(super_type);
		return super_expr;
	}

	UniqueConstructorExprPtr Sema::ActOnConstructorExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtrList&& args)
	{
		if (!isa<ClassType>(type))
		{
			diagnostics.Report(loc, ctor_init_on_non_class_variable);
			return nullptr;
		}
		ClassDecl const* class_decl = type_cast<ClassType>(type).GetClassDecl();
		std::vector<ConstructorDecl const*> candidate_ctors = class_decl->FindConstructors();
		std::vector<ConstructorDecl const*> match_ctors{};
		uint32 match_conversions_needed = UINT32_MAX;

		for (ConstructorDecl const* ctor : candidate_ctors)
		{
			FuncType const& func_type = ctor->GetFuncType();
			std::span<QualType const> param_types = func_type.GetParams();
			if (args.size() != param_types.size()) continue;

			bool incompatible_arg = false;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (isa<RefType>(func_param_type) && !arg->IsLValue())
				{
					incompatible_arg = true;
					break;
				}
				if (!func_param_type->IsAssignableFrom(arg->GetType()))
				{
					incompatible_arg = true;
					break;
				}
			}
			if (incompatible_arg) continue;

			uint32 current_conversions_needed = 0;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (!func_param_type->IsSameAs(arg->GetType()))
				{
					++current_conversions_needed;
				}
			}
			if (match_conversions_needed == current_conversions_needed)
			{
				match_ctors.push_back(ctor);
			}
			else if (current_conversions_needed < match_conversions_needed)
			{
				match_conversions_needed = current_conversions_needed;
				match_ctors.clear();
				match_ctors.push_back(ctor);
			}
		}

		if (match_ctors.empty())
		{
			diagnostics.Report(loc, matching_ctor_not_found);
			return nullptr;
		}
		if (match_ctors.size() > 1)
		{
			diagnostics.Report(loc, matching_ctor_ambiguous);
			return nullptr;
		}

		ConstructorDecl const* match_ctor = match_ctors[0];
		std::span<QualType const> param_types = match_ctor->GetFuncType().GetParams();
		for (uint64 i = 0; i < param_types.size(); ++i)
		{
			UniqueExprPtr& arg = args[i];
			QualType const& func_param_type = param_types[i];
			if (!func_param_type->IsSameAs(arg->GetType()))
			{
				arg = ActOnImplicitCastExpr(loc, func_param_type, std::move(arg));
			}
		}

		UniqueConstructorExprPtr ctor_expr = MakeUnique<ConstructorExpr>(loc, match_ctor);
		ctor_expr->SetType(type);
		ctor_expr->SetArgs(std::move(args));
		return ctor_expr;
	}

	UniqueImplicitCastExprPtr Sema::ActOnImplicitCastExpr(SourceLocation const& loc, QualType const& type, UniqueExprPtr&& expr)
	{
		QualType const& cast_type = type;
		QualType const& operand_type = expr->GetType();

		if (isa<ArrayType>(cast_type) || isa<ArrayType>(operand_type)) diagnostics.Report(loc, invalid_cast);
		if (isa<VoidType>(cast_type)) diagnostics.Report(loc, invalid_cast);
		if (!cast_type->IsAssignableFrom(operand_type)) diagnostics.Report(loc, invalid_cast);

		UniqueImplicitCastExprPtr cast_expr = MakeUnique<ImplicitCastExpr>(loc, type);
		cast_expr->SetLValue(expr->IsLValue());
		cast_expr->SetOperand(std::move(expr));
		return cast_expr;
	}

	template<typename DeclType> requires std::is_base_of_v<VarDecl, DeclType>
	UniquePtr<DeclType> Sema::ActOnVariableDeclCommon(std::string_view name, SourceLocation const& loc, QualType const& type, UniqueExprPtr&& init_expr, DeclVisibility visibility)
	{
		bool const has_init = (init_expr != nullptr);
		bool has_type_specifier = !type.IsNull();
		bool is_ref_type = has_type_specifier && isa<RefType>(type);
		if (has_type_specifier && is_ref_type)
		{
			RefType const& ref_type = type_cast<RefType>(type);
			has_type_specifier = !ref_type.GetReferredType().IsNull();
		}
		bool const init_expr_is_decl_ref = has_init && isa<DeclRefExpr>(init_expr.get());
		bool const init_expr_const_ref = has_init && isa<RefType>(init_expr->GetType()) && init_expr->GetType().IsConst();

		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
		}

		if (has_init && has_type_specifier)
		{
			if (!type->IsAssignableFrom(init_expr->GetType()))
			{
				diagnostics.Report(loc, incompatible_initializer);
				return nullptr;
			}
			else if (!type->IsSameAs(init_expr->GetType()))
			{
				init_expr = ActOnImplicitCastExpr(loc, type, std::move(init_expr));
			}
		}
		else if (!has_init && !has_type_specifier)
		{
			diagnostics.Report(loc, missing_type_specifier_or_init_expr);
			return nullptr;
		}

		if (ctx.decl_sym_table.LookUpCurrentScope(name))
		{
			diagnostics.Report(loc, redefinition_of_identifier, name);
			return nullptr;
		}
		if (has_type_specifier && isa<VoidType>(type))
		{
			diagnostics.Report(loc, void_invalid_context);
			return nullptr;
		}

		UniquePtr<DeclType> var_decl = MakeUnique<DeclType>(name, loc);
		var_decl->SetGlobal(ctx.decl_sym_table.IsGlobal());
		var_decl->SetVisibility(visibility);
		OLA_ASSERT(var_decl->IsGlobal() || !var_decl->IsExtern());

		if (var_decl->IsGlobal() && init_expr && !init_expr->IsConstexpr())
		{
			diagnostics.Report(loc, global_variable_initializer_not_constexpr, name);
			return nullptr;
		}

		bool is_array = (has_type_specifier && isa<ArrayType>(type)) || (has_init && isa<ArrayType>(init_expr->GetType()));
		if (is_array)
		{
			if (is_ref_type)
			{
				diagnostics.Report(loc, arrays_cannot_be_refs);
				return nullptr;
			}
			if (Expr* array_init_expr = init_expr.get())
			{
				ArrayType const& init_expr_type = type_cast<ArrayType>(array_init_expr->GetType());

				bool is_multidimensional_array = isa<ArrayType>(init_expr_type.GetBaseType());
				if (is_multidimensional_array && init_expr_is_decl_ref)
				{
					diagnostics.Report(loc, multidimensional_arrays_cannot_alias);
					return nullptr;
				}
				if (has_type_specifier && !is_multidimensional_array)
				{
					ArrayType const& decl_type = type_cast<ArrayType>(type);
					if (!decl_type.GetBaseType().IsConst() && init_expr_type.GetBaseType().IsConst())
					{
						diagnostics.Report(loc, assigning_const_array_to_non_const_array, name);
						return nullptr;
					}
				}

				if (has_type_specifier && isoneof<InitializerListExpr, StringLiteral>(array_init_expr))
				{
					ArrayType arr_type = type_cast<ArrayType>(type);
					uint64 const arr_type_size = arr_type.GetArraySize();
					uint64 const init_arr_size = init_expr_type.GetArraySize();
					if (arr_type_size && arr_type_size < init_arr_size)
					{
						diagnostics.Report(loc, invalid_init_list_expression);
						return nullptr;
					}
					else if (arr_type_size > init_arr_size)
					{
						array_init_expr->SetType(type);
					}
				}

				if (!has_type_specifier)
				{
					QualType base_type = init_expr_type.GetBaseType();
					if (type.IsConst()) base_type.AddConst();
					if (init_expr_is_decl_ref)
					{
						QualType var_type(ArrayType(base_type, 0));
						var_decl->SetType(var_type);
					}
					else
					{
						QualType var_type(ArrayType(base_type, init_expr_type.GetArraySize()));
						var_decl->SetType(var_type);
					}
				}
				else
				{
					ArrayType arr_type = type_cast<ArrayType>(type);
					if (arr_type.GetArraySize() == 0)
					{
						QualType base_type = arr_type.GetBaseType();
						if (type.IsConst()) base_type.AddConst();
						QualType var_type(ArrayType(base_type, init_expr_type.GetArraySize()));
						var_decl->SetType(var_type);
					}
					else
					{
						var_decl->SetType(type);
					}
				}
			}
			else var_decl->SetType(type);
		}
		else if ((has_init && !has_type_specifier))
		{
			QualType var_type(init_expr->GetType());
			if (is_ref_type) var_type = RefType(var_type);
			if (type.IsConst()) var_type.AddConst();
			var_decl->SetType(var_type);
		}
		else
		{
			var_decl->SetType(type);
		}
		var_decl->SetInitExpr(std::move(init_expr));

		QualType const& var_type = var_decl->GetType();
		if (isa<RefType>(var_type))
		{
			if (!var_decl->GetInitExpr())
			{
				diagnostics.Report(loc, ref_var_needs_init);
				return nullptr;
			}
			if (!var_decl->GetInitExpr()->IsLValue())
			{
				diagnostics.Report(loc, ref_var_rvalue_bind);
				return nullptr;
			}
			if (!var_type.IsConst() && init_expr_const_ref)
			{
				diagnostics.Report(loc, nonconst_ref_init_with_const_ref);
				return nullptr;
			}
		}
		if (isa<ClassType>(var_type))
		{
			ClassDecl const* class_decl = type_cast<ClassType>(var_type).GetClassDecl();
			if (class_decl->IsAbstract())
			{
				diagnostics.Report(loc, variable_type_abstract, class_decl->GetName());
				return nullptr;
			}
		}

		ctx.decl_sym_table.Insert(var_decl.get());
		return var_decl;
	}


	template<typename DeclType> requires std::is_base_of_v<ola::FunctionDecl, DeclType>
	std::vector<DeclType const*> Sema::ResolveCall(std::vector<DeclType const*> const& candidate_decls, UniqueExprPtrList&& args)
	{
		std::vector<DeclType const*> match_decls{};
		uint32 match_conversions_needed = UINT32_MAX;
		for (DeclType const* decl : candidate_decls)
		{
			FuncType const& func_type = decl->GetFuncType();
			std::span<QualType const> param_types = func_type.GetParams();
			if (args.size() != param_types.size()) continue;

			bool incompatible_arg = false;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (isa<RefType>(func_param_type) && !arg->IsLValue())
				{
					incompatible_arg = true;
					break;
				}
				if (!func_param_type->IsAssignableFrom(arg->GetType()))
				{
					incompatible_arg = true;
					break;
				}
			}
			if (incompatible_arg) continue;

			uint32 current_conversions_needed = 0;
			for (uint64 i = 0; i < param_types.size(); ++i)
			{
				UniqueExprPtr& arg = args[i];
				QualType const& func_param_type = param_types[i];
				if (!func_param_type->IsSameAs(arg->GetType()))
				{
					++current_conversions_needed;
				}
			}
			if (match_conversions_needed == current_conversions_needed)
			{
				match_decls.push_back(decl);
			}
			else if (current_conversions_needed < match_conversions_needed)
			{
				match_conversions_needed = current_conversions_needed;
				match_decls.clear();
				match_decls.push_back(decl);
			}
		}
		return match_decls;
	}
}

