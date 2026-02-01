#include "InterpreterValue.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{
	InterpreterValue InterpreterValue::Bitcast(IRType* to_type) const
	{
		if (to_type->IsFloat() && kind == Kind::Int)
		{
			Float64 result;
			std::memcpy(&result, &int_val, sizeof(Float64));
			return MakeFloat(result);
		}
		else if (to_type->IsInteger() && kind == Kind::Float)
		{
			Int64 result;
			std::memcpy(&result, &float_val, sizeof(Int64));
			return MakeInt(result);
		}
		else if (to_type->IsPointer())
		{
			return *this;
		}
		return *this;
	}
}
