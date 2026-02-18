#pragma once
#include <string_view>
#include <functional>
#include <unordered_map>
#include "InterpreterValue.h"

namespace ola
{
	class InterpreterMemory;

	using IntrinsicFn = std::function<InterpreterValue(std::vector<InterpreterValue> const&, InterpreterMemory&)>;

	class Intrinsics
	{
	public:
		explicit Intrinsics(InterpreterMemory& memory);

		Bool IsIntrinsic(std::string_view name) const;
		InterpreterValue Call(std::string_view name, std::vector<InterpreterValue> const& args);

	private:
		InterpreterMemory& memory;
		std::unordered_map<std::string_view, IntrinsicFn> intrinsics;

	private:
		void RegisterIntrinsics();

		// std.io
		static InterpreterValue Intrinsic_PrintInt(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_PrintFloat(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_PrintChar(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_PrintString(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_ReadInt(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_ReadFloat(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_ReadChar(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);

		// std.math
		static InterpreterValue Intrinsic_Sqrt(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Sin(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Cos(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Tan(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Asin(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Acos(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Atan(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Atan2(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Pow(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Log(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Log2(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Log10(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Exp(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Fabs(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Fmod(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Ceil(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Floor(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Round(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Trunc(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Fmin(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Fmax(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Abs(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Min(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_Max(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);

		// std.assert
		static InterpreterValue Intrinsic_Assert(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
		static InterpreterValue Intrinsic_AssertMsg(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);

		// std.string
		static InterpreterValue Intrinsic_StringToInt(std::vector<InterpreterValue> const& args, InterpreterMemory& mem);
	};
}
