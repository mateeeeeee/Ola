#include "Type.h"
#include "AST.h"
#include "Frontend/Context.h"

namespace ola
{
	Bool QualType::operator==(QualType const& o) const
	{
		return type == o.type && qualifiers == o.qualifiers;
	}

	Bool RefType::IsAssignableFrom(Type const* other) const
	{
		return this == other || type->IsAssignableFrom(other);
	}
	RefType* RefType::Get(Context* ctx, QualType const& type)
	{
		return ctx->GetRefType(type);
	}

	Bool VoidType::IsAssignableFrom(Type const* other) const
	{
		return isa<VoidType>(other); 
	}
	VoidType* VoidType::Get(Context* ctx)
	{
		return ctx->GetVoidType();
	}

	Bool BoolType::IsAssignableFrom(Type const* other) const
	{
		return isoneof<BoolType,IntType,FloatType>(other);
	}
	BoolType* BoolType::Get(Context* ctx)
	{
		return ctx->GetBoolType();
	}

	Bool CharType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<CharType>(referred_type.GetTypePtr());
		}
		else return isa<CharType>(other);
	}
	CharType* CharType::Get(Context* ctx)
	{
		return ctx->GetCharType();
	}

	Bool IntType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<IntType>(referred_type.GetTypePtr());
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}
	IntType* IntType::Get(Context* ctx)
	{
		return ctx->GetIntType();
	}

	Bool FloatType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<FloatType>(referred_type.GetTypePtr());
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}
	FloatType* FloatType::Get(Context* ctx)
	{
		return ctx->GetFloatType();
	}

	Bool ArrayType::IsAssignableFrom(Type const* other) const
	{
		if (!isa<ArrayType>(other)) return false;
		ArrayType const* other_array_type = cast<ArrayType>(other);
		return element_type.GetTypePtr() == other_array_type->element_type.GetTypePtr();
	}
	ArrayType* ArrayType::Get(Context* ctx, QualType const& type, Uint32 array_size)
	{
		return ctx->GetArrayType(type, array_size);
	}

	Bool FuncType::IsAssignableFrom(Type const* other) const
	{
		return false;
	}
	FuncType* FuncType::Get(Context* ctx, QualType const& return_type, std::vector<QualType> const& param_types)
	{
		return ctx->GetFuncType(return_type, param_types);
	}

	ClassType::ClassType(ClassDecl const* class_decl) : Type{ TypeKind::Class, 0, 0 }, class_decl(class_decl)
	{
		if (!class_decl) return;

		auto AlignTo = []<typename T>(T n, T align) { return (n + align - 1) / align * align; };
		Uint32 offset = 0;

		if (class_decl->IsPolymorphic()) offset += 8;

		ClassDecl const* curr_base_class_decl = class_decl->GetBaseClass();
		while (curr_base_class_decl)
		{
			for (auto const& field : curr_base_class_decl->GetFields())
			{
				QualType const& mem_type = field->GetType();
				offset = AlignTo(offset, mem_type->GetAlign());
				offset += mem_type->GetSize();
				if (GetAlign() < mem_type->GetAlign()) SetAlign(mem_type->GetAlign());
			}
			curr_base_class_decl = curr_base_class_decl->GetBaseClass();
		}
		for (auto const& field : class_decl->GetFields())
		{
			QualType const& mem_type = field->GetType();
			offset = AlignTo(offset, mem_type->GetAlign());
			offset += mem_type->GetSize();
			if (GetAlign() < mem_type->GetAlign()) SetAlign(mem_type->GetAlign());
		}
		if (offset == 0) offset = 1;
		if (GetAlign()) offset = AlignTo(offset, GetAlign());
		SetSize(offset);
	}
	Bool ClassType::IsAssignableFrom(Type const* other) const
	{
		if (this != other)
		{
			if (RefType const* ref_other = dyn_cast<RefType>(other))
			{
				if (!isa<ClassType>(ref_other->GetReferredType().GetTypePtr())) return false;
				QualType const& referred_type = ref_other->GetReferredType();
				ClassType const* referred_class_type = cast<ClassType>(referred_type.GetTypePtr());
				return IsAssignableFrom(referred_class_type);
			}
			else if (ClassType const* class_other = dyn_cast<ClassType>(other))
			{
				return class_other->GetClassDecl()->IsDerivedFrom(class_decl);
			}
			else return false;
		}
		return true;
	}
	ClassType* ClassType::Get(Context* ctx, ClassDecl const* class_decl)
	{
		return ctx->GetClassType(class_decl);
	}
}

