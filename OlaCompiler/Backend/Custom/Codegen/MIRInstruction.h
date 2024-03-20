#pragma once
#include <array>
#include "MIROperand.h"

namespace ola
{

	enum MIRGenericInst : uint32
	{
		// control-flow
		InstJump,    
		InstBranch,  
		InstUnreachable,
		// Memory
		InstLoad,
		InstStore,
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
		InstFAbs,
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
		InstCopy,
		InstSelect,
		InstLoadGlobalAddress,
		InstLoadImm,
		InstLoadStackObjectAddr,
		InstCopyFromReg,
		InstCopyToReg,
		InstLoadImmToReg,
		InstLoadRegFromStack,
		InstStoreRegToStack,

		ISASpecificBegin,
	};

	class MIRInstruction
	{
		static constexpr uint32 MAX_OPERANDS = 7;

	public:
		explicit MIRInstruction(uint32 opcode) : opcode(opcode) {}

		MIRInstruction& SetOpcode(uint32 _opcode)
		{
			opcode = _opcode;
			return *this;
		}
		uint32 GetOpcode() const { return opcode; }


		bool operator==(MIRInstruction const& rhs) const
		{
			return opcode == rhs.opcode && operands == rhs.operands;
		}

		template<uint32 Idx>
		MIROperand const& GetOp() const
		{
			return operands[Idx];
		}
		template<uint32 Idx>
		MIROperand& GetOp()
		{
			return operands[Idx];
		}

		template<uint32 Idx>
		MIRInstruction& SetOp(MIROperand const& operand)
		{
			static_assert(Idx < MAX_OPERANDS);
			operands[Idx] = operand;
			return* this;
		}

	private:
		uint32 opcode;
		std::array<MIROperand, MAX_OPERANDS> operands;
	};
}