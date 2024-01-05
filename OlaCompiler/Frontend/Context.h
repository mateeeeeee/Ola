#pragma once
#include <vector>

namespace ola
{
	class Type;
	class QualType;
	class ArrayType;
	class ClassType;
	class RefType;
	class FuncType;
	class VoidType;
	class BoolType;
	class CharType;
	class IntType;
	class FloatType;
	class ClassDecl;

	class Context
	{
	public:

		Context();
		~Context();

		VoidType*  GetVoidType()  const  { return void_type;  }
		BoolType*  GetBoolType()  const  { return bool_type;  }
		CharType*  GetCharType()  const  { return char_type;  }
		IntType*   GetIntType()   const  { return int_type;   }
		FloatType* GetFloatType() const  { return float_type; }

		ArrayType* GetArrayType(QualType const& type, uint32 array_size);
		RefType* GetRefType(QualType const& type);
		FuncType* GetFuncType(QualType const& return_type, std::vector<QualType> const& param_types);
		ClassType* GetClassType(ClassDecl const* class_decl);

	private:

		VoidType* void_type;
		BoolType* bool_type;
		CharType* char_type;
		IntType*   int_type;
		FloatType* float_type;

		std::vector<ArrayType*> array_types;
		std::vector<ClassType*> class_types;
		std::vector<RefType*>   ref_types;
		std::vector<FuncType*>  function_types;
	};
}