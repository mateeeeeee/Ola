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
		if (!isa<RefType>(other)) return false;
		RefType const& other_ref_type = type_cast<RefType>(other);
		return type->IsSameAs(other_ref_type.GetReferredType());
	}

	bool VoidType::IsAssignableFrom(Type const& other) const
	{
		return isa<VoidType>(other); 
	}

	bool BoolType::IsAssignableFrom(Type const& other) const
	{
		return isoneof<BoolType,IntType,FloatType>(other);
	}

	bool CharType::IsAssignableFrom(Type const& other) const
	{
		if (RefType const* ref_other = dyn_type_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<CharType>(referred_type); 
		}
		else return isa<CharType>(other);
	}

	bool IntType::IsAssignableFrom(Type const& other) const
	{
		if (RefType const* ref_other = dyn_type_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<IntType>(referred_type);
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}

	bool FloatType::IsAssignableFrom(Type const& other) const
	{
		if (RefType const* ref_other = dyn_type_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || referred_type->Is(TypeKind::Float);
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}

	bool ArrayType::IsAssignableFrom(Type const& other) const
	{
		return IsSameAs(other);
	}
	bool ArrayType::IsSameAs(Type const& other) const
	{
		if (!isa<ArrayType>(other)) return false;
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
	bool ClassType::IsAssignableFrom(Type const& other) const
	{
		if (!IsSameAs(other))
		{
			if (RefType const* ref_other = dyn_type_cast<RefType>(other))
			{
				if (!isa<ClassType>(ref_other->GetReferredType())) return false;
				QualType const& referred_type = ref_other->GetReferredType();
				ClassType const& referred_class_type = type_cast<ClassType>(referred_type);
				return IsAssignableFrom(referred_class_type);
			}
			else if (ClassType const* class_other = dyn_type_cast<ClassType>(other))
			{
				return class_other->GetClassDecl()->IsDerivedFrom(class_decl);
			}
			else return false;
		}
		return true;
	}

	bool ClassType::IsSameAs(Type const& other) const
	{
		if (!isa<ClassType>(other)) return false;
		ClassType const& class_type = type_cast<ClassType>(other);
		return class_decl == class_type.GetClassDecl();
	}

}

