#include "CopyCoalescer.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/Targets/Target.h"

namespace ola
{
	CopyCoalescer::CopyCoalescer(InterferenceGraph& IG, Uint32 K_gp, Uint32 K_fp)
		: IG(IG), K_gp(K_gp), K_fp(K_fp)
	{
	}

	Uint32 CopyCoalescer::GetK(Uint32 vreg) const
	{
		IGNode const* node = IG.GetNode(vreg);
		return (node && node->is_float) ? K_fp : K_gp;
	}

	void CopyCoalescer::CollectMoves(MachineFunction& MF, TargetInstInfo const& inst_info)
	{
		all_moves.clear();
		move_list.clear();
		for (auto& MBB : MF.Blocks())
		{
			for (MachineInstruction& MI : MBB->Instructions())
			{
				if (MI.GetOpcode() != InstMove)
				{
					continue;
				}

				InstInfo const& info = inst_info.GetInstInfo(MI);
				if (info.GetOperandCount() < 2)
				{
					continue;
				}

				MachineOperand& dst = MI.GetOperand(0);
				MachineOperand& src = MI.GetOperand(1);
				if (!IsOperandVReg(dst) || !IsOperandVReg(src))
				{
					continue;
				}

				Bool dst_float = dst.GetType() == MachineType::Float64;
				Bool src_float = src.GetType() == MachineType::Float64;
				if (dst_float != src_float)
				{
					continue;
				}

				Uint32 src_vreg = src.GetReg().reg;
				Uint32 dst_vreg = dst.GetReg().reg;
				if (src_vreg != dst_vreg)
				{
					all_moves.push_back(MoveInfo{ &MI, src_vreg, dst_vreg });
				}
			}
		}

		for (MoveInfo& move : all_moves)
		{
			move_list[move.src_vreg].push_back(&move);
			move_list[move.dst_vreg].push_back(&move);
		}
	}

	void CopyCoalescer::InitWorklists()
	{
		move_worklist.clear();
		active_moves.clear();
		coalesced_moves.clear();
		constrained_moves.clear();
		frozen_moves.clear();
		alias.clear();

		for (MoveInfo& move : all_moves)
		{
			move_worklist.push_back(&move);
		}
	}

	Uint32 CopyCoalescer::GetAlias(Uint32 vreg)
	{
		if (alias.contains(vreg))
		{
			return GetAlias(alias[vreg]);
		}
		return vreg;
	}

	Bool CopyCoalescer::IsMoveRelated(Uint32 vreg)
	{
		return !NodeMoves(vreg).empty();
	}

	std::vector<MoveInfo*> CopyCoalescer::NodeMoves(Uint32 vreg)
	{
		std::vector<MoveInfo*> result{};
		if (!move_list.contains(vreg))
		{
			return result;
		}

		for (MoveInfo* move : move_list[vreg])
		{
			Bool const in_active = std::find(active_moves.begin(), active_moves.end(), move) != active_moves.end();
			Bool const in_worklist = std::find(move_worklist.begin(), move_worklist.end(), move) != move_worklist.end();
			if (in_active || in_worklist)
			{
				result.push_back(move);
			}
		}
		return result;
	}

	void CopyCoalescer::AddWorklist(Uint32 vreg)
	{
		IGNode* node = IG.GetNode(vreg);
		if (!node)
		{
			return;
		}

		Uint32 K = GetK(vreg);
		if (node->degree < K && !IsMoveRelated(vreg))
		{
			freeze_worklist.erase(vreg);
			if (OnAddToSimplifyWorklist)
			{
				OnAddToSimplifyWorklist(vreg);
			}
		}
	}

	void CopyCoalescer::EnableMoves(Uint32 vreg)
	{
		for (MoveInfo* move : NodeMoves(vreg))
		{
			auto it = std::find(active_moves.begin(), active_moves.end(), move);
			if (it != active_moves.end())
			{
				active_moves.erase(it);
				move_worklist.push_back(move);
			}
		}
	}

	void CopyCoalescer::DecrementDegree(Uint32 vreg)
	{
		IGNode* node = IG.GetNode(vreg);
		if (!node)
		{
			return;
		}

		Uint32 K = GetK(vreg);
		Uint32 old_degree = node->degree;
		if (old_degree == K)
		{
			EnableMoves(vreg);
			for (Uint32 neighbor : node->neighbors)
			{
				EnableMoves(neighbor);
			}

			if (IsInSpillWorklist && IsInSpillWorklist(vreg))
			{
				if (IsMoveRelated(vreg))
				{
					freeze_worklist.insert(vreg);
				}
				else if (OnAddToSimplifyWorklist)
				{
					OnAddToSimplifyWorklist(vreg);
				}
			}
		}
	}

	// George's OK test: t is OK to coalesce with r if:
	// t already interferes with r
	// OR
	// t has insignificant degree (< K)
	Bool CopyCoalescer::OK(Uint32 t, Uint32 r)
	{
		IGNode* t_node = IG.GetNode(t);
		if (!t_node)
		{
			return true;
		}
		Uint32 K = GetK(t);
		return t_node->degree < K || IG.Interferes(t, r);
	}

