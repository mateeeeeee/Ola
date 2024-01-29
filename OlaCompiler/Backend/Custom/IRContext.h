#pragma once
#include <vector>
#include <unordered_map>
#include <string>

namespace ola
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
	class LabelType;

	class ConstantString;
	class ConstantInt;
	class ConstantFloat;

	class IRContext
	{
	public:

		IRContext();
		~IRContext();

		VoidType* GetVoidType()   const { return void_type; }
		FloatType* GetFloatType() const { return float_type; }
		LabelType* GetLabelType() const { return label_type; }

		IntegerType*	GetIntegerType(uint32 width);
		PointerType*	GetPointerType(IRType* pointee_type);
		ArrayType*		GetArrayType(IRType* base_type, uint32 array_size);
		FunctionType*   GetFunctionType(IRType* ret_type, std::vector<IRType*> const& param_types);
		StructType*     GetStructType(std::string_view name, std::vector<IRType*> const& member_types);

		ConstantString* GetConstantString(std::string_view str);
		ConstantInt* GetConstantInt64(int64 value);
		ConstantInt* GetConstantInt8(int8 value);
		ConstantInt* GetTrueValue()  const { return true_value; }
		ConstantInt* GetFalseValue() const { return false_value; }

	private:
		VoidType*	 void_type;
		IntegerType* int1_type;
		IntegerType* int8_type;
		FloatType*   float_type;
		LabelType*   label_type;

		std::vector<ArrayType*>		array_types;
		std::vector<PointerType*>   pointer_types;
		std::vector<FunctionType*>	function_types;
		std::vector<StructType*>	struct_types;

		ConstantInt* true_value;
		ConstantInt* false_value;
		std::unordered_map<std::string_view, ConstantString*> constant_strings;
		std::unordered_map<int64, ConstantInt*> constant_ints64;
		std::unordered_map<int8, ConstantInt*> constant_ints8;
		
	};
}



