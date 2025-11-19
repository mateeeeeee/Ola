#include "ARM64TargetInstInfo.h"
#include "Backend/Custom/Codegen/ARM64/ARM64.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	InstInfo ARM64TargetInstInfo::GetInstInfo(Uint32 opcode) const
	{
		InstInfo inst_info{};
		switch (opcode)
		{
		case InstPush:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagUse);
		}
		break;
		case InstPop:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;
		case InstMove:
		case InstLoad:
		case InstLoadGlobalAddress:
		case InstCMoveEQ:
		case InstCMoveNE:
		case InstZExt:
		case InstF2S:
		case InstS2F:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstStore:
		case InstICmp:
		case InstFCmp:
		case InstTest:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;

		case InstAdd:
		case InstSub:
		case InstShl:
		case InstAShr:
		case InstLShr:
		case InstAnd:
		case InstOr:
		case InstXor:
		case InstSMul:
		case InstUMul:
		case InstSDiv:
		case InstUDiv:
		case InstSRem:
		case InstURem:
		case InstFAdd:
		case InstFSub:
		case InstFMul:
		case InstFDiv:
		{
			inst_info.SetOperandCount(3);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
			inst_info.SetOpFlag(2, OperandFlagUse);

		}
		break;

		case InstNeg:
		case InstNot:
		case InstFNeg:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstJump:
		case InstJE:
		case InstJNE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagNone);
			inst_info.SetInstFlag(InstFlagTerminator);
			inst_info.SetInstFlag(InstFlagBranch);
		}
		break;
		case InstCall:
		{
			inst_info.SetOperandCount(0);
			inst_info.SetInstFlag(InstFlagCall);
		}
		break;
		case InstRet:
		{
			inst_info.SetOperandCount(0);
			inst_info.SetInstFlag(InstFlagTerminator);
		}
		break;
		case ARM64_InstAdrp:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagNone); 
		}
		break;
		case ARM64_InstStp:
		{
			inst_info.SetOperandCount(3);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
			inst_info.SetOpFlag(2, OperandFlagUse);		}
		break;
		case ARM64_InstLdp:
		{
			// ldp Xd1, Xd2, [Xn, #offset] - load pair
			inst_info.SetOperandCount(3);
			inst_info.SetOpFlag(0, OperandFlagDef); 
			inst_info.SetOpFlag(1, OperandFlagDef);  	
			inst_info.SetOpFlag(2, OperandFlagUse);
		}
		break;
		case ARM64_InstMovz:
		case ARM64_InstMovk:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagNone);
		}
		break;
		case ARM64_InstFMov:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case ARM64_InstCset:
		case ARM64_InstCsetEQ:
		case ARM64_InstCsetNE:
		case ARM64_InstCsetGT:
		case ARM64_InstCsetGE:
		case ARM64_InstCsetLT:
		case ARM64_InstCsetLE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;

		case ARM64_InstMrs:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagNone);
		}
		break;
		case ARM64_InstMsr:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagNone);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case ARM64_InstMsub:
		{
			inst_info.SetOperandCount(4);
			inst_info.SetOpFlag(0, OperandFlagDef);  // Xd (destination)
			inst_info.SetOpFlag(1, OperandFlagUse);  // Xn (multiplicand)
			inst_info.SetOpFlag(2, OperandFlagUse);  // Xm (multiplier)
			inst_info.SetOpFlag(3, OperandFlagUse);  // Xa (minuend)
		}
		break;
		default:
			break;
		}
		return inst_info;
	}

	std::string ARM64TargetInstInfo::GetInstName(Uint32 opcode) const
	{
		return ARM64_GetOpcodeString(opcode);
	}
}
