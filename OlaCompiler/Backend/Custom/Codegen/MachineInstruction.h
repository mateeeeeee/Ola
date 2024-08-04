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
		InstJump,    
		InstTest,    
		InstJE,    
		InstJNE,    
		InstCall,
		// Memory
		InstLoad,
		InstStore,
		//Stack
		InstPush,
		InstPop,
		// Arithmetic
		InstAdd,
		InstSub,
		InstMul,
		InstUDiv,
		InstURem,
		// Bitwise
		InstAnd,
		InstOr,
		InstXor,
		InstShl,
		InstLShr,
		InstAShr,
		// Signed Div/Rem
		InstSDiv,
		InstSRem,
		// Unary
		InstNeg,
		InstNot,
		// FP
		InstFAdd,
		InstFSub,
		InstFMul,
		InstFDiv,
		InstFNeg,
		InstFFma,
		// Comparison
		InstICmpEQ,
		InstICmpNE,
		InstICmpSLT,
		InstICmpSLE,
		InstICmpSGT,
		InstICmpSGE,
		InstICmpULT,
		InstICmpULE,
		InstICmpUGT,
		InstICmpUGE,

		InstFCmpOEQ,
		InstFCmpONE,
		InstFCmpOLT,
		InstFCmpOLE,
		InstFCmpOGT,
		InstFCmpOGE,
		InstFCmpUEQ,
		InstFCmpUNE,
		InstFCmpULT,
		InstFCmpULE,
		InstFCmpUGT,
		InstFCmpUGE,
		// Conversion
		InstSExt,
		InstZExt,
		InstTrunc,
		InstF2U,
		InstF2S,
		InstU2F,
		InstS2F,
		InstFCast,
		// Misc
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
		{
		
		}

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

		void SetFlag(MachineInstFlag flag)
		{
			flags |= flag;
		}
		void SetIgnoringDefFlag()
		{
			SetFlag(MachineInstFlag_IgnoreDef);
		}
		bool HasFlag(MachineInstFlag flag) const
		{
			return (flags & flag) != 0;
		}
		bool HasIgnoringDefFlag() const
		{
			return HasFlag(MachineInstFlag_IgnoreDef);
		}

	private:
		uint32 opcode;
		uint32 flags;
		std::array<MachineOperand, MAX_OPERANDS> operands;
	};
}