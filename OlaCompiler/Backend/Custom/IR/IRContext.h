#pragma once
#include <vector>
#include <unordered_map>
#include <string>

namespace ola
{
	class IRType;
	class UnknownType;
	class IRVoidType;
	class IRPtrType;
	class IRIntType;
	class IRFloatType;
	class IRArrayType;
	class IRStructType;
	class IRFuncType;
	class IRLabelType;

	class ConstantString;
	class ConstantInt;
	class ConstantFloat;

	class IRContext
	{
	public:

		IRContext();
		~IRContext();

		IRVoidType* GetVoidType()   const { return void_type; }
		IRFloatType* GetFloatType() const { return float_type; }
		IRLabelType* GetLabelType() const { return label_type; }

		IRIntType*	GetIntegerType(uint32 width);
		IRPtrType*	GetPointerType(IRType* pointee_type);
		IRArrayType*		GetArrayType(IRType* base_type, uint32 array_size);
		IRFuncType*   GetFunctionType(IRType* ret_type, std::vector<IRType*> const& param_types);
		IRStructType*     GetStructType(std::string_view name, std::vector<IRType*> const& member_types);

		ConstantString* GetString(std::string_view str);
		ConstantInt* GetInt64(int64 value);
		ConstantInt* GetInt8(int8 value);
		ConstantInt* GetTrueValue()  const { return true_value; }
		ConstantInt* GetFalseValue() const { return false_value; }

	private:
		IRVoidType*	 void_type;
		IRIntType* int1_type;
		IRIntType* int8_type;
		IRFloatType*   float_type;
		IRLabelType*   label_type;

		std::vector<IRArrayType*>		array_types;
		std::vector<IRPtrType*>   pointer_types;
		std::vector<IRFuncType*>	function_types;
		std::vector<IRStructType*>	struct_types;

		ConstantInt* true_value;
		ConstantInt* false_value;
		std::unordered_map<std::string_view, ConstantString*> constant_strings;
		std::unordered_map<int64, ConstantInt*> constant_ints64;
		std::unordered_map<int8, ConstantInt*> constant_ints8;
		
	};
}



