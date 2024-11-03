#pragma once
#include "ASTNode.h"
#include "ASTAliases.h"
#include "Stmt.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"
#include "Compiler/RTTI.h"

namespace ola
{
	enum class DeclKind : Uint8
	{
		Var,
		ParamVar,
		Field,
		Function,
		Method,
		Constructor,
		Enum,
		EnumMember,
		Alias,
		Class
	};
	enum class DeclVisibility : Uint8
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
		Bool IsPublic()  const { return  visibility == DeclVisibility::Public; }
		Bool IsPrivate() const { return visibility == DeclVisibility::Private; }
		Bool IsExtern()  const { return  visibility == DeclVisibility::Extern; }

		virtual Bool IsTag() const { return false; }
		virtual Bool IsMember() const { return false; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return true; }

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

		void SetGlobal(Bool _is_global)
		{
			is_global = _is_global;
		}
		Bool IsGlobal() const { return is_global; }

		void SetInitExpr(UniqueExprPtr&& expr)
		{
			init_expr = std::move(expr);
		}
		Expr const* GetInitExpr() const { return init_expr.get(); }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) 
		{ 
			switch (decl->GetDeclKind())
			{
			case DeclKind::Var:
			case DeclKind::ParamVar:
			case DeclKind::Field:
				return true;
			}
			return false;
		}
	private:
		UniqueExprPtr init_expr = nullptr;
		Bool is_global = false;

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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::ParamVar; }
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
		void SetFieldIndex(Uint32 i)
		{
			index = i;
		}
		Uint32 GetFieldIndex() const { return index; }

		virtual Bool IsMember() const override { return true; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Field; }
	private:
		ClassDecl const* parent = nullptr;
		Uint32 index = -1;
	};

	inline Bool HasAttribute(Uint8 attrs, Uint8 attr)
	{
		return (attrs & attr) == attr;
	}

	enum FuncAttribute : Uint8
	{
		FuncAttribute_None = 0x00,
		FuncAttribute_NoInline = 0x01,
		FuncAttribute_Inline = 0x02,
		FuncAttribute_NoMangle = 0x04
	};
	using FuncAttributes = Uint8;

	class FunctionDecl : public Decl
	{
		friend class LabelVisitor;
		static std::string GetTypeMangledName(QualType const&);

	public:
		FunctionDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Function, name, loc) {}

		void SetParamDecls(UniqueParamVarDeclPtrList&& param_decls);
		void SetBodyStmt(UniqueCompoundStmtPtr&& _body_stmt);
		void SetFuncAttributes(FuncAttributes attrs)
		{
			func_attributes = attrs;
		}
		Bool HasFuncAttribute(FuncAttribute attr) const
		{
			return HasAttribute(func_attributes, attr);
		}
		Bool IsInline()   const { return HasFuncAttribute(FuncAttribute_Inline); }
		Bool IsNoInline() const { return HasFuncAttribute(FuncAttribute_NoInline); }
		Bool NoMangle() const { return HasFuncAttribute(FuncAttribute_NoMangle); }

		UniqueParamVarDeclPtrList const& GetParamDecls() const { return param_decls; }
		CompoundStmt const* GetBodyStmt() const { return body_stmt.get(); }
		std::vector<LabelStmt const*> const& GetLabels() const
		{
			return labels;
		}

		FuncType const* GetFuncType() const
		{
			OLA_ASSERT(isa<FuncType>(GetType()));
			return cast<FuncType>(GetType());
		}
		Bool HasDefinition() const
		{
			return body_stmt != nullptr;
		}
		std::string GetMangledName() const;

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) 
		{ 
			switch (decl->GetDeclKind())
			{
			case DeclKind::Function:
			case DeclKind::Method:
			case DeclKind::Constructor:
				return true;
			}
			return false;
		}

	protected:
		UniqueParamVarDeclPtrList param_decls;
		UniqueCompoundStmtPtr body_stmt;
		FuncAttributes func_attributes = FuncAttribute_None;
		std::vector<LabelStmt const*> labels;

	protected:
		FunctionDecl(DeclKind kind, std::string_view name, SourceLocation const& loc) : Decl(kind, name, loc) {}
	};

	enum MethodAttribute : Uint8
	{
		MethodAttribute_None = 0x00,
		MethodAttribute_Const = 0x01,
		MethodAttribute_Virtual = 0x02,
		MethodAttribute_Pure = 0x04,
		MethodAttribute_Final = 0x08,
	};
	using MethodAttributes = Uint8;

	class MethodDecl : public FunctionDecl
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
		Bool HasMethodAttribute(MethodAttribute attr) const
		{
			return HasAttribute(method_attrs, attr);
		}
		Bool IsVirtual() const { return HasMethodAttribute(MethodAttribute_Virtual); }
		Bool IsPure() const { return HasMethodAttribute(MethodAttribute_Pure); }
		Bool IsFinal() const { return HasMethodAttribute(MethodAttribute_Final); }
		Bool IsConst() const { return HasMethodAttribute(MethodAttribute_Const); }

		void SetVTableIndex(Uint32 i) const { vtable_index = i; }
		Uint32 GetVTableIndex() const { return vtable_index; }
		virtual Bool IsConstructor() const { return false; }
		virtual Bool IsMember() const override { return true; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl)
		{
			switch (decl->GetDeclKind())
			{
			case DeclKind::Method:
			case DeclKind::Constructor:
				return true;
			}
			return false;
		}

	private:
		ClassDecl const* parent = nullptr;
		MethodAttributes method_attrs = MethodAttribute_None;
		mutable Uint32 vtable_index = -1;

	protected:
		MethodDecl(DeclKind kind, std::string_view name, SourceLocation const& loc) : FunctionDecl(kind, name, loc) {}

	};

	class ConstructorDecl final : public MethodDecl
	{
	public:
		ConstructorDecl(std::string_view name, SourceLocation const& loc) : MethodDecl(DeclKind::Constructor, name, loc) {}

		virtual Bool IsConstructor() const { return true; }

		virtual void Accept(ASTVisitor&, Uint32) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Constructor; }
	};

	class TagDecl : public Decl
	{
	public:
		virtual Bool IsTag() const override { return true; }

		static Bool ClassOf(Decl const* decl)
		{
			switch (decl->GetDeclKind())
			{
			case DeclKind::Alias:
			case DeclKind::Class:
			case DeclKind::Enum:
				return true;
			}
			return false;
		}

	protected:
		TagDecl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc) : Decl(decl_kind, name, loc) {}
	};

	class EnumDecl final : public TagDecl
	{
	public:
		EnumDecl(std::string_view name, SourceLocation const& loc) : TagDecl(DeclKind::Enum, name, loc) {}

		void SetEnumMembers(UniqueEnumMemberDeclPtrList&& _enum_members)
		{
			enum_members = std::move(_enum_members);
		}
		UniqueEnumMemberDeclPtrList const& GetEnumMembers() const { return enum_members; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Enum; }

	private:
		UniqueEnumMemberDeclPtrList enum_members;
	};

	class EnumMemberDecl final : public Decl
	{
	public:
		EnumMemberDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::EnumMember, name, loc)
		{}

		void SetValue(Sint64 _value)
		{
			value = _value;
		}
		Sint64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::EnumMember; }
	private:
		Sint64 value = 0;
	};

	class AliasDecl final : public TagDecl
	{
	public:
		AliasDecl(std::string_view name, SourceLocation const& loc, QualType const& aliased_type) : TagDecl(DeclKind::Alias, name, loc)
		{
			SetType(aliased_type);
			SetVisibility(DeclVisibility::Public);
		}

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Alias; }
	};

	enum class BuildVTableResult
	{
		Success = 0,
		Error_OverrideFinal = 1
	};
	class ClassDecl final : public TagDecl
	{
	public:
		ClassDecl(std::string_view name, SourceLocation const& loc) : TagDecl(DeclKind::Class, name, loc) {}

		void SetFields(UniqueFieldDeclPtrList&& _fields);
		UniqueFieldDeclPtrList const& GetFields() const { return fields; }
		void SetMethods(UniqueMethodDeclPtrList&& _methods);
		UniqueMethodDeclPtrList const& GetMethods() const { return methods; }
		void SetBaseClass(ClassDecl const* _base_class) 
		{ 
			base_class  = _base_class;
		}
		ClassDecl const* GetBaseClass() const { return base_class; }

		std::vector<ConstructorDecl const*> FindConstructors() const;
		std::vector<MethodDecl const*> FindMethodDecls(std::string_view name) const;
		FieldDecl* FindFieldDecl(std::string_view name) const;

		Uint64 GetFieldCount() const
		{
			return base_class ? base_class->GetFieldCount() + fields.size() : fields.size();
		}
		Bool IsDerivedFrom(ClassDecl const* base) const
		{
			ClassDecl const* curr_base_class = base_class;
			while (curr_base_class)
			{
				if (curr_base_class == base) return true;
				curr_base_class = curr_base_class->base_class;
			}
			return false;
		}
		Bool IsPolymorphic() const
		{
			return polymorphic;
		}
		Bool IsAbstract() const
		{
			return abstract;
		}
		Bool IsFinal() const { return final; }
		void SetFinal(Bool _final) { final = _final; }

		BuildVTableResult BuildVTable(MethodDecl const*& error_decl);
		std::vector<MethodDecl const*> const& GetVTable() const;

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Class; }

	private:
		ClassDecl const* base_class = nullptr;
		UniqueFieldDeclPtrList fields;
		UniqueMethodDeclPtrList methods;
		std::vector<MethodDecl const*> vtable;
		Bool abstract = false;
		Bool polymorphic = false;
		Bool final = false;

	private:
		Bool IsPolymorphicImpl() const;
	};
}

