#include "Decl.h"
#include "ASTVisitor.h"
#include "Expr.h"

namespace ola
{
	class LabelVisitor : public ASTVisitor
	{
	public:
		explicit LabelVisitor(std::vector<LabelStmt const*>& labels) : labels(labels) {}
		virtual void Visit(LabelStmt const& label, uint32) override
		{
			labels.push_back(&label);
		}

	private:
		std::vector<LabelStmt const*>& labels;
	};
	class ThisVisitor : public ASTVisitor
	{
	public:
		explicit ThisVisitor(QualType const& this_type) : this_type(this_type) {}
		virtual void Visit(ThisExpr const& this_expr, uint32) override
		{
			ThisExpr& mut_this_expr = const_cast<ThisExpr&>(this_expr);
			if (this_expr.GetType().IsConst()) this_type.AddConst();
			mut_this_expr.SetType(this_type);
		}

	private:
		QualType this_type;
	};

	void FunctionDecl::SetParamDecls(UniqueParamVarDeclPtrList&& param_decls)
	{
		param_declarations = std::move(param_decls);
		for (auto& param_decl : param_declarations) param_decl->SetParentDecl(this);
	}
	void FunctionDecl::SetBodyStmt(UniqueCompoundStmtPtr&& _body_stmt)
	{
		body_stmt = std::move(_body_stmt);
		LabelVisitor label_visitor(labels);
		body_stmt->Accept(label_visitor, 0);
	}

	void ClassDecl::SetFields(UniqueFieldDeclPtrList&& _fields)
	{
		fields = std::move(_fields);
		uint64 field_index_offset = base_class ? base_class->GetFieldCount() : 0;
		for (uint32 i = 0; i < fields.size(); ++i)
		{
			auto& field = fields[i];
			field->SetParentDecl(this);
			field->SetFieldIndex(field_index_offset + i);
		}
	}
	void ClassDecl::SetMethods(UniqueMethodDeclPtrList&& _methods)
	{
		methods = std::move(_methods);
		ThisVisitor this_visitor(ClassType(this));
		for (auto& method : methods)
		{
			method->SetParentDecl(this);
			method->Accept(this_visitor, 0);
		}
	}
	void ClassDecl::BuildVTable()
	{
		polymorphic = IsPolymorphicImpl();
		if (!polymorphic) return;
		
		if (base_class)
		{
			std::vector<MethodDecl const*> base_vtable = base_class->GetVTable();
			vtable.reserve(base_vtable.size());
			for (uint64 i = 0; i < base_vtable.size(); ++i)
			{
				base_vtable[i]->SetVTableIndex(vtable.size());
				vtable.push_back(base_vtable[i]);
			}
		}
		for (auto const& method : methods)
		{
			if (method->IsVirtual())
			{
				auto it = std::find_if(vtable.begin(), vtable.end(),
					[&method](MethodDecl const* entry)
					{
						if (entry->GetName() != method->GetName()) return false;

						FuncType const& entry_type = entry->GetFuncType();
						FuncType const& method_type = method->GetFuncType();
						if (!entry_type.GetReturnType()->IsSameAs(method_type.GetReturnType())) return false;
						if (entry_type.GetParamCount() != method_type.GetParamCount()) return false;
						for (uint32 i = 0; i < entry_type.GetParamCount(); ++i)
						{
							if (!entry_type.GetParams()[i]->IsSameAs(method_type.GetParams()[i])) return false;
						}
						return true;
					});

				if (it != vtable.end())
				{
					method->SetVTableIndex((*it)->GetVTableIndex());
					*it = method.get();
				}
				else
				{
					method->SetVTableIndex(vtable.size());
					vtable.push_back(method.get());
				}
			}
		}

		for (MethodDecl const* vtable_entry : vtable)
		{
			if (vtable_entry->IsPure())
			{
				abstract = true;
				break;
			}
		}
	}
	std::vector<MethodDecl const*> const& ClassDecl::GetVTable() const
	{
		OLA_ASSERT(IsPolymorphic());
		return vtable;
	}
	bool ClassDecl::IsPolymorphicImpl() const
	{
		for (auto const& method : methods) if (method->IsVirtual()) return true;
		return base_class ? base_class->IsPolymorphic() : false;
	}

	void Decl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(false);
	}
	void VarDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (init_expr) init_expr->Accept(visitor, depth + 1);
	}
	void ParamVarDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void FieldDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (body_stmt) body_stmt->Accept(visitor, depth + 1);
	}
	void MethodDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (body_stmt) body_stmt->Accept(visitor, depth + 1);
	}
	void EnumMemberDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void EnumDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& enum_member : enum_members) enum_member->Accept(visitor, depth + 1);
	}
	void AliasDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ClassDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& field : fields) field->Accept(visitor, depth + 1);
		for (auto const& method : methods) method->Accept(visitor, depth + 1);
	}

	void Decl::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(false);
	}
	void VarDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ParamVarDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FieldDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void MethodDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void EnumMemberDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void EnumDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void AliasDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ClassDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

}

