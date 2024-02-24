#pragma once
#include "Utility/ConstexprString.h"

namespace ola
{
	namespace x86_64
	{
		enum Register
		{
			RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, RIP, R8, R9, R10, R11, R12, R13, R14, R15
		};

		enum FPRegister
		{
			XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15
		};

		namespace call_info
		{
			Register arg_registers[4] = { Register::RCX, Register::RDX, Register::R8, Register::R9 };
			Register return_register = Register::RAX;
			Register callee_saved_registers[7] = { Register::R12, Register::R13, Register::R14, Register::R15, Register::RBX, Register::RSP, Register::RBP };
			Register caller_saved_registers[9] = { Register::RAX, Register::RCX, Register::RDX, Register::RSI, Register::RDI, Register::R8, Register::R9, Register::R10, Register::R11 };

			FPRegister fp_arg_registers[4] = { FPRegister::XMM0, FPRegister::XMM1, FPRegister::XMM2, FPRegister::XMM3 };
			FPRegister fp_return_register = FPRegister::XMM0;
			FPRegister fp_callee_saved_registers[8] = { FPRegister::XMM6, FPRegister::XMM7, FPRegister::XMM8, FPRegister::XMM9, FPRegister::XMM10, FPRegister::XMM11, FPRegister::XMM12, FPRegister::XMM13 };
			FPRegister fp_caller_saved_registers[1] = { };
		};

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
			switch (size)
			{
			case 64: return ConstexprStringValue<'r', '0' + r>;
			case 32: return ConstexprStringValue<'r', '0' + r, 'd'>;
			case 16: return ConstexprStringValue<'r', '0' + r, 'w'>;
			case 8:  return ConstexprStringValue<'r', '0' + r, 'b'>;
			}
			OLA_UNREACHABLE();
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
		constexpr auto ToString(Register reg, uint32 size = 64)
		{
			using enum Register;
			if (size == 0) size = 64;
			switch (reg)
			{
			case RAX: return LegacyGPR<'a'>(size);
			case RBX: return LegacyGPR<'b'>(size);
			case RCX: return LegacyGPR<'c'>(size);
			case RDX: return LegacyGPR<'d'>(size);
			case R8:  return ExtendedGPR<8>(size);
			case R9:  return ExtendedGPR<9>(size);
			case R10: return ExtendedGPR<10>(size);
			case R11: return ExtendedGPR<11>(size);
			case R12: return ExtendedGPR<12>(size);
			case R13: return ExtendedGPR<13>(size);
			case R14: return ExtendedGPR<14>(size);
			case R15: return ExtendedGPR<15>(size);
			case RDI: return Special<'d', 'i'>(size);
			case RSI: return Special<'s', 'i'>(size);
			case RBP: return Special<'b', 'p'>(size);
			case RSP: return Special<'s', 'p'>(size);
			case RIP: return Special<'i', 'p'>(size);
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
	
}