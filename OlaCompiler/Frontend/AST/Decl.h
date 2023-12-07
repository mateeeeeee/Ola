#pragma once
#include "ASTNode.h"
#include "ASTTypeAliases.h"
#include "Stmt.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"

namespace ola
{
	enum class DeclKind : uint8
	{
		Var,
		ParamVar,
		Field,
		Function,
		Method,
		Enum,
		EnumMember,
		Alias,
		Class
	};
	enum class DeclVisibility : uint8
	{
		None,
		Private,
		Public,
		Extern
	};

	class Decl : public ASTNode
	{
	public:
		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

		void SetType(QualType const& _type) { type = _type; }
		QualType const& GetType() const { return type; }

		void SetVisibility(DeclVisibility _visibility)
		{
			visibility = _visibility;
		}
		bool IsPublic() const { return visibility == DeclVisibility::Public; }
		bool IsPrivate() const { return visibility == DeclVisibility::Private; }
		bool IsExtern() const { return visibility == DeclVisibility::Extern; }

		virtual bool IsTag() const { return false; }
		virtual bool IsMember() const { return false; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		DeclKind const decl_kind;
		std::string name;
		SourceLocation source_loc;
		QualType type;
		DeclVisibility visibility = DeclVisibility::None;

	protected:
		Decl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
	};

	class VarDecl : public Decl
	{
	public:
		VarDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Var, name, loc) {}

		void SetGlobal(bool _is_global)
		{
			is_global = _is_global;
		}
		bool IsGlobal() const { return is_global; }

		void SetInitExpr(UniqueExprPtr&& expr)
		{
			init_expr = std::move(expr);
		}
		Expr const* GetInitExpr() const { return init_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Var; }
	private:
		UniqueExprPtr init_expr = nullptr;
		bool is_global = false;

	protected:
		VarDecl(DeclKind kind, std::string_view name, SourceLocation const& loc) : Decl(kind, name, loc) {}
	};

	class ParamVarDecl final : public VarDecl
	{
	public:
		ParamVarDecl(std::string_view name, SourceLocation const& loc) : VarDecl(DeclKind::ParamVar, name, loc) {}

		void SetParentDecl(FunctionDecl const* _parent)
		{
			parent = _parent;
		}
		FunctionDecl const* GetParentDecl() const { return parent; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::ParamVar; }
	private:
		FunctionDecl const* parent = nullptr;
	};

	class FieldDecl final : public VarDecl
	{
	public:
		FieldDecl(std::string_view name, SourceLocation const& loc) : VarDecl(DeclKind::Field, name, loc) {}

		void SetParentDecl(ClassDecl const* _parent)
		{
			parent = _parent;
		}
		ClassDecl const* GetParentDecl() const { return parent; }
		void SetFieldIndex(uint32 i)
		{
			index = i;
		}
		uint32 GetFieldIndex() const { return index; }

		virtual bool IsMember() const override { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Field; }
	private:
		ClassDecl const* parent = nullptr;
		uint32 index = -1;
	};

	enum FuncAttribute : uint8
	{
		FuncAttribute_None = 0x00,
		FuncAttribute_NoInline = 0x01,
		FuncAttribute_Inline = 0x02
	};
	using FuncAttributes = uint8;

	class FunctionDecl : public Decl
	{
		friend class LabelVisitor;
	public:
		FunctionDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Function, name, loc) {}

		void SetParamDecls(UniqueParamVarDeclPtrList&& param_decls)
		{
			param_declarations = std::move(param_decls);
			for (auto& param_decl : param_declarations) param_decl->SetParentDecl(this);
		}
		void SetBodyStmt(UniqueCompoundStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}
		void SetFuncAttributes(FuncAttributes attrs)
		{
			func_attributes = attrs;
		}
		bool HasFuncAttribute(FuncAttribute attr) const
		{
			return (func_attributes & attr) == attr;
		}

		UniqueParamVarDeclPtrList const& GetParamDecls() const { return param_declarations; }
		CompoundStmt const* GetBodyStmt() const { return body_stmt.get(); }
		ConstLabelStmtPtrList GetLabels() const;
		FuncType const& GetFuncType() const
		{
			OLA_ASSERT(GetType()->GetKind() == TypeKind::Function);
			return type_cast<FuncType>(GetType());
		}
		bool HasDefinition() const
		{
			return body_stmt != nullptr;
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Function; }
	protected:
		UniqueParamVarDeclPtrList param_declarations;
		UniqueCompoundStmtPtr body_stmt;
		mutable ConstLabelStmtPtrList labels;
		FuncAttributes func_attributes = FuncAttribute_None;

