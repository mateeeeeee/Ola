#include "Context.h"
#include "Frontend/AST/Type.h"

namespace ola
{
	Context::Context()
	{
		void_type = new VoidType();
		bool_type = new BoolType();
		char_type = new CharType();
		int_type = new IntType();
		float_type = new FloatType();
	}

	Context::~Context()
	{
		for (ArrayType* array_type : array_types)		delete array_type;
		for (ClassType* class_type : class_types)		delete class_type;
		for (RefType* ref_type : ref_types)				delete ref_type;
		for (FuncType* function_type : function_types)	delete function_type;

		delete float_type;
		delete int_type;
		delete char_type;
		delete bool_type;
		delete void_type;
	}

}

