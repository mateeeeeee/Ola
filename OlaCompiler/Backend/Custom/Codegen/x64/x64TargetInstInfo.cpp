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
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		}
		return inst_info;
	}
}
