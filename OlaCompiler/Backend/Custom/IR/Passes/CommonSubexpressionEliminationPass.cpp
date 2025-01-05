#include <unordered_set>
#include "CommonSubexpressionEliminationPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Utility/Hash.h"

namespace ola
{
	namespace
	{
		struct InstructionHasher
		{
			Uint64 operator()(Instruction const* I) const 
			{
				HashState hash{};
				hash.Combine(I->GetOpcode());
				for (Use const& U : I->Operands()) hash.Combine(U.GetValue());
				return hash;
			}
		};

		struct InstructionComparator
		{
			Bool operator()(Instruction const* I1, Instruction const* I2) const 
			{
				if (I1->GetOpcode() != I2->GetOpcode()) return false;
				if (I1->GetType() != I2->GetType()) return false;
				if (I1->GetNumOperands() != I2->GetNumOperands()) return false;

				for (Uint32 i = 0; i < I1->GetNumOperands(); ++i)
				{
					if (I1->GetOperand(i) != I2->GetOperand(i)) return false;
				}
				return true;
			}
		};
	}

	Bool CommonSubexpressionEliminationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool Changed = false;
		for (BasicBlock& BB : F.Blocks())
		{
			Changed |= RunOn(BB, FAM);
		}
		return Changed;
	}

	Bool CommonSubexpressionEliminationPass::RunOn(BasicBlock& BB, FunctionAnalysisManager& FAM)
	{
		std::unordered_set<Instruction*, InstructionHasher, InstructionComparator> LookupTable;
		Bool Changed = false;

		auto IsMovableInst = [](Instruction& I) 
			{
				if (I.IsTerminator()) return false;
				switch (I.GetOpcode())
				{
				case Opcode::Alloca:
				case Opcode::Phi:
				case Opcode::Load:
				case Opcode::Store:
				case Opcode::Call:
					return false;
				}
				return true;
			};
		for (Instruction& I : BB.Instructions())
		{
			if (!IsMovableInst(I)) continue;
			if (auto [iter, res] = LookupTable.insert(&I); !res) 
			{
				Changed |= I.ReplaceAllUsesWith(*iter);
			}
		}
		return Changed;
	}

}

