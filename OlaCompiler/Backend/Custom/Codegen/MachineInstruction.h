#pragma once
#include <array>
#include "MachineOperand.h"
#include "Utility/EnumOperators.h"

namespace ola
{
	enum MachineOpcode : uint32
	{
		InstUnknown,
		// control-flow
		InstCall,
		InstJump,
		InstJE,
		InstJNE,

		//Memory
		InstMove,					//generic; later: reg <- reg, reg <- immediate
		InstLoad,					//reg <- [memory]
		InstStore,					//[memory] <- reg
		InstLoadGlobalAddress,		//reg <- memory
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
		
		ISASpecificBegin,
	};

	enum MachineInstFlag : uint32
	{
		MachineInstFlag_None = 0x0,
		MachineInstFlag_IgnoreDef = 0x1,
	};

	class MachineInstruction
	{
		static constexpr uint32 MAX_OPERANDS = 7;

	public:
		explicit MachineInstruction(uint32 opcode) : opcode(opcode), flags(MachineInstFlag_None) 
		{}

		MachineInstruction& SetOpcode(uint32 _opcode)
		{
			opcode = _opcode;
			return *this;
		}
		uint32 GetOpcode() const { return opcode; }


		bool operator==(MachineInstruction const& rhs) const
		{
			return opcode == rhs.opcode && operands == rhs.operands;
		}

		template<uint32 Idx>
		MachineOperand const& GetOp() const
		{
			return operands[Idx];
		}
		template<uint32 Idx>
		MachineOperand& GetOp()
		{
			return operands[Idx];
		}
		template<uint32 Idx>
		MachineInstruction& SetOp(MachineOperand const& operand)
		{
			static_assert(Idx < MAX_OPERANDS);
			operands[Idx] = operand;
			return* this;
		}

		MachineOperand& GetOperand(uint32 idx)
		{
			return operands[idx];
		}
		MachineOperand const& GetOperand(uint32 idx) const
		{
			return operands[idx];
		}
		void SetOperand(uint32 idx, MachineOperand const& operand)
		{
			operands[idx] = operand;
		}

		MachineInstruction& SetFlag(MachineInstFlag flag)
		{
			flags |= flag;
			return *this;
		}
		MachineInstruction& SetIgnoreDef()
		{
			return SetFlag(MachineInstFlag_IgnoreDef);
		}

		bool HasFlag(MachineInstFlag flag) const
		{
			return (flags & flag) != 0;
		}
		bool HasIgnoreDef() const
		{
			return HasFlag(MachineInstFlag_IgnoreDef);
		}

	private:
		uint32 opcode;
		uint32 flags;
		std::array<MachineOperand, MAX_OPERANDS> operands;
	};
}