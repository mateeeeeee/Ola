#pragma once
#include <unordered_map>
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class Instruction;
	class Loop;
	class LoopInfo;
	class PhiInst;
	class CompareInst;
	class Value;
	class BasicBlock;

	struct InductionVariable
	{
		PhiInst* Phi = nullptr;
		Value* InitValue = nullptr;
		Value* StepValue = nullptr;
		Instruction* StepInst = nullptr;
		Bool IsIncrement = true;
	};

	struct LoopExitCondition
	{
		CompareInst* Compare = nullptr;
		Value* Bound = nullptr;
		Bool ExitOnTrue = true;
	};

	struct LoopUnrollConfig
	{
		Uint32 UnrollFactor = 4;
		Uint32 FullUnrollThreshold = 32;
		Uint32 MaxUnrolledSize = 256;
		Bool AllowPartialUnroll = true;
	};

	struct LoopUnrollAnalysis
	{
		Bool IsCanonical = false;
		Bool HasKnownTripCount = false;
		Int64 TripCount = -1;
		InductionVariable IV;
		LoopExitCondition ExitCond;
		BasicBlock* Preheader = nullptr;
		BasicBlock* Header = nullptr;
		BasicBlock* Latch = nullptr;
		BasicBlock* ExitBlock = nullptr;
	};

	class LoopUnrollPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		explicit LoopUnrollPass(LoopUnrollConfig config = {})
			: FunctionPass(id), Config(config) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		LoopUnrollConfig Config;

	private:
		LoopUnrollAnalysis AnalyzeLoop(Loop* L, Function& F) const;
		Bool FindInductionVariable(Loop* L, InductionVariable& IV) const;
		Bool FindExitCondition(Loop* L, InductionVariable const& IV, LoopExitCondition& ExitCond) const;
		Bool ComputeTripCount(InductionVariable const& IV, LoopExitCondition const& ExitCond, Int64& TripCount) const;

		Bool FullUnroll(Loop* L, LoopUnrollAnalysis const& Analysis, Function& F, LoopInfo& LI);
		Bool PartialUnroll(Loop* L, LoopUnrollAnalysis const& Analysis, Uint32 Factor, Function& F);

		std::unordered_map<Value*, Value*> CloneLoopBody(
			Loop* L,
			BasicBlock* InsertBefore,
			std::unordered_map<Value*, Value*> const& ValueMap,
			Function& F);

		static Bool CanCloneInstruction(Instruction const* I);
		Bool IsSafeToUnroll(Loop* L) const;
		Uint32 EstimateLoopSize(Loop* L) const;
	};

	OLA_REGISTER_PASS(LoopUnrollPass, "Loop Unroll Pass");

	inline FunctionPass* CreateLoopUnrollPass(LoopUnrollConfig config = {})
	{
		return new LoopUnrollPass(config);
	}
}
