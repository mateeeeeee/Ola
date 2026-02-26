#include "Intrinsics.h"
#include "InterpreterMemory.h"
#include <cstdio>
#include <cmath>
#include <cstdlib>

namespace ola
{
	Intrinsics::Intrinsics(InterpreterMemory& memory)
		: memory(memory)
	{
		RegisterIntrinsics();
	}

	void Intrinsics::RegisterIntrinsics()
	{
		intrinsics["PrintInt"] = Intrinsic_PrintInt;
		intrinsics["PrintFloat"] = Intrinsic_PrintFloat;
		intrinsics["PrintChar"] = Intrinsic_PrintChar;
		intrinsics["PrintString"] = Intrinsic_PrintString;
		intrinsics["ReadInt"] = Intrinsic_ReadInt;
		intrinsics["ReadFloat"] = Intrinsic_ReadFloat;
		intrinsics["ReadChar"] = Intrinsic_ReadChar;

		intrinsics["Sqrt"] = Intrinsic_Sqrt;
		intrinsics["Sin"] = Intrinsic_Sin;
		intrinsics["Cos"] = Intrinsic_Cos;
		intrinsics["Tan"] = Intrinsic_Tan;
		intrinsics["Asin"] = Intrinsic_Asin;
		intrinsics["Acos"] = Intrinsic_Acos;
		intrinsics["Atan"] = Intrinsic_Atan;
		intrinsics["Atan2"] = Intrinsic_Atan2;
		intrinsics["Pow"] = Intrinsic_Pow;
		intrinsics["Log"] = Intrinsic_Log;
		intrinsics["Log2"] = Intrinsic_Log2;
		intrinsics["Log10"] = Intrinsic_Log10;
		intrinsics["Exp"] = Intrinsic_Exp;
		intrinsics["Fabs"] = Intrinsic_Fabs;
		intrinsics["Fmod"] = Intrinsic_Fmod;
		intrinsics["Ceil"] = Intrinsic_Ceil;
		intrinsics["Floor"] = Intrinsic_Floor;
		intrinsics["Round"] = Intrinsic_Round;
		intrinsics["Trunc"] = Intrinsic_Trunc;
		intrinsics["Fmin"] = Intrinsic_Fmin;
		intrinsics["Fmax"] = Intrinsic_Fmax;
		intrinsics["Abs"] = Intrinsic_Abs;
		intrinsics["Min"] = Intrinsic_Min;
		intrinsics["Max"] = Intrinsic_Max;

		intrinsics["Assert"] = Intrinsic_Assert;
		intrinsics["AssertMsg"] = Intrinsic_AssertMsg;

		intrinsics["StringToInt"] = Intrinsic_StringToInt;

		intrinsics["__ola_new"] = Intrinsic_OlaNew;
		intrinsics["__ola_delete"] = Intrinsic_OlaDelete;
	}

	Bool Intrinsics::IsIntrinsic(std::string_view name) const
	{
		return intrinsics.find(name) != intrinsics.end();
	}

	InterpreterValue Intrinsics::Call(std::string_view name, std::vector<InterpreterValue> const& args)
	{
		auto it = intrinsics.find(name);
		if (it != intrinsics.end())
		{
			return it->second(args, memory);
		}
		OLA_ASSERT_MSG(false, "Unknown intrinsic");
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_PrintInt(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty())
		{
			std::printf("%lld", static_cast<long long>(args[0].AsInt()));
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_PrintFloat(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty())
		{
			std::printf("%f", args[0].AsFloat());
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_PrintChar(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty())
		{
			std::putchar(static_cast<Char>(args[0].AsInt()));
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_PrintString(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty())
		{
			Char const* str = reinterpret_cast<Char const*>(args[0].AsPointer());
			if (str)
			{
				std::printf("%s", str);
			}
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_ReadInt(std::vector<InterpreterValue> const&, InterpreterMemory&)
	{
		Int64 val = 0;
		std::scanf("%lld", reinterpret_cast<long long*>(&val));
		return InterpreterValue::MakeInt(val);
	}

	InterpreterValue Intrinsics::Intrinsic_ReadFloat(std::vector<InterpreterValue> const&, InterpreterMemory&)
	{
		Float64 val = 0.0;
		std::scanf("%lf", &val);
		return InterpreterValue::MakeFloat(val);
	}

	InterpreterValue Intrinsics::Intrinsic_ReadChar(std::vector<InterpreterValue> const&, InterpreterMemory&)
	{
		Int val = std::getchar();
		return InterpreterValue::MakeInt(val);
	}

	InterpreterValue Intrinsics::Intrinsic_Sqrt(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::sqrt(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Sin(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::sin(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Cos(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::cos(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Tan(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::tan(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Asin(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::asin(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Acos(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::acos(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Atan(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::atan(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Atan2(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::atan2(args[0].AsFloat(), args[1].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Pow(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::pow(args[0].AsFloat(), args[1].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Log(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::log(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Log2(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::log2(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Log10(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::log10(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Exp(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::exp(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Fabs(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::fabs(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Fmod(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::fmod(args[0].AsFloat(), args[1].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Ceil(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::ceil(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Floor(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::floor(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Round(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::round(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Trunc(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::trunc(args[0].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Fmin(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::fmin(args[0].AsFloat(), args[1].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Fmax(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		return InterpreterValue::MakeFloat(std::fmax(args[0].AsFloat(), args[1].AsFloat()));
	}

	InterpreterValue Intrinsics::Intrinsic_Abs(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		Int64 val = args[0].AsInt();
		return InterpreterValue::MakeInt(val < 0 ? -val : val);
	}

	InterpreterValue Intrinsics::Intrinsic_Min(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		Int64 a = args[0].AsInt();
		Int64 b = args[1].AsInt();
		return InterpreterValue::MakeInt(a < b ? a : b);
	}

	InterpreterValue Intrinsics::Intrinsic_Max(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		Int64 a = args[0].AsInt();
		Int64 b = args[1].AsInt();
		return InterpreterValue::MakeInt(a > b ? a : b);
	}

	InterpreterValue Intrinsics::Intrinsic_Assert(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty() && args[0].IsZero())
		{
			std::fprintf(stderr, "Assertion failed!\n");
			std::exit(-252);
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_AssertMsg(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (args.size() >= 2 && args[0].IsZero())
		{
			Char const* msg = reinterpret_cast<Char const*>(args[1].AsPointer());
			std::fprintf(stderr, "Assertion failed: %s\n", msg ? msg : "");
			std::exit(-252);
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue Intrinsics::Intrinsic_StringToInt(std::vector<InterpreterValue> const& args, InterpreterMemory&)
	{
		if (!args.empty())
		{
			Char const* str = reinterpret_cast<Char const*>(args[0].AsPointer());
			if (str)
			{
				return InterpreterValue::MakeInt(std::atoll(str));
			}
		}
		return InterpreterValue::MakeInt(0);
	}

	InterpreterValue Intrinsics::Intrinsic_OlaNew(std::vector<InterpreterValue> const& args, InterpreterMemory& mem)
	{
		OLA_ASSERT(args.size() == 1);
		Uint32 size = static_cast<Uint32>(args[0].AsInt());
		Uint8* ptr = mem.HeapAlloc(size);
		return InterpreterValue::MakePointer(ptr);
	}

	InterpreterValue Intrinsics::Intrinsic_OlaDelete(std::vector<InterpreterValue> const& args, InterpreterMemory& mem)
	{
		OLA_ASSERT(args.size() == 1);
		Uint8* ptr = args[0].AsPointer();
		mem.HeapFree(ptr);
		return InterpreterValue::MakeVoid();
	}
}
