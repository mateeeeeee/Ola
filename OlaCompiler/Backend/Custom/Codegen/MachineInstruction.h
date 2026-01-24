#pragma once
#include <array>
#include "MachineOperand.h"
#include "Utility/EnumOperators.h"

namespace ola
{
	enum MachineOpcode : Uint32
	{
		InstUnknown,
		// control-flow
		InstCall,
		InstRet,
		InstJump,
		InstJE,
		InstJNE,

		//Memory
		InstMove,					//generic; later: reg <- reg, reg <- immediate
		InstLoad,					//reg <- [memory]
		InstStore,					//[memory] <- reg
		InstLoadGlobalAddress,		//reg <- memory
		InstMemCpy,					//memcpy: dst, src, size (for struct copies)
		InstCMoveEQ,
		InstCMoveNE,

		//Stack
		InstPush,
		InstPop,

		// Arithmetic
		InstAdd,
		InstSub,
		InstUMul,
		InstSMul,
		InstUDiv,
		InstURem,

		// Signed Div/Rem
		InstSDiv,
		InstSRem,

		// Bitwise
		InstAnd,
		InstOr,
		InstXor,
		InstShl,
		InstLShr,
		InstAShr,

		// Unary
		InstNeg,
		InstNot,

		// FP
		InstFAdd,
		InstFSub,
		InstFMul,
		InstFDiv,
		InstFNeg,

		// Comparison
		InstICmp,
		InstFCmp,
		InstTest,

		// Conversion
		InstZExt,
		InstF2S,
		InstS2F,
		InstOpcodeCount,
		ISASpecificBegin = InstOpcodeCount,
	};

	enum MachineInstFlag : Uint32
	{
		MachineInstFlag_None = 0x0,
		MachineInstFlag_Dead = 0x1
	};

	class MachineInstruction
	{
		static constexpr Uint32 MAX_OPERANDS = 7;

	public:
		explicit MachineInstruction(Uint32 opcode) : opcode(opcode), flags(MachineInstFlag_None) 
		{}

		MachineInstruction& SetOpcode(Uint32 _opcode)
		{
			opcode = _opcode;
			return *this;
		}
		Uint32 GetOpcode() const { return opcode; }
		Char const* GetOpcodeName() const;

		Bool operator==(MachineInstruction const& rhs) const
		{
			return opcode == rhs.opcode && operands == rhs.operands;
		}

		template<Uint32 Idx>
		MachineOperand const& GetOp() const
		{
			return operands[Idx];
		}
		template<Uint32 Idx>
		MachineOperand& GetOp()
		{
			return operands[Idx];
		}
		template<Uint32 Idx>
		MachineInstruction& SetOp(MachineOperand const& operand)
		{
			static_assert(Idx < MAX_OPERANDS);
			operands[Idx] = operand;
			return* this;
		}

		MachineOperand& GetOperand(Uint32 idx)
		{
			return operands[idx];
		}
		MachineOperand const& GetOperand(Uint32 idx) const
		{
			return operands[idx];
		}
		void SetOperand(Uint32 idx, MachineOperand const& operand)
		{
			operands[idx] = operand;
		}

		MachineInstruction& SetFlag(MachineInstFlag flag)
		{
			flags |= flag;
			return *this;
		}
		MachineInstruction& SetDead()
		{
			return SetFlag(MachineInstFlag_Dead);
		}
		Bool HasFlag(MachineInstFlag flag) const
		{
			return (flags & flag) != 0;
		}
		Bool IsDead() const
		{
			return HasFlag(MachineInstFlag_Dead);
		}

	private:
		Uint32 opcode;
		Uint32 flags;
		std::array<MachineOperand, MAX_OPERANDS> operands;
	};
}