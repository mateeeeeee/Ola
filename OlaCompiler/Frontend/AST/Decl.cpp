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

	std::vector<LabelStmt const*> const& FunctionDecl::GetLabels() const
	{
		OLA_ASSERT(body_stmt);
		if (!labels.empty()) return labels;

		LabelVisitor label_visitor(labels);
		body_stmt->Accept(label_visitor, 0);
		return labels;
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

	std::vector<MethodDecl const*> ClassDecl::GetVTable() const
	{
		OLA_ASSERT(IsPolymorphic());

		std::vector<MethodDecl const*> vtable_entries;
		if (base_class)
		{
			std::vector<MethodDecl const*> base_vtable = base_class->GetVTable();
			vtable_entries.insert(vtable_entries.end(), base_vtable.begin(), base_vtable.end());
		}

		for (auto const& method : methods)
		{
			if (method->IsVirtual()) 
			{
				auto it = std::find_if(vtable_entries.begin(), vtable_entries.end(),
					[&method](MethodDecl const* entry)
					{
						//for now compare names, later signatures
						return entry->GetName() == method->GetName();
					});

				if (it != vtable_entries.end()) *it = method.get();
				else vtable_entries.push_back(method.get()); 
			}
		}
		return vtable_entries;
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

