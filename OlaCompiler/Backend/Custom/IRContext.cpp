#include "IRContext.h"
#include "IRType.h"

namespace ola::ir
{

	IRContext::IRContext()
	{
		void_type = new(this) VoidType();
		int1_type = new(this) IntegerType(1);
		int8_type = new(this) IntegerType(8);
		float_type = new(this) FloatType();
	}

	IRContext::~IRContext()
	{
		for (ArrayType* array_type : array_types)			delete array_type;
		for (StructType* struct_type : struct_types)		delete struct_type;
		for (PointerType* ref_type : pointer_types)			delete ref_type;
		for (FunctionType* function_type : function_types)	delete function_type;

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

}

