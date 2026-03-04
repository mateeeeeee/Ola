#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "RegisterAllocator.h"
#include "InterferenceGraph.h"

namespace ola
{
	struct LiveInterval;
	struct LivenessAnalysisResult;
	class MachineOperand;
	class CopyCoalescer;

	class GraphColoringRegisterAllocator : public RegisterAllocator
	{
	public:
		explicit GraphColoringRegisterAllocator(MachineModule& M);
		~GraphColoringRegisterAllocator();
		virtual void AssignRegisters(MachineFunction&) override;

	private:
		Uint32 K_gp = 0;
		Uint32 K_fp = 0;

		std::unordered_set<Uint32> simplify_worklist;
		std::unordered_set<Uint32> spill_worklist;
		std::unordered_set<Uint32> spilled_nodes;
		std::stack<Uint32> select_stack;
		std::unordered_map<Uint32, MachineOperand> spill_slots;
		std::unique_ptr<CopyCoalescer> coalescer;
		Bool enable_coalescing = true;

	private:
		void SetupCoalescer(MachineFunction& MF, InterferenceGraph& IG);
		void Build(MachineFunction& MF, LivenessAnalysisResult& liveness, InterferenceGraph& IG);
		void ComputeSpillCosts(MachineFunction& MF, InterferenceGraph& IG, LivenessAnalysisResult& liveness);
		void MakeWorklists(InterferenceGraph& IG);
		void Simplify(InterferenceGraph& IG);
		Uint32 SelectSpill(InterferenceGraph& IG);
		Bool Select(InterferenceGraph& IG, std::vector<Uint32> const& gp_colors, std::vector<Uint32> const& fp_colors);
		void Finalize(MachineFunction& MF, InterferenceGraph& IG);
	};
}
