#pragma once
#include <vector>

namespace ola::ir
{
	class IRType;
	class UnknownType;
	class VoidType;
	class PointerType;
	class IntegerType;
	class FloatType;
	class ArrayType;
	class StructType;
	class FunctionType;

	class IRContext
	{
	public:

		IRContext();
		~IRContext();

		VoidType* GetVoidType()   const { return void_type; }
		FloatType* GetFloatType() const { return float_type; }

		IntegerType* GetIntegerType(uint32 width);
		ArrayType* GetArrayType(IRType* base_type, uint32 array_size);

	private:
		VoidType*	 void_type;
		IntegerType* int1_type;
		IntegerType* int8_type;
		FloatType*   float_type;

		std::vector<ArrayType*>		array_types;
		std::vector<PointerType*>   pointer_types;
		std::vector<FunctionType*>	function_types;
		std::vector<StructType*>	struct_types;
	};
}



