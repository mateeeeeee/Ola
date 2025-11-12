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
        case ARM64_InstFmov:
        case ARM64_InstUcvtf:
        case ARM64_InstFcvtzs:
        case ARM64_InstAdrp:
        case ARM64_InstLdr:
        case ARM64_InstLdp:
        case ARM64_InstMovz:
        case ARM64_InstMovk:
        {
            inst_info.SetOperandCount(2);
            inst_info.SetOpFlag(0, OperandFlagDef);
            inst_info.SetOpFlag(1, OperandFlagUse);
        }
        break;
        case InstStore:
        case ARM64_InstStr:
        case ARM64_InstStp:
        {
            inst_info.SetOperandCount(2);
            inst_info.SetOpFlag(0, OperandFlagUse);
            inst_info.SetOpFlag(1, OperandFlagUse);
        }
        break;
        case InstJump:
        case InstJE:
        case InstJNE:
        case ARM64_InstBL:
        case ARM64_InstBr:
        case ARM64_InstBlr:
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
        {
            inst_info.SetOperandCount(2);
            inst_info.SetOpFlag(0, OperandFlagDef);
            inst_info.SetOpFlag(1, OperandFlagUse);
        }
        break;
        case InstTest:
        case InstICmp:
        case InstFCmp:
        case ARM64_InstCmp:
        {
            inst_info.SetOperandCount(2);
            inst_info.SetOpFlag(0, OperandFlagUse);
            inst_info.SetOpFlag(1, OperandFlagUse);
        }
        break;
        case InstNeg:
        case InstNot:
        case InstFNeg:
        case ARM64_InstCset:
        {
            inst_info.SetOperandCount(1);
            inst_info.SetOpFlag(0, OperandFlagDef);
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
