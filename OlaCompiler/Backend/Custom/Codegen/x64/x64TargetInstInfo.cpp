#include "x64.h"
#include "x64TargetInstInfo.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{

	InstInfo x64TargetInstInfo::GetInstInfo(Uint32 opcode) const
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
		case x64::InstSetA:
		case x64::InstSetAE:
		case x64::InstSetB:
		case x64::InstSetBE:
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

	std::string x64TargetInstInfo::GetInstName(Uint32 opcode) const
	{
		OLA_ASSERT(opcode > ISASpecificBegin);
		switch (opcode)
		{
		case x64::InstSetE:		return "x64::SetE";
		case x64::InstSetNE:	return "x64::SetNE";
		case x64::InstSetGT:	return "x64::SetGT";
		case x64::InstSetGE:	return "x64::SetGE";
		case x64::InstSetLT:	return "x64::SetLT";
		case x64::InstSetLE:	return "x64::SetLE";
		case x64::InstSetA:		return "x64::SetA";
		case x64::InstSetAE:	return "x64::SetAE";
		case x64::InstSetB:		return "x64::SetB";
		case x64::InstSetBE:	return "x64::SetBE";
		case x64::InstCqo:		return "x64::Cqo";
		case x64::InstMoveFP:	return "x64::MoveFP";
		case x64::InstStoreFP:	return "x64::StoreFP";
		case x64::InstLoadFP:	return "x64::LoadFP";
		case x64::InstXorFP:	return "x64::XorFP";
		}
		return "";
	}

}
