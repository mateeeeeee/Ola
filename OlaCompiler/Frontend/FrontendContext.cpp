#include "FrontendContext.h"
#include "Frontend/AST/Type.h"

namespace ola
{
	FrontendContext::FrontendContext()
	{
		void_type	= new(this) VoidType();
		bool_type	= new(this) BoolType();
		char_type	= new(this) CharType();
		int_type	= new(this) IntType();
		float_type	= new(this) FloatType();
	}

	FrontendContext::~FrontendContext()
	{
		for (ArrayType* array_type : array_types) 
		{
			delete array_type;
		}
		for (ClassType* class_type : class_types)
		{
			delete class_type;
		}
		for (RefType* ref_type : ref_types)
		{
			delete ref_type;
		}
		for (FuncType* function_type : function_types)
		{
			delete function_type;
		}

		delete float_type;
		delete int_type;
		delete char_type;
		delete bool_type;
		delete void_type;
	}

	ArrayType* FrontendContext::GetArrayType(QualType const& type, Uint32 array_size)
	{
		for (auto const& array_type : array_types)
		{
			if (array_type->GetElementType() == type && array_type->GetArraySize() == array_size)
			{
				return array_type;
			}
		}
		ArrayType* new_type = new(this) ArrayType(type, array_size);
		array_types.push_back(new_type);
		return new_type;
	}

	RefType* FrontendContext::GetRefType(QualType const& type)
	{
		for (auto const& ref_type : ref_types)
		{
			if (ref_type->GetReferredType() == (type))
			{
				return ref_type;
			}
		}
		ref_types.push_back(new(this) RefType(type));
		return ref_types.back();
	}

	FuncType* FrontendContext::GetFuncType(QualType const& return_type, std::vector<QualType> const& param_types)
	{
		for (auto const& function_type : function_types)
		{
			if (function_type->GetReturnType() != return_type)
			{
				continue;
			}

			if (function_type->GetParamCount() != param_types.size())
			{
				continue;
			}

			Uint64 const param_count = function_type->GetParamCount();
			Bool incompatible = false;
			for (Uint64 i = 0; i < param_count; ++i)
			{
				if (function_type->GetParamType(i) != param_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if (!incompatible)
			{
				return function_type;
			}
		}
		function_types.push_back(new(this) FuncType(return_type, param_types));
		return function_types.back();
	}

	ClassType* FrontendContext::GetClassType(ClassDecl const* class_decl)
	{
		for (auto const& class_type : class_types)
		{
			if (class_type->GetClassDecl() == class_decl)
			{
				return class_type;
			}
		}
		class_types.push_back(new(this) ClassType(class_decl));
		return class_types.back();
	}

}

