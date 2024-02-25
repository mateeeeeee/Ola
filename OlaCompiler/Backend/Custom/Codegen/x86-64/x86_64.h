#pragma once
#include "Utility/ConstexprString.h"

namespace ola::x86_64
{
	enum Register : uint16
	{
		RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, RIP, R8, R9, R10, R11, R12, R13, R14, R15
	};

	enum FPRegister : uint16
	{
		XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15
	};

	namespace windows
	{
		Register arg_registers[4] = { RCX, RDX, R8, R9 };
		Register return_register = RAX;
		Register callee_saved_registers[7] = { R12, R13, R14, R15, RBX, RSP, RBP };
		Register caller_saved_registers[9] = { RAX, RCX, RDX, RSI, RDI, R8, R9, R10, R11 };

		FPRegister fp_arg_registers[4] = { XMM0, XMM1, XMM2, XMM3 };
		FPRegister fp_return_register = XMM0;
		FPRegister fp_callee_saved_registers[10] = { XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15 };
		FPRegister fp_caller_saved_registers[6]  = { XMM0, XMM1, XMM2, XMM3, XMM4, XMM5 };
	};
	namespace linux
	{

	};
		

	namespace detail
	{

		template <char r>
		constexpr auto LegacyGPR(uint32 size)
		{
			switch (size)
			{
			case 64: return ConstexprStringValue<'r', r, 'x'>;
			case 32: return ConstexprStringValue<'e', r, 'x'>;
			case 16: return ConstexprStringValue<r, 'x'>;
			case 8: return ConstexprStringValue<r, 'l'>;
			}
			OLA_UNREACHABLE();
			return "";
		}
		template <uint32 r>
		constexpr auto ExtendedGPR(uint32 size)
		{
			if (r < 10)
			{
				switch (size)
				{
				case 64: return ConstexprStringValue<'r', '0' + r>;
				case 32: return ConstexprStringValue<'r', '0' + r, 'd'>;
				case 16: return ConstexprStringValue<'r', '0' + r, 'w'>;
				case 8:  return ConstexprStringValue<'r', '0' + r, 'b'>;
				}
				OLA_UNREACHABLE();
			}
			else
			{
				constexpr uint32 q = r % 10;
				switch (size)
				{
				case 64: return ConstexprStringValue<'r', '1', '0' + q>;
				case 32: return ConstexprStringValue<'r', '1', '0' + q, 'd'>;
				case 16: return ConstexprStringValue<'r', '1', '0' + q, 'w'>;
				case 8:  return ConstexprStringValue<'r', '1', '0' + q, 'b'>;
				}
				OLA_UNREACHABLE();
			}
			return "";
		}
		template <char c1, char c2>
		constexpr auto Special(uint32 size)
		{
			switch (size)
			{
			case 64: return ConstexprStringValue<'r', c1, c2>;
			case 32: return ConstexprStringValue<'e', c1, c2>;
			case 16: return ConstexprStringValue<c1, c2>;
			case 8: return  ConstexprStringValue< c1, c2, 'l'>;
			}
			OLA_UNREACHABLE();
			return "";
		}
	}

	constexpr auto ToString(Register reg, uint32 size = 64)
	{
		using enum Register;
		if (size == 0) size = 64;
		switch (reg)
		{
		case RAX: return detail::LegacyGPR<'a'>(size);
		case RBX: return detail::LegacyGPR<'b'>(size);
		case RCX: return detail::LegacyGPR<'c'>(size);
		case RDX: return detail::LegacyGPR<'d'>(size);
		case R8:  return detail::ExtendedGPR<8>(size);
		case R9:  return detail::ExtendedGPR<9>(size);
		case R10: return detail::ExtendedGPR<10>(size);
		case R11: return detail::ExtendedGPR<11>(size);
		case R12: return detail::ExtendedGPR<12>(size);
		case R13: return detail::ExtendedGPR<13>(size);
		case R14: return detail::ExtendedGPR<14>(size);
		case R15: return detail::ExtendedGPR<15>(size);
		case RDI: return detail::Special<'d', 'i'>(size);
		case RSI: return detail::Special<'s', 'i'>(size);
		case RBP: return detail::Special<'b', 'p'>(size);
		case RSP: return detail::Special<'s', 'p'>(size);
		case RIP: return detail::Special<'i', 'p'>(size);
		}
		OLA_UNREACHABLE();
		return "";
	}
	constexpr auto ToString(FPRegister reg)
	{
		switch (reg)
		{
		case XMM0: return "xmm0";
		case XMM1: return "xmm1";
		case XMM2: return "xmm2";
		case XMM3: return "xmm3";
		case XMM4: return "xmm4";
		case XMM5: return "xmm5";
		case XMM6: return "xmm6";
		case XMM7: return "xmm7";
		case XMM8: return "xmm8";
		case XMM9: return "xmm9";
		case XMM10: return "xmm10";
		case XMM11: return "xmm11";
		case XMM12: return "xmm12";
		case XMM13: return "xmm13";
		case XMM14: return "xmm14";
		case XMM15: return "xmm15";
		default:
			OLA_UNREACHABLE();
		}

		return "";
	}

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

}