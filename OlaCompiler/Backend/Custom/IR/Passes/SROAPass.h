#pragma once
#include <unordered_map>
#include <vector>
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class AllocaInst;
	class PtrAddInst;
	class IRStructType;
	class IRType;
	class BasicBlock;

	class SROAPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		SROAPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		struct FieldInfo
		{
			Uint32 index;
			Uint32 offset;
			IRType* type;
		};

		std::vector<FieldInfo> ComputeFieldLayout(IRStructType* struct_type);
		Bool IsAllocaSROACandidate(AllocaInst* AI);
		Bool TryScalarizeAlloca(AllocaInst* AI, BasicBlock& entry_block);
	};

	OLA_REGISTER_PASS(SROAPass, "SROA Pass");
	inline FunctionPass* CreateSROAPass() { return new SROAPass(); }
}
