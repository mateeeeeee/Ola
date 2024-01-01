#include "Type.h"
#include "AST.h"
#include "Frontend/Context.h"

namespace ola
{
	bool QualType::operator==(QualType const& o) const
	{
		return type->IsEqualTo(o.type) && qualifiers == o.qualifiers;
	}


	bool RefType::IsAssignableFrom(Type const* other) const
	{
		return type->IsAssignableFrom(other) || IsEqualTo(other);
	}
	bool RefType::IsEqualTo(Type const* other) const
	{
		if (!isa<RefType>(other)) return false;
		RefType const* other_ref_type = cast<RefType>(other);
		return type->IsEqualTo(other_ref_type->GetReferredType());
	}
	RefType* RefType::Get(Context* ctx, QualType const& type)
	{
		for (auto const& ref_type : ctx->ref_types)
		{
			if (ref_type->GetReferredType()==(type)) return ref_type;
		}
		ctx->ref_types.push_back(new(ctx) RefType(type));
		return ctx->ref_types.back();
	}

	bool VoidType::IsAssignableFrom(Type const* other) const
	{
		return isa<VoidType>(other); 
	}

	VoidType* VoidType::Get(Context* ctx)
	{
		return ctx->void_type;
	}

	bool BoolType::IsAssignableFrom(Type const* other) const
	{
		return isoneof<BoolType,IntType,FloatType>(other);
	}

	BoolType* BoolType::Get(Context* ctx)
	{
		return ctx->bool_type;
	}

	bool CharType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<CharType>(referred_type); 
		}
		else return isa<CharType>(other);
	}

	CharType* CharType::Get(Context* ctx)
	{
		return ctx->char_type;
	}

	bool IntType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<IntType>(referred_type);
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}

	IntType* IntType::Get(Context* ctx)
	{
		return ctx->int_type;
	}

	bool FloatType::IsAssignableFrom(Type const* other) const
	{
		if (RefType const* ref_other = dyn_cast<RefType>(other))
		{
			QualType const& referred_type = ref_other->GetReferredType();
			return referred_type.IsNull() || isa<FloatType>(referred_type);
		}
		else return isoneof<BoolType, IntType, FloatType>(other);
	}

	FloatType* FloatType::Get(Context* ctx)
	{
		return ctx->float_type;
	}

	bool ArrayType::IsAssignableFrom(Type const* other) const
	{
		if (!isa<ArrayType>(other)) return false;
		ArrayType const* other_array_type = cast<ArrayType>(other);
		return base_type->IsEqualTo(other_array_type->base_type);
	}
	bool ArrayType::IsEqualTo(Type const* other) const
	{
		if (!isa<ArrayType>(other)) return false;
		ArrayType const* other_array_type = cast<ArrayType>(other);
		return base_type->IsEqualTo(other_array_type->base_type) && array_size == other_array_type->array_size;
	}

	ArrayType* ArrayType::Get(Context* ctx, QualType const& type, uint32 array_size)
	{
		for (auto const& array_type : ctx->array_types)
		{
			if (array_type->GetBaseType() == type && array_type->GetArraySize() == array_size) return array_type;
		}
		ArrayType* new_type = new(ctx) ArrayType(type, array_size);
		ctx->array_types.push_back(new_type);
		return new_type;
	}

	bool FuncType::IsAssignableFrom(Type const* other) const
	{
		return false;
	}

	FuncType* FuncType::Get(Context* ctx, QualType const& return_type, std::vector<QualType> const& param_types /*= {}*/)
	{
		for (auto const& function_type : ctx->function_types)
		{
			if (function_type->GetReturnType() != return_type) continue;
			if (function_type->GetParamCount() != param_types.size()) continue;
			uint64 param_count = function_type->GetParamCount();
			bool incompatible = false;
			for (uint64 i = 0; i < param_count; ++i)
			{
				if (function_type->GetParamType(i) != param_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if(!incompatible) return function_type;
		}
		ctx->function_types.push_back(new(ctx) FuncType(return_type, param_types));
		return ctx->function_types.back();
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
	bool ClassType::IsAssignableFrom(Type const* other) const
	{
		if (!IsEqualTo(other))
		{
			if (RefType const* ref_other = dyn_cast<RefType>(other))
			{
				if (!isa<ClassType>(ref_other->GetReferredType())) return false;
				QualType const& referred_type = ref_other->GetReferredType();
				ClassType const* referred_class_type = cast<ClassType>(referred_type);
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

	bool ClassType::IsEqualTo(Type const* other) const
	{
		if (!isa<ClassType>(other)) return false;
		ClassType const* class_type = cast<ClassType>(other);
		return class_decl == class_type->GetClassDecl();
	}

	ClassType* ClassType::Get(Context* ctx, ClassDecl const* class_decl)
	{
		for (auto const& class_type : ctx->class_types)
		{
			if (class_type->GetClassDecl() == class_decl) return class_type;
		}
		ctx->class_types.push_back(new(ctx) ClassType(class_decl));
		return ctx->class_types.back();
	}

}

