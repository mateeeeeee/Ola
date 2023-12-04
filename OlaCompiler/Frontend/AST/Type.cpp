#include "Type.h"
#include "AST.h"

namespace ola
{

	bool RefType::IsAssignableFrom(Type const& other) const
	{
		return type->IsAssignableFrom(other) || IsSameAs(other);
	}
	bool RefType::IsSameAs(Type const& other) const
	{
		if (other.IsNot(TypeKind::Ref)) return false;
		RefType const& other_ref_type = type_cast<RefType>(other);
		return type->IsSameAs(other_ref_type.GetReferredType());
	}

	bool VoidType::IsAssignableFrom(Type const& other) const
	{
		return other.Is(TypeKind::Void);
	}

	bool BoolType::IsAssignableFrom(Type const& other) const
	{
		return other.IsOneOf(TypeKind::Bool, TypeKind::Int, TypeKind::Float);
	}

	bool CharType::IsAssignableFrom(Type const& other) const
	{
		if (other.Is(TypeKind::Ref))
		{
			RefType const& other_ref = type_cast<RefType>(other);
			QualType const& referred_type = other_ref.GetReferredType();
			return referred_type.IsNull() || referred_type->Is(TypeKind::Char);
		}
		else return other.Is(TypeKind::Char);
	}

	bool IntType::IsAssignableFrom(Type const& other) const
	{
		if (other.Is(TypeKind::Ref))
		{
			RefType const& other_ref = type_cast<RefType>(other);
			QualType const& referred_type = other_ref.GetReferredType();
			return referred_type.IsNull() || referred_type->Is(TypeKind::Int);
		}
		else return other.IsOneOf(TypeKind::Bool, TypeKind::Int, TypeKind::Float);
	}

	bool FloatType::IsAssignableFrom(Type const& other) const
	{
		if (other.Is(TypeKind::Ref))
		{
			RefType const& other_ref = type_cast<RefType>(other);
			QualType const& referred_type = other_ref.GetReferredType();
			return referred_type.IsNull() || referred_type->Is(TypeKind::Float);
		}
		else
			return other.IsOneOf(TypeKind::Bool, TypeKind::Float, TypeKind::Int);
	}

	bool ArrayType::IsAssignableFrom(Type const& other) const
	{
		if (other.IsNot(TypeKind::Array)) return false;
		ArrayType const& other_array_type = type_cast<ArrayType>(other);
		return base_type->IsAssignableFrom(other_array_type.base_type);
	}
	bool ArrayType::IsSameAs(Type const& other) const
	{
		if (other.IsNot(TypeKind::Array)) return false;
		ArrayType const& other_array_type = type_cast<ArrayType>(other);
		return base_type->IsSameAs(other_array_type.base_type);
	}

	bool FuncType::IsAssignableFrom(Type const& other) const
	{
		return false;
	}

	ClassType::ClassType(ClassDecl const* class_decl) : Type{ TypeKind::Class, 0, 0 }, class_decl(class_decl)
	{
		if (!class_decl) return;

		auto AlignTo = []<typename T>(T n, T align) { return (n + align - 1) / align * align; };
		uint32 offset = 0;
		for (auto const& field : class_decl->GetFields())
		{
			QualType const& mem_type = field->GetType();
			offset = AlignTo(offset, mem_type->GetAlign());
			offset += mem_type->GetSize();
			if (GetAlign() < mem_type->GetAlign()) SetAlign(mem_type->GetAlign());
		}
		SetSize(AlignTo(offset, GetAlign()));
	}
	bool ClassType::IsAssignableFrom(Type const& other) const
	{
		if (!IsSameAs(other))
		{
			if (other.Is(TypeKind::Ref))
			{
				RefType const& ref_other = type_cast<RefType>(other);
				if (!ref_other.GetReferredType()->Is(TypeKind::Class)) return false;
				QualType const& referred_type = ref_other.GetReferredType();
				ClassType const& referred_class_type = type_cast<ClassType>(referred_type);
				return IsSameAs(referred_class_type);
			}
			else return false;
		}
		return true;
	}

	bool ClassType::IsSameAs(Type const& other) const
	{
		if (other.GetKind() != TypeKind::Class) return false;
		ClassType const& class_type = type_cast<ClassType>(other);
		return class_decl == class_type.GetClassDecl();
	}

}

