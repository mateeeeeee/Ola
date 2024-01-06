#pragma once
#include "ASTNode.h"
#include "ASTAliases.h"
#include "Stmt.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"
#include "Compiler/RTTI.h"

namespace ola
{
	enum class DeclKind : uint8
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
		bool IsPublic()  const { return  visibility == DeclVisibility::Public; }
		bool IsPrivate() const { return visibility == DeclVisibility::Private; }
		bool IsExtern()  const { return  visibility == DeclVisibility::Extern; }

		virtual bool IsTag() const { return false; }
		virtual bool IsMember() const { return false; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return true; }

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

		static bool ClassOf(Decl const* decl) 
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

	inline bool HasAttribute(uint8 attrs, uint8 attr)
	{
		return (attrs & attr) == attr;
	}

	enum FuncAttribute : uint8
	{
		FuncAttribute_None = 0x00,
		FuncAttribute_NoInline = 0x01,
		FuncAttribute_Inline = 0x02,
		FuncAttribute_NoMangling = 0x04
	};
	using FuncAttributes = uint8;

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
		bool HasFuncAttribute(FuncAttribute attr) const
		{
			return HasAttribute(func_attributes, attr);
		}
		bool IsInline()   const { return HasFuncAttribute(FuncAttribute_Inline); }
		bool IsNoInline() const { return HasFuncAttribute(FuncAttribute_NoInline); }
		bool NoMangling() const { return HasFuncAttribute(FuncAttribute_NoMangling); }

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
		bool HasDefinition() const
		{
			return body_stmt != nullptr;
		}
		std::string GetMangledName() const;

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) 
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

	enum MethodAttribute : uint8
	{
		MethodAttribute_None = 0x00,
		MethodAttribute_Const = 0x01,
		MethodAttribute_Virtual = 0x02,
		MethodAttribute_Pure = 0x04,
		MethodAttribute_Final = 0x08,
	};
	using MethodAttributes = uint8;

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
		bool HasMethodAttribute(MethodAttribute attr) const
		{
			return HasAttribute(method_attrs, attr);
		}
		bool IsVirtual() const { return HasMethodAttribute(MethodAttribute_Virtual); }
		bool IsPure() const { return HasMethodAttribute(MethodAttribute_Pure); }
		bool IsFinal() const { return HasMethodAttribute(MethodAttribute_Final); }
		bool IsConst() const { return HasMethodAttribute(MethodAttribute_Const); }

		void SetVTableIndex(uint32 i) const { vtable_index = i; }
		uint32 GetVTableIndex() const { return vtable_index; }
		virtual bool IsConstructor() const { return false; }
		virtual bool IsMember() const override { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl)
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
		mutable uint32 vtable_index = -1;

	protected:
		MethodDecl(DeclKind kind, std::string_view name, SourceLocation const& loc) : FunctionDecl(kind, name, loc) {}

	};

	class ConstructorDecl final : public MethodDecl
	{
	public:
		ConstructorDecl(std::string_view name, SourceLocation const& loc) : MethodDecl(DeclKind::Constructor, name, loc) {}

		virtual bool IsConstructor() const { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Constructor; }
	};

	class TagDecl : public Decl
	{
	public:
		virtual bool IsTag() const override { return true; }

		static bool ClassOf(Decl const* decl)
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Enum; }

	private:
		UniqueEnumMemberDeclPtrList enum_members;
	};

	class EnumMemberDecl final : public Decl
	{
	public:
		EnumMemberDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::EnumMember, name, loc)
		{}

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

	class AliasDecl final : public TagDecl
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

		uint64 GetFieldCount() const
		{
			return base_class ? base_class->GetFieldCount() + fields.size() : fields.size();
		}
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
			return polymorphic;
		}
		bool IsAbstract() const
		{
			return abstract;
		}
		bool IsFinal() const { return final; }
		void SetFinal(bool _final) { final = _final; }

		BuildVTableResult BuildVTable(MethodDecl const*& error_decl);
		std::vector<MethodDecl const*> const& GetVTable() const;

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;


		static bool ClassOf(Decl const* decl) { return decl->GetDeclKind() == DeclKind::Class; }

	private:
		ClassDecl const* base_class = nullptr;
		UniqueFieldDeclPtrList fields;
		UniqueMethodDeclPtrList methods;
		std::vector<MethodDecl const*> vtable;
		bool abstract = false;
		bool polymorphic = false;
		bool final = false;

	private:
		bool IsPolymorphicImpl() const;
	};
}

