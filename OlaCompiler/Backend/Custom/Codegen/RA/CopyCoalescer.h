#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "InterferenceGraph.h"

namespace ola
{
	class MachineFunction;
	class MachineInstruction;
	class TargetInstInfo;

	struct MoveInfo
	{
		MachineInstruction* inst;
		Uint32 src_vreg;
		Uint32 dst_vreg;
	};

	class CopyCoalescer
	{
	public:
		CopyCoalescer(InterferenceGraph& IG, Uint32 K_gp, Uint32 K_fp);

		void CollectMoves(MachineFunction& MF, TargetInstInfo const& inst_info);
		void InitWorklists();

		Bool HasWorklistMoves() const { return !move_worklist.empty(); }
		Bool HasFreezeWorklist() const { return !freeze_worklist.empty(); }

		void Coalesce();
		void Freeze();

		Uint32 GetAlias(Uint32 vreg);
		Bool IsMoveRelated(Uint32 vreg);
		void EnableMoves(Uint32 vreg);
		void DecrementDegree(Uint32 vreg);

		void AddToFreezeWorklist(Uint32 vreg) { freeze_worklist.insert(vreg); }
		void RemoveFromFreezeWorklist(Uint32 vreg) { freeze_worklist.erase(vreg); }
		Bool InFreezeWorklist(Uint32 vreg) const { return freeze_worklist.contains(vreg); }

		std::unordered_set<MachineInstruction*> const& GetCoalescedMoves() const { return coalesced_moves; }

	public:
		std::function<void(Uint32)> OnAddToSimplifyWorklist;
		std::function<void(Uint32)> OnAddToSpillWorklist;
		std::function<Bool(Uint32)> IsInSpillWorklist;

	private:
		std::vector<MoveInfo*> NodeMoves(Uint32 vreg);
		void AddWorklist(Uint32 vreg);
		Bool OK(Uint32 t, Uint32 r);
		Bool GeorgeTest(Uint32 u, Uint32 v);
		Bool Conservative(Uint32 u, Uint32 v);
		void Combine(Uint32 u, Uint32 v);
		void FreezeMoves(Uint32 vreg);

		Uint32 GetK(Uint32 vreg) const;

	private:
		InterferenceGraph& IG;
		Uint32 K_gp;
		Uint32 K_fp;

		std::unordered_set<Uint32> freeze_worklist;
		std::vector<MoveInfo> all_moves;
		std::vector<MoveInfo*> move_worklist;
		std::vector<MoveInfo*> active_moves;
		std::unordered_set<MachineInstruction*> coalesced_moves;
		std::unordered_set<MachineInstruction*> constrained_moves;
		std::unordered_set<MachineInstruction*> frozen_moves;

		std::unordered_map<Uint32, Uint32> alias;
		std::unordered_map<Uint32, std::vector<MoveInfo*>> move_list;
	};
}
