#pragma once
#include <vector>
#include <unordered_map>

namespace ola::ir
{
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

	public:

	private:
		VoidType*	 void_type;
		FloatType*	 float_type;
		std::unordered_map<uint32, IntegerType*> int_types;

		std::vector<ArrayType*>		array_types;
		std::vector<StructType*>	struct_types;
		std::vector<PointerType*>   pointer_types;
		std::vector<FunctionType*>	function_types;
	};
}