	// George test: coalesce u into v if for every neighbor t of v, OK(t, u)
	Bool CopyCoalescer::GeorgeTest(Uint32 u, Uint32 v)
	{
		IGNode* v_node = IG.GetNode(v);
		if (!v_node)
		{
			return false;
		}
		for (Uint32 t : v_node->neighbors)
		{
			IGNode* t_node = IG.GetNode(t);
			if (t_node && !t_node->on_stack && GetAlias(t) != GetAlias(u))
			{
				if (!OK(t, u))
				{
					return false;
				}
			}
		}
		return true;
	}

	// Briggs conservative test: coalesce if merged node has < K significant-degree neighbors
	Bool CopyCoalescer::Conservative(Uint32 u, Uint32 v)
	{
		IGNode* u_node = IG.GetNode(u);
		IGNode* v_node = IG.GetNode(v);
		if (!u_node || !v_node)
		{
			return false;
		}

		std::unordered_set<Uint32> neighbors;
		for (Uint32 n : u_node->neighbors)
		{
			IGNode* n_node = IG.GetNode(n);
			if (n_node && !n_node->on_stack)
			{
				neighbors.insert(GetAlias(n));
			}
		}
		for (Uint32 n : v_node->neighbors)
		{
			IGNode* n_node = IG.GetNode(n);
			if (n_node && !n_node->on_stack)
			{
				neighbors.insert(GetAlias(n));
			}
		}

		Uint32 K = GetK(u);
		Uint32 significant = 0;
		for (Uint32 n : neighbors)
		{
			if (n == u || n == v)
			{
				continue;
			}
			IGNode* n_node = IG.GetNode(n);
			if (n_node && n_node->degree >= K)
			{
				significant++;
			}
		}
		return significant < K;
	}

	void CopyCoalescer::Combine(Uint32 u, Uint32 v)
	{
		freeze_worklist.erase(v);
		alias[v] = u;

		for (MoveInfo* move : move_list[v])
		{
			move_list[u].push_back(move);
		}

		IGNode* v_node = IG.GetNode(v);
		IGNode* u_node = IG.GetNode(u);
		if (!v_node || !u_node)
		{
			return;
		}

		for (Uint32 t : v_node->neighbors)
		{
			IGNode* t_node = IG.GetNode(t);
			if (!t_node || t_node->on_stack)
			{
				continue;
			}

			Uint32 t_alias = GetAlias(t);
			if (t_alias == u)
			{
				continue;
			}

			if (!IG.Interferes(t_alias, u))
			{
				IG.AddInterference(t_alias, u);
			}
			IG.DecrementDegree(t_alias);
			DecrementDegree(t_alias);
		}

		Uint32 K = GetK(u);
		if (u_node->degree >= K && freeze_worklist.contains(u))
		{
			freeze_worklist.erase(u);
			if (OnAddToSpillWorklist)
			{
				OnAddToSpillWorklist(u);
			}
		}
	}

	void CopyCoalescer::Coalesce()
	{
		if (move_worklist.empty())
		{
			return;
		}

		MoveInfo* move = move_worklist.back();
		move_worklist.pop_back();

		Uint32 x = GetAlias(move->dst_vreg);
		Uint32 y = GetAlias(move->src_vreg);
		if (x == y)
		{
			coalesced_moves.insert(move->inst);
			AddWorklist(x);
			return;
		}

		if (IG.Interferes(x, y))
		{
			constrained_moves.insert(move->inst);
			AddWorklist(x);
			AddWorklist(y);
			return;
		}

		// try to coalesce using George or Briggs test
		// prefer to coalesce smaller into larger (by degree)
		IGNode* x_node = IG.GetNode(x);
		IGNode* y_node = IG.GetNode(y);
		Uint32 u = x, v = y;
		if (x_node && y_node && y_node->degree > x_node->degree)
		{
			u = y;
			v = x;
		}

		if (GeorgeTest(u, v) || Conservative(u, v))
		{
			coalesced_moves.insert(move->inst);
			Combine(u, v);
			AddWorklist(u);
		}
		else
		{
			active_moves.push_back(move);
		}
	}

	void CopyCoalescer::FreezeMoves(Uint32 vreg)
	{
		for (MoveInfo* move : NodeMoves(vreg))
		{
			Uint32 x = move->dst_vreg;
			Uint32 y = move->src_vreg;
			Uint32 v = (GetAlias(y) == GetAlias(vreg)) ? GetAlias(x) : GetAlias(y);

			auto it = std::find(active_moves.begin(), active_moves.end(), move);
			if (it != active_moves.end())
			{
				active_moves.erase(it);
			}

			auto it2 = std::find(move_worklist.begin(), move_worklist.end(), move);
			if (it2 != move_worklist.end())
			{
				move_worklist.erase(it2);
			}
			frozen_moves.insert(move->inst);

			IGNode* v_node = IG.GetNode(v);
			if (v_node && !IsMoveRelated(v) && v_node->degree < GetK(v))
			{
				freeze_worklist.erase(v);
				if (OnAddToSimplifyWorklist)
				{
					OnAddToSimplifyWorklist(v);
				}
			}
		}
	}

	void CopyCoalescer::Freeze()
	{
		if (freeze_worklist.empty())
		{
			return;
		}

		Uint32 vreg = *freeze_worklist.begin();
		freeze_worklist.erase(vreg);
		if (OnAddToSimplifyWorklist)
		{
			OnAddToSimplifyWorklist(vreg);
		}
		FreezeMoves(vreg);
	}
}
