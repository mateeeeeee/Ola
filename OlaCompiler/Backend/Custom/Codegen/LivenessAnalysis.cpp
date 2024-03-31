#include "LivenessAnalysis.h"
#include "MIRGlobal.h"
#include "MIRBasicBlock.h"
#include "MIRModule.h"

namespace ola
{
	static inline uint32 GetRegAsUint(MIROperand const& operand)
	{
		OLA_ASSERT(operand.IsReg() && (IsVirtualReg(operand.GetReg().reg) || IsISAReg(operand.GetReg().reg)));
		return static_cast<uint32>(operand.GetReg().reg);
	}


	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF)
	{
		LivenessAnalysisResult result{};
		return result;
	}

}


