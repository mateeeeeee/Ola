#include "x64TargetInstInfo.h"
#include "Backend/Custom/Codegen/x64/x64.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{

	InstInfo Microsoft_x64TargetInstInfo::GetInstInfo(Uint32 opcode) const
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
		case x64_InstLoadFP:
		case x64_InstMoveFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstStore:
		case x64_InstStoreFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagUse);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstJump:
		case InstJE:
		case InstJNE:
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
		case x64_InstXorFP:
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
		case InstNot:
		case InstFNeg:
		case x64_InstSetE:
		case x64_InstSetNE:
		case x64_InstSetGT:
		case x64_InstSetGE:
		case x64_InstSetLT:
		case x64_InstSetLE:
		case x64_InstSetA:
		case x64_InstSetAE:
		case x64_InstSetB:
		case x64_InstSetBE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;
		case x64_InstCqo:
		{
			inst_info.SetOperandCount(0);
		}
		break;
		}
		return inst_info;
	}

	std::string Microsoft_x64TargetInstInfo::GetInstName(Uint32 opcode) const
	{
		OLA_ASSERT(opcode > ISASpecificBegin);
		switch (opcode)
		{
		case x64_InstSetE:		return "x64_SetE";
		case x64_InstSetNE:	return "x64_SetNE";
		case x64_InstSetGT:	return "x64_SetGT";
		case x64_InstSetGE:	return "x64_SetGE";
		case x64_InstSetLT:	return "x64_SetLT";
		case x64_InstSetLE:	return "x64_SetLE";
		case x64_InstSetA:		return "x64_SetA";
		case x64_InstSetAE:	return "x64_SetAE";
		case x64_InstSetB:		return "x64_SetB";
		case x64_InstSetBE:	return "x64_SetBE";
		case x64_InstCqo:		return "x64_Cqo";
		case x64_InstMoveFP:	return "x64_MoveFP";
		case x64_InstStoreFP:	return "x64_StoreFP";
		case x64_InstLoadFP:	return "x64_LoadFP";
		case x64_InstXorFP:	return "x64_XorFP";
		}
		return "";
	}

}
