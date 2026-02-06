#include "AliasAnalysisPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{
	Bool AliasAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		// AliasAnalysis doesn't need per-function state for our simple implementation
		// The analysis is stateless and can be queried directly
		return false;
	}

	MemoryLocation AliasAnalysis::GetMemoryLocation(Value* Ptr)
	{
		MemoryLocation Loc{};
		Loc.Ptr = Ptr;
		Loc.Offset = 0;
		while (Ptr)
		{
			if (PtrAddInst* PA = dyn_cast<PtrAddInst>(Ptr))
			{
				if (ConstantInt* CI = dyn_cast<ConstantInt>(PA->GetOffset()))
				{
					if (Loc.HasKnownOffset())
					{
						Loc.Offset += CI->GetValue();
					}
				}
				else
				{
					Loc.Offset = UNKNOWN_MEMORY_OFFSET;
				}
				Ptr = PA->GetBase();
				Loc.Ptr = Ptr;
			}
			else if (GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(Ptr))
			{
				// for GEP, we'd need to compute the offset from indices
				// for now, treat as unknown offset but continue to base
				Loc.Offset = UNKNOWN_MEMORY_OFFSET;
				Ptr = GEP->GetBaseOperand();
				Loc.Ptr = Ptr;
			}
			else
			{
				break;
			}
		}
		return Loc;
	}

	Value* AliasAnalysis::GetUnderlyingObject(Value* V)
	{
		while (V)
		{
			if (PtrAddInst* PA = dyn_cast<PtrAddInst>(V))
			{
				V = PA->GetBase();
			}
			else if (GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(V))
			{
				V = GEP->GetBaseOperand();
			}
			else if (CastInst* CI = dyn_cast<CastInst>(V))
			{
				if (CI->GetOpcode() == Opcode::Bitcast)
				{
					V = CI->GetSrc();
				}
				else
				{
					break;
				}
			}
			else if (PhiInst* Phi = dyn_cast<PhiInst>(V))
			{
				// could do more sophisticated analysis here somehow?
				break;
			}
			else
			{
				break;
			}
		}
		return V;
	}

	Bool AliasAnalysis::IsIdentifiedObject(Value* V)
	{
		/*An "identified" object is one with a distinct identity that cannot alias with other identified objects:
			- AllocaInst: local stack allocations
			- GlobalVariable: global variables */
		return isa<AllocaInst>(V) || isa<GlobalVariable>(V);
	}

	AliasResult AliasAnalysis::AliasFromUnderlyingObjects(Value* O1, Value* O2) const
	{
		if (O1 == O2)
		{
			return AliasResult::MayAlias;  // Could be MustAlias if offsets match
		}

		if (IsIdentifiedObject(O1) && IsIdentifiedObject(O2))
		{
			return AliasResult::NoAlias;
		}

		if (AllocaInst* AI1 = dyn_cast<AllocaInst>(O1))
		{
			if (isa<GlobalVariable>(O2))
			{
				return AliasResult::NoAlias;
			}
		}
		if (AllocaInst* AI2 = dyn_cast<AllocaInst>(O2))
		{
			if (isa<GlobalVariable>(O1))
			{
				return AliasResult::NoAlias;
			}
		}
		return AliasResult::MayAlias;
	}

	AliasResult AliasAnalysis::Alias(Value* P1, Value* P2) const
	{
		if (P1 == P2)
		{
			return AliasResult::MustAlias;
		}

		Value* O1 = GetUnderlyingObject(P1);
		Value* O2 = GetUnderlyingObject(P2);

		AliasResult BaseResult = AliasFromUnderlyingObjects(O1, O2);
		if (BaseResult == AliasResult::NoAlias)
		{
			return AliasResult::NoAlias;
		}

		if (O1 == O2)
		{
			MemoryLocation Loc1 = GetMemoryLocation(P1);
			MemoryLocation Loc2 = GetMemoryLocation(P2);
			if (Loc1.HasKnownOffset() && Loc2.HasKnownOffset())
			{
				if (Loc1.Offset != Loc2.Offset)
				{
					return AliasResult::NoAlias;
				}
				else
				{
					return AliasResult::MustAlias;
				}
			}
		}
		return AliasResult::MayAlias;
	}

	AliasResult AliasAnalysis::Alias(MemoryLocation const& Loc1, MemoryLocation const& Loc2) const
	{
		if (!Loc1.Ptr || !Loc2.Ptr)
		{
			return AliasResult::MayAlias;
		}

		Value* O1 = GetUnderlyingObject(Loc1.Ptr);
		Value* O2 = GetUnderlyingObject(Loc2.Ptr);

		AliasResult BaseResult = AliasFromUnderlyingObjects(O1, O2);
		if (BaseResult == AliasResult::NoAlias)
		{
			return AliasResult::NoAlias;
		}

		if (O1 == O2 && Loc1.HasKnownOffset() && Loc2.HasKnownOffset())
		{
			MemoryLocation BaseLoc1 = GetMemoryLocation(Loc1.Ptr);
			MemoryLocation BaseLoc2 = GetMemoryLocation(Loc2.Ptr);

			if (BaseLoc1.HasKnownOffset() && BaseLoc2.HasKnownOffset())
			{
				Int64 TotalOffset1 = BaseLoc1.Offset + Loc1.Offset;
				Int64 TotalOffset2 = BaseLoc2.Offset + Loc2.Offset;

				if (TotalOffset1 != TotalOffset2)
				{
					return AliasResult::NoAlias;
				}
				return AliasResult::MustAlias;
			}
		}
		return AliasResult::MayAlias;
	}
}
