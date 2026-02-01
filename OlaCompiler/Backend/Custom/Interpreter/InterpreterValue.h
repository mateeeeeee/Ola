#pragma once
#include <cstring>

namespace ola
{
	class IRType;

	struct InterpreterValue
	{
		enum class Kind : Uint8
		{
			Void,
			Int,
			Float,
			Pointer
		};

		Kind kind = Kind::Void;
		union
		{
			Int64   int_val;
			Float64 float_val;
			Uint8*  ptr_val;
		};

		InterpreterValue() : kind(Kind::Void), int_val(0) {}

		static InterpreterValue MakeVoid()
		{
			InterpreterValue v;
			v.kind = Kind::Void;
			v.int_val = 0;
			return v;
		}

		static InterpreterValue MakeInt(Int64 val)
		{
			InterpreterValue v;
			v.kind = Kind::Int;
			v.int_val = val;
			return v;
		}

		static InterpreterValue MakeFloat(Float64 val)
		{
			InterpreterValue v;
			v.kind = Kind::Float;
			v.float_val = val;
			return v;
		}

		static InterpreterValue MakePointer(Uint8* ptr)
		{
			InterpreterValue v;
			v.kind = Kind::Pointer;
			v.ptr_val = ptr;
			return v;
		}

		Int64 AsInt() const
		{
			if (kind == Kind::Float)
				return static_cast<Int64>(float_val);
			return int_val;
		}

		Float64 AsFloat() const
		{
			if (kind == Kind::Int)
				return static_cast<Float64>(int_val);
			return float_val;
		}

		Uint8* AsPointer() const
		{
			return ptr_val;
		}

		Bool IsZero() const
		{
			switch (kind)
			{
			case Kind::Int:     return int_val == 0;
			case Kind::Float:   return float_val == 0.0;
			case Kind::Pointer: return ptr_val == nullptr;
			default: 			return true;
			}
		}

		InterpreterValue Bitcast(IRType* to_type) const;
	};
}
