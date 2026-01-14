#include "X86TargetInstInfo.h"
#include "Backend/Custom/Codegen/X86/X86.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{

	InstInfo X86TargetInstInfo::GetInstInfo(Uint32 opcode) const
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
		case X86_InstLoadFP:
		case X86_InstMoveFP:
		{
			inst_info.SetOperandCount(2);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
		}
		break;
		case InstStore:
		case X86_InstStoreFP:
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
		case X86_InstXorFP:
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
		case X86_InstSetE:
		case X86_InstSetNE:
		case X86_InstSetGT:
		case X86_InstSetGE:
		case X86_InstSetLT:
		case X86_InstSetLE:
		case X86_InstSetA:
		case X86_InstSetAE:
		case X86_InstSetB:
		case X86_InstSetBE:
		{
			inst_info.SetOperandCount(1);
			inst_info.SetOpFlag(0, OperandFlagDef);
		}
		break;
		case X86_InstCqo:
		{
			inst_info.SetOperandCount(0);
		}
		break;
		case X86_InstLea:
		{
			inst_info.SetOperandCount(5);
			inst_info.SetOpFlag(0, OperandFlagDef);
			inst_info.SetOpFlag(1, OperandFlagUse);
			inst_info.SetOpFlag(2, OperandFlagUse);
			inst_info.SetOpFlag(3, OperandFlagNone);
			inst_info.SetOpFlag(4, OperandFlagNone);
		}
		break;
		}
		return inst_info;
	}

	std::string X86TargetInstInfo::GetInstName(Uint32 opcode) const
	{
		OLA_ASSERT(opcode > ISASpecificBegin);
		switch (opcode)
		{
		case X86_InstSetE:		return "X86_SetE";
		case X86_InstSetNE:		return "X86_SetNE";
		case X86_InstSetGT:		return "X86_SetGT";
		case X86_InstSetGE:		return "X86_SetGE";
		case X86_InstSetLT:		return "X86_SetLT";
		case X86_InstSetLE:		return "X86_SetLE";
		case X86_InstSetA:		return "X86_SetA";
		case X86_InstSetAE:		return "X86_SetAE";
		case X86_InstSetB:		return "X86_SetB";
		case X86_InstSetBE:		return "X86_SetBE";
		case X86_InstCqo:		return "X86_Cqo";
		case X86_InstMoveFP:	return "X86_MoveFP";
		case X86_InstStoreFP:	return "X86_StoreFP";
		case X86_InstLoadFP:	return "X86_LoadFP";
		case X86_InstXorFP:		return "X86_XorFP";
		case X86_InstLea:		return "X86_Lea";
		}
		return "";
	}

}
