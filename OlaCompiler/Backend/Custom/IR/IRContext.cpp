#include "IRContext.h"
#include "IRType.h"
#include "Constant.h"

namespace ola
{

	IRContext::IRContext()
	{
		void_type = new(this) IRVoidType(*this);
		int1_type = new(this) IRIntType(*this, 1);
		int8_type = new(this) IRIntType(*this, 8);
		float_type = new(this) IRFloatType(*this);
		label_type = new(this) IRLabelType(*this);

		true_value = new ConstantInt(int1_type, 1);
		false_value = new ConstantInt(int1_type, 0);
		zero_float = new ConstantFloat(float_type, 0.0);
	}

	IRContext::~IRContext()
	{
		for (IRArrayType* array_type : array_types)			delete array_type;
		for (IRStructType* struct_type : struct_types)		delete struct_type;
		for (IRPtrType* ref_type : pointer_types)			delete ref_type;
		for (IRFuncType* function_type : function_types)	delete function_type;

		for (auto& [_, v] : constant_strings) delete v;
		for (auto& [_, v] : constant_ints64) delete v;
		for (auto& [_, v] : constant_ints8) delete v;

		delete zero_float;
		delete false_value;
		delete true_value;

		delete label_type;
		delete float_type;
		delete int1_type;
		delete int8_type;
		delete void_type;
	}

	IRIntType* IRContext::GetIntegerType(Uint32 width)
	{
		switch (width)
		{
		case 1: return int1_type;
		case 8: return int8_type;
		default:
			OLA_ASSERT_MSG(false, "Invalid integer type width!");
		}
		return nullptr;
	}

	IRPtrType* IRContext::GetPointerType(IRType* pointee_type)
	{
		for (auto const& pointer_type : pointer_types)
		{
			if (pointer_type->GetPointeeType() == pointee_type) return pointer_type;
		}
		IRPtrType* new_type = new(this) IRPtrType(*this, pointee_type);
		pointer_types.push_back(new_type);
		return new_type;
	}

	IRArrayType* IRContext::GetArrayType(IRType* base_type, Uint32 array_size)
	{
		for (auto const& array_type : array_types)
		{
			if (array_type->GetElementType() == base_type && array_type->GetArraySize() == array_size) return array_type;
		}
		IRArrayType* new_type = new(this) IRArrayType(*this, base_type, array_size);
		array_types.push_back(new_type);
		return new_type;
	}

	IRFuncType* IRContext::GetFunctionType(IRType* ret_type, std::vector<IRType*> const& param_types)
	{
		for (auto const& function_type : function_types)
		{
			if (function_type->GetReturnType() != ret_type) continue;
			if (function_type->GetParamCount() != param_types.size()) continue;
			Uint64 const param_count = function_type->GetParamCount();
			bool incompatible = false;
			for (Uint64 i = 0; i < param_count; ++i)
			{
				if (function_type->GetParamType(i) != param_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if (!incompatible) return function_type;
		}
		function_types.push_back(new(this) IRFuncType(*this, ret_type, param_types));
		return function_types.back();
	}

	IRStructType* IRContext::GetStructType(std::string_view name, std::vector<IRType*> const& member_types)
	{
		for (auto const& struct_type : struct_types)
		{
			if (struct_type->GetName() != name) continue;
			if (struct_type->GetMemberCount() != member_types.size()) continue;
			Uint64 const member_count = struct_type->GetMemberCount();
			bool incompatible = false;
			for (Uint64 i = 0; i < member_count; ++i)
			{
				if (struct_type->GetMemberType(i) != member_types[i])
				{
					incompatible = true;
					break;
				}
			}
			if (!incompatible) return struct_type;
		}
		struct_types.push_back(new(this) IRStructType(*this, name, member_types));
		return struct_types.back();
	}

	ConstantString* IRContext::GetString(std::string_view str)
	{
		if (constant_strings.contains(str)) return constant_strings[str];
		constant_strings[str] = new ConstantString(*this, str);
		return constant_strings[str];
	}

	ConstantInt* IRContext::GetInt64(Sint64 value)
	{
		if (constant_ints64.contains(value)) return constant_ints64[value];
		constant_ints64[value] = new ConstantInt(int8_type, value);
		return constant_ints64[value];
	}

	ConstantInt* IRContext::GetInt8(Sint8 value)
	{
		if (constant_ints8.contains(value)) return constant_ints8[value];
		constant_ints8[value] = new ConstantInt(int1_type, value);
		return constant_ints8[value];
	}


	ConstantInt* IRContext::GetInt(IRType* type, Sint64 value)
	{
		OLA_ASSERT(type->IsInteger());
		IRIntType* int_type = cast<IRIntType>(type);
		if (int_type->GetWidth() == 8) return GetInt64(value);
		else return GetInt8(value);
	}

	ConstantFloat* IRContext::GetFloat(double value)
	{
		if (constant_floats.contains(value)) return constant_floats[value];
		constant_floats[value] = new ConstantFloat(float_type, value);
		return constant_floats[value];
	}

	ConstantArray* IRContext::GetNullArray(IRArrayType* array_type)
	{
		if (!constant_null_arrays.contains(array_type))
		{
			IRType* element_type = array_type->GetElementType();
			Uint32 array_size = array_type->GetArraySize();

			Constant* element_null_value = Constant::GetNullValue(element_type);
			std::vector<Constant*> elements(array_size, element_null_value);

			constant_null_arrays[array_type] = new ConstantArray(array_type, elements);
		}
		return constant_null_arrays[array_type];
	}

	Constant* IRContext::GetNullValue(IRType* type)
	{
		if (isa<IRIntType>(type))
		{
			IRIntType* int_type = cast<IRIntType>(type);
			if (int_type->GetWidth() == 8) return GetInt64(0);
			else return GetInt8(0);
		}
		else if (isa<IRFloatType>(type))
		{
			return GetZeroFloat();
		}
		else if (isa<IRArrayType>(type))
		{
			return GetNullArray(cast<IRArrayType>(type));
		}
		return nullptr;
	}

}

