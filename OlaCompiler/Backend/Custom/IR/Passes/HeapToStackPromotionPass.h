#pragma once
#include <vector>
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class Value;
	class IRType;
	class CallInst;
	class CastInst;
	class AllocaInst;

	class HeapToStackPromotionPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		HeapToStackPromotionPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		struct HeapAllocation
		{
			CallInst* alloc_call;
			CastInst* bitcast;
			IRType* allocated_type;
			Uint64 alloc_size;
		};

		std::vector<HeapAllocation> FindHeapAllocations(Function& F);
		Bool PointerEscapes(Value* ptr, Function& F);
		void CollectDerivedPointers(Value* root, std::vector<Value*>& derived);
		Bool PromoteAllocation(HeapAllocation const& alloc, Function& F);
		void RemoveMatchingDeletes(Value* ptr, Function& F);
	};

	OLA_REGISTER_PASS(HeapToStackPromotionPass, "Heap to Stack Promotion Pass");
	inline FunctionPass* CreateHeapToStackPromotionPass() { return new HeapToStackPromotionPass(); }
}
