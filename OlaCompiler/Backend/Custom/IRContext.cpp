#include "IRContext.h"
#include "IRType.h"

namespace ola::ir
{

	IRContext::IRContext()
	{
		void_type = new(this) VoidType();
		int_types[1] = new(this) IntegerType(1);
		int_types[8] = new(this) IntegerType(8);
		float_type = new(this) FloatType();
	}

	IRContext::~IRContext()
	{
		for (ArrayType* array_type : array_types)			delete array_type;
		for (StructType* struct_type : struct_types)		delete struct_type;
		for (PointerType* ref_type : pointer_types)			delete ref_type;
		for (FunctionType* function_type : function_types)	delete function_type;

		delete float_type;
		for (auto [width, int_type] : int_types)
		{
			delete int_type;
		}
		delete void_type;
	}

}

