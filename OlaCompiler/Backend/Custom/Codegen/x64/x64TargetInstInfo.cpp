#include "x64.h"
#include "x64TargetInstInfo.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{

	InstInfo x64TargetInstInfo::GetInstInfo(uint32 opcode) const
	{
		InstInfo inst_info{};
		switch (opcode)
		{
		case InstPush:
		case InstSDiv:
		case InstSRem:
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
		case x64::InstLoadFP:
		case x64::InstMoveFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstStore:
		case x64::InstStoreFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstJump:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagNone);
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
		case InstFAdd:
		case InstFSub:
		case InstFMul:
		case InstFDiv:
		case x64::InstXorFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstTest:
		case InstICmp:
		case InstFCmp:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstNeg:
		case InstFNeg:
		case x64::InstSetE:
		case x64::InstSetNE:
		case x64::InstSetGT:
		case x64::InstSetGE:
		case x64::InstSetLT:
		case x64::InstSetLE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;
		case x64::InstCqo:
		{
			inst_info.SetOperandCount(0);
		}
		break;
		}
		return inst_info;
	}
}
