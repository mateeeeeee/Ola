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
		case InstLoad:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstStore:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
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
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstTest:
		case x64::InstICmp:
		case x64::InstFCmp:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstNeg:
		case x64::SetE:
		case x64::SetNE:
		case x64::SetGT:
		case x64::SetGE:
		case x64::SetLT:
		case x64::SetLE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;
		}
		return inst_info;
	}
}
