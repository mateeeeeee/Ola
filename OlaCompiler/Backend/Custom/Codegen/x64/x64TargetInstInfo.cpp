#include "x64.h"
#include "x64TargetInstInfo.h"
#include "Backend/Custom/Codegen/MIRInstruction.h"

namespace ola
{

	InstInfo x64TargetInstInfo::GetInstInfo(uint32 opcode) const
	{
		InstInfo inst_info{};
		switch (opcode)
		{
		case InstStore:
		case InstLoad:
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
		}
		return inst_info;
	}
}