	protected:
		FunctionDecl(DeclKind kind, std::string_view name, SourceLocation const& loc) : Decl(kind, name, loc) {}
	};

	enum MethodAttribute : uint8
	{
		MethodAttribute_None = 0x00,
		MethodAttribute_Const = 0x01,
		MethodAttribute_Virtual = 0x02
	};
	using MethodAttributes = uint8;
	class MethodDecl final : public FunctionDecl
	{
	public:
		MethodDecl(std::string_view name, SourceLocation const& loc) : FunctionDecl(DeclKind::Method, name, loc) {}

		void SetParentDecl(ClassDecl const* _parent)
		{
			parent = _parent;
		}
		ClassDecl const* GetParentDecl() const { return parent; }

		void SetMethodAttributes(MethodAttributes attrs)
		{
			method_attrs = attrs;
		}
		bool HasMethodAttribute(MethodAttribute attr) const
		{
			return (method_attrs & attr) == attr;
		}
		bool IsVirtual() const { return HasMethodAttribute(MethodAttribute_Virtual); }
		bool IsConst() const { return HasMethodAttribute(MethodAttribute_Const); }

		virtual bool IsMember() const override { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Method; }
	private:
		ClassDecl const* parent = nullptr;
		MethodAttributes method_attrs = MethodAttribute_None;
	};

	class TagDecl : public Decl
	{
	public:
		virtual bool IsTag() const override { return true; }

	protected:
		TagDecl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc) : Decl(decl_kind, name, loc) {}
	};

	class EnumDecl : public TagDecl
	{
	public:
		EnumDecl(std::string_view name, SourceLocation const& loc) : TagDecl(DeclKind::Enum, name, loc) {}

		void SetEnumMembers(UniqueEnumMemberDeclPtrList&& _enum_members)
		{
			enum_members = std::move(_enum_members);
		}
		UniqueEnumMemberDeclPtrList const& GetEnumMembers() const { return enum_members; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Enum; }
	private:
		UniqueEnumMemberDeclPtrList enum_members;
	};

	class EnumMemberDecl : public Decl
	{
	public:
		EnumMemberDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::EnumMember, name, loc)
		{
			SetType(builtin_types::Enum);
		}

		void SetValue(int64 _value)
		{
			value = _value;
		}
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::EnumMember; }
	private:
		int64 value = 0;
	};

	class AliasDecl : public TagDecl
	{
	public:
		AliasDecl(std::string_view name, SourceLocation const& loc, QualType const& aliased_type) : TagDecl(DeclKind::Alias, name, loc)
		{
			SetType(aliased_type);
			SetVisibility(DeclVisibility::Public);
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Alias; }
	};

	class ClassDecl : public TagDecl
	{
	public:
		ClassDecl(std::string_view name, SourceLocation const& loc) : TagDecl(DeclKind::Class, name, loc) {}

		void SetFields(UniqueFieldDeclPtrList&& _fields)
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
		UniqueFieldDeclPtrList const& GetFields() const { return fields; }
		void SetMethods(UniqueMethodDeclPtrList&& _methods)
		{
			methods = std::move(_methods);
			for (auto& method : methods) method->SetParentDecl(this);
		}
		UniqueMethodDeclPtrList const& GetMethods() const { return methods; }
		void SetBaseClass(ClassDecl const* _base_class) 
		{ 
			base_class  = _base_class;
		}
		ClassDecl const* GetBaseClass() const { return base_class; }

		bool IsDerivedFrom(ClassDecl const* base) const
		{
			ClassDecl const* curr_base_class = base_class;
			while (curr_base_class)
			{
				if (curr_base_class == base) return true;
				curr_base_class = curr_base_class->base_class;
			}
			return false;
		}
		bool IsPolymorphic() const
		{
			for (auto const& method : methods) if (method->IsVirtual()) return true;
			return base_class ? base_class->IsPolymorphic() : false;
		}
		uint64 GetFieldCount() const
		{
			return base_class ? base_class->GetFieldCount() + fields.size() : fields.size();
		}
		Decl* FindMemberDecl(std::string_view name) const
		{
			for (uint32 i = 0; i < fields.size(); ++i)
			{
				if (fields[i]->GetName().compare(name) == 0)
				{
					return fields[i].get();
				}
			}
			for (uint32 i = 0; i < methods.size(); ++i)
			{
				if (methods[i]->GetName().compare(name) == 0)
				{
					return methods[i].get();
				}
			}
			return base_class ? base_class->FindMemberDecl(name) : nullptr;
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Class; }

	private:
		ClassDecl const* base_class = nullptr;
		UniqueFieldDeclPtrList fields;
		UniqueMethodDeclPtrList methods;
	};


	template <typename T> requires std::derived_from<T, Decl>
	inline bool isa(Decl const* decl) { return T::ClassOf(decl); }

	template<typename T> requires std::derived_from<T, Decl>
	inline T* cast(Decl* decl)
	{
		return static_cast<T*>(decl);
	}
	template<typename T> requires std::derived_from<T, Decl>
	inline T const* cast(Decl const* decl)
	{
		return static_cast<T const*>(decl);
	}

	template<typename T> requires std::derived_from<T, Decl>
	inline T* dyn_cast(Decl* decl)
	{
		return isa<T>(decl) ? static_cast<T*>(decl) : nullptr;
	}
	template<typename T> requires std::derived_from<T, Decl>
	inline T const* dyn_cast(Decl const* decl)
	{
		return isa<T>(decl) ? static_cast<T const*>(decl) : nullptr;
	}
}

