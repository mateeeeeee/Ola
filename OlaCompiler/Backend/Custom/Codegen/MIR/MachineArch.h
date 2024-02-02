#pragma once
#include <string>

namespace ola
{
	enum class MachineArch
	{
		x86,
		x64,
		Unknown
	};
	enum ByteSize
	{
		ByteSize_1,
		ByteSize_2,
		ByteSize_4,
		ByteSize_8
	};

	enum class ConditionCode
	{
		None,
		E,
		NE,
		B,
		BE,
		A,
		AE,
		L,
		LE,
		G,
		GE,
		Z,
		NZ,
		S,
		NS
	};
	inline constexpr ConditionCode InvertConditionCode(ConditionCode cc)
	{
		switch (cc)
		{
		case ConditionCode::E:  return ConditionCode::NE;
		case ConditionCode::NE: return ConditionCode::E;
		case ConditionCode::B:  return ConditionCode::AE;
		case ConditionCode::BE: return ConditionCode::A;
		case ConditionCode::A:  return ConditionCode::BE;
		case ConditionCode::AE: return ConditionCode::B;
		case ConditionCode::L:  return ConditionCode::GE;
		case ConditionCode::LE: return ConditionCode::G;
		case ConditionCode::G:  return ConditionCode::LE;
		case ConditionCode::GE: return ConditionCode::L;
		case ConditionCode::Z:  return ConditionCode::NZ;
		case ConditionCode::NZ: return ConditionCode::Z;
		case ConditionCode::S:  return ConditionCode::NS;
		case ConditionCode::NS: return ConditionCode::S;
		case ConditionCode::None:
		default:
			return ConditionCode::None;
		}
	}

	enum class MachineSegment : uint16
	{
		None,
		BSS,
		Const,
		Data,
		Text
	};

	struct MachineResult
	{
		std::string no_segment;
		std::string bss_segment;
		std::string rodata_segment;
		std::string data_segment;
		std::string text_segment;
	};
}