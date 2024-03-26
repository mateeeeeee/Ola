#pragma once
#include <array>
#include "MIROperand.h"
#include "Utility/EnumOperators.h"

namespace ola
{

	enum MIRGenericInst : uint32
	{
		InstUnknown,
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

		MIROperand& GetOperand(uint32 idx)
		{
			return operands[idx];
		}
		MIROperand const& GetOperand(uint32 idx) const
		{
			return operands[idx];
		}
		void SetOperand(uint32 idx, MIROperand const& operand)
		{
			operands[idx] = operand;
		}

	private:
		uint32 opcode;
		std::array<MIROperand, MAX_OPERANDS> operands;
	};

	enum OperandFlag : uint32 
	{
		OperandFlagNone = 0,
		OperandFlagUse = 1 << 0,
		OperandFlagDef = 1 << 1
	};
	template <>
	struct EnumBitmaskOperators<OperandFlag>
	{
		static constexpr bool enable = true;
	};

	enum InstFlag : uint32 
	{
		InstFlagNone = 0,
		InstFlagLoad = 1 << 0,
		InstFlagStore = 1 << 1,
		InstFlagTerminator = 1 << 2,
		InstFlagBranch = 1 << 3,
		InstFlagCall = 1 << 4,
		InstFlagLoadConstant = 1 << 5,
		InstFlagRegDef = 1 << 6,  
		InstFlagCommutative = 1 << 7,
		InstFlagReturn = 1 << 8
	};
	template <>
	struct EnumBitmaskOperators<InstFlag>
	{
		static constexpr bool enable = true;
	};

	class MIRInstructionInfo
	{
		static constexpr uint32 MAX_OPERANDS = 7;
	public:
		MIRInstructionInfo(uint32 operand_count, InstFlag inst_flag) : operand_count(operand_count), instruction_flag(inst_flag), operand_flags()
		{
		}

		bool HasOpFlag(uint32 idx, OperandFlag flag) const
		{
			OLA_ASSERT(idx < operand_count);
			return (operand_flags[idx] & flag) == flag;
		}
		bool HasInstFlag(InstFlag flag) const
		{
			return (instruction_flag & flag) == flag;
		}
		uint32 GetOperandCount() const { return operand_count; }


	private:
		uint32 operand_count;
		OperandFlag operand_flags[MAX_OPERANDS];
		InstFlag instruction_flag;

	};
}