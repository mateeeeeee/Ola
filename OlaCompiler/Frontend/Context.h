#pragma once
#include <vector>

namespace ola
{
	class ArrayType;
	class ClassType;
	class RefType;
	class FuncType;
	class VoidType;
	class BoolType;
	class CharType;
	class IntType;
	class FloatType;

	class Context
	{
	public:

		Context();
		~Context();

		VoidType* void_type;
		BoolType* bool_type;
		CharType* char_type;
		IntType*  int_type;
		FloatType* float_type;

		std::vector<ArrayType*> array_types;
		std::vector<ClassType*> class_types;
		std::vector<RefType*>   ref_types;
		std::vector<FuncType*>  function_types;
	};
}