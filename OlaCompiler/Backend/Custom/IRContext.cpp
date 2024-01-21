#include "IRContext.h"
#include "IRType.h"

namespace ola
{

	IRContext::IRContext()
	{
		void_type = new(this) VoidType();
		int1_type = new(this) IntegerType(1);
		int8_type = new(this) IntegerType(8);
		float_type = new(this) FloatType();
		label_type = new(this) LabelType;
	}

	IRContext::~IRContext()
	{
		for (ArrayType* array_type : array_types)			delete array_type;
		for (StructType* struct_type : struct_types)		delete struct_type;
		for (PointerType* ref_type : pointer_types)			delete ref_type;
		for (FunctionType* function_type : function_types)	delete function_type;

		delete label_type;
		delete float_type;
		delete int1_type;
		delete int8_type;
		delete void_type;
	}

	IntegerType* IRContext::GetIntegerType(uint32 width)
	{
		switch (width)
		{
		case 1:
		case 8:
		default:
			OLA_ASSERT_MSG(false, "Invalid integer type width!");
		}
		return nullptr;
	}

	PointerType* IRContext::GetPointerType(IRType* pointee_type)
	{
		for (auto const& pointer_type : pointer_types)
		{
			if (pointer_type->GetPointeeType() == pointee_type) return pointer_type;
		}
		PointerType* new_type = new(this) PointerType(pointee_type);
		pointer_types.push_back(new_type);
		return new_type;
	}

	ArrayType* IRContext::GetArrayType(IRType* base_type, uint32 array_size)
	{
		for (auto const& array_type : array_types)
		{
			if (array_type->GetBaseType() == base_type && array_type->GetArraySize() == array_size) return array_type;
		}
		ArrayType* new_type = new(this) ArrayType(base_type, array_size);
		array_types.push_back(new_type);
		return new_type;
	}

	FunctionType* IRContext::GetFunctionType(IRType* ret_type, std::vector<IRType*> const& param_types)
	{
		for (auto const& function_type : function_types)
		{
			if (function_type->GetReturnType() != ret_type) continue;
			if (function_type->GetParamCount() != param_types.size()) continue;
			uint64 const param_count = function_type->GetParamCount();
			bool incompatible = false;
			for (uint64 i = 0; i < param_count; ++i)
			{
				if (function_type->GetParamType(i) != param_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if (!incompatible) return function_type;
		}
		function_types.push_back(new(this) FunctionType(ret_type, param_types));
		return function_types.back();
	}

	StructType* IRContext::GetStructType(std::string_view name, std::vector<IRType*> const& member_types)
	{
		for (auto const& struct_type : struct_types)
		{
			if (struct_type->GetName() != name) continue;
			if (struct_type->GetMemberCount() != member_types.size()) continue;
			uint64 const member_count = struct_type->GetMemberCount();
			bool incompatible = false;
			for (uint64 i = 0; i < member_count; ++i)
			{
				if (struct_type->GetMemberType(i) != member_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if (!incompatible) return struct_type;
		}
		struct_types.push_back(new(this) StructType(name, member_types));
		return struct_types.back();
	}

}

