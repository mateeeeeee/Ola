#pragma once
#include "Utility/ConstexprString.h"

namespace ola
{
	enum class x86_64_Register
	{
		RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, RIP, R8, R9, R10, R11, R12, R13, R14, R15
	};

	enum class x86_64_FPRegister 
	{
		XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15
	};

	namespace x86_64_CallInfo 
	{
		struct UnixSystemVABI 
		{
			//TODO
		} SystemVABI;

		//r12, r13, r14, r15, rbx, rsp, rbp
		struct WindowsMicrosoftX64ABI 
		{
			x86_64_Register arg_registers[4] = { x86_64_Register::RCX, x86_64_Register::RDX, x86_64_Register::R8, x86_64_Register::R9 };
			x86_64_Register return_register = x86_64_Register::RAX;
			x86_64_Register callee_saved_registers[7] = { x86_64_Register::R12, x86_64_Register::R13, x86_64_Register::R14, x86_64_Register::R15, x86_64_Register::RBX, x86_64_Register::RSP, x86_64_Register::RBP };
			x86_64_Register caller_saved_registers[9] = { x86_64_Register::RAX, x86_64_Register::RCX, x86_64_Register::RDX, x86_64_Register::RSI, x86_64_Register::RDI, x86_64_Register::R8, x86_64_Register::R9, x86_64_Register::R10, x86_64_Register::R11 };

			x86_64_FPRegister fp_arg_registers[4] = { x86_64_FPRegister::XMM0, x86_64_FPRegister::XMM1, x86_64_FPRegister::XMM2, x86_64_FPRegister::XMM3 };
			x86_64_FPRegister fp_return_register = x86_64_FPRegister::XMM0;
			x86_64_FPRegister fp_callee_saved_registers[8] = { x86_64_FPRegister::XMM6, x86_64_FPRegister::XMM7, x86_64_FPRegister::XMM8, x86_64_FPRegister::XMM9, x86_64_FPRegister::XMM10, x86_64_FPRegister::XMM11, x86_64_FPRegister::XMM12, x86_64_FPRegister::XMM13 };
			x86_64_FPRegister fp_caller_saved_registers[1] = { };
		} MicrosoftX64ABI;
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
	constexpr auto ToString(x86_64_Register reg, uint32 size = 64)
	{
		using enum x86_64_Register;
		if (size == 0) size = 64;
		switch (reg)
		{
		case RAX: return LegacyGPR<'a'>(size);
		case RBX: return LegacyGPR<'b'>(size);
		case RCX: return LegacyGPR<'c'>(size);
		case RDX: return LegacyGPR<'d'>(size);
		case R8: return ExtendedGPR<8>(size);
		case R9: return ExtendedGPR<9>(size);
		case R10: return ExtendedGPR<10>(size);
		case R11: return ExtendedGPR<11>(size);
		case R12: return ExtendedGPR<12>(size);
		case R13: return ExtendedGPR<13>(size);
		case R14: return ExtendedGPR<14>(size);
		case R15: return ExtendedGPR<15>(size);
		case RDI: return Special<'d','i'>(size);
		case RSI: return Special<'s', 'i'>(size);
		case RBP: return Special<'b', 'p'>(size);
		case RSP: return Special<'s', 'p'>(size);
		case RIP: return Special<'i', 'p'>(size);
		}
		OLA_UNREACHABLE();
		return "";
	}
	constexpr auto ToString(x86_64_FPRegister reg)
	{
		switch (reg) 
		{
		case x86_64_FPRegister::XMM0: return "xmm0";
		case x86_64_FPRegister::XMM1: return "xmm1";
		case x86_64_FPRegister::XMM2: return "xmm2";
		case x86_64_FPRegister::XMM3: return "xmm3";
		case x86_64_FPRegister::XMM4: return "xmm4";
		case x86_64_FPRegister::XMM5: return "xmm5";
		case x86_64_FPRegister::XMM6: return "xmm6";
		case x86_64_FPRegister::XMM7: return "xmm7";
		case x86_64_FPRegister::XMM8: return "xmm8";
		case x86_64_FPRegister::XMM9: return "xmm9";
		case x86_64_FPRegister::XMM10: return "xmm10";
		case x86_64_FPRegister::XMM11: return "xmm11";
		case x86_64_FPRegister::XMM12: return "xmm12";
		case x86_64_FPRegister::XMM13: return "xmm13";
		case x86_64_FPRegister::XMM14: return "xmm14";
		case x86_64_FPRegister::XMM15: return "xmm15";
		default: 
			OLA_UNREACHABLE();
		}

		return "";
	}

	enum class x64ConditionCode
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
	inline constexpr x64ConditionCode InvertConditionCode(x64ConditionCode cc)
	{
		switch (cc)
		{
		case x64ConditionCode::E:  return x64ConditionCode::NE;
		case x64ConditionCode::NE: return x64ConditionCode::E;
		case x64ConditionCode::B:  return x64ConditionCode::AE;
		case x64ConditionCode::BE: return x64ConditionCode::A;
		case x64ConditionCode::A:  return x64ConditionCode::BE;
		case x64ConditionCode::AE: return x64ConditionCode::B;
		case x64ConditionCode::L:  return x64ConditionCode::GE;
		case x64ConditionCode::LE: return x64ConditionCode::G;
		case x64ConditionCode::G:  return x64ConditionCode::LE;
		case x64ConditionCode::GE: return x64ConditionCode::L;
		case x64ConditionCode::Z:  return x64ConditionCode::NZ;
		case x64ConditionCode::NZ: return x64ConditionCode::Z;
		case x64ConditionCode::S:  return x64ConditionCode::NS;
		case x64ConditionCode::NS: return x64ConditionCode::S;
		case x64ConditionCode::None:
		default:
			return x64ConditionCode::None;
		}
	}

}