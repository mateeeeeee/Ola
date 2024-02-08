#pragma once
#include <vector>
#include <string>
#include "MIRFwd.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class BasicBlock;
	class MachineBasicBlock : public IListNode<MachineBasicBlock>
	{
		friend class MachineFunction;
	public:
		MachineBasicBlock();
		MachineBasicBlock(MachineFunction& mf, const BasicBlock* bb);
		~MachineBasicBlock();

		BasicBlock const* GetBasicBlock() const { return bb; }
		MachineFunction const* GetParent() const { return parent; }
		MachineFunction* GetParent() { return parent; }

		IList<MachineInst>& GetInstructions() { return instructions; }
		IList<MachineInst> const& GetInstructions() const { return instructions; }

		std::string_view GetName() const 
		{
			//return bb ? bb->GetName() : "";
			return "";
		}
		std::string GetFullName() const
		{
			return "";
		}

		uint32 GetNumber() const { return number; }
		void SetNumber(uint32 N) { number = N; }

		uint32 Size() const;
		bool  Empty() const { return instructions.Empty(); }

		MachineInst& Front() { return instructions.Front(); }
		MachineInst& Back() { return instructions.Back(); }
		MachineInst const& Front() const { return instructions.Front(); }
		MachineInst const& Back()  const { return instructions.Back(); }

		auto begin() { return instructions.begin(); }
		auto begin() const { return instructions.begin(); }
		auto end() { return instructions.end(); }
		auto end() const { return instructions.end(); }
		auto rbegin() { return instructions.rbegin(); }
		auto rbegin() const { return instructions.rbegin(); }
		auto rend() { return instructions.rend(); }
		auto rend() const { return instructions.rend(); }

		void AddPredecessor(MachineBasicBlock* p)
		{
			predecessors.push_back(p);
		}
		void AddSuccessor(MachineBasicBlock* s)
		{
			successors.push_back(s);
		}

	private:
		uint32 number = -1;
		BasicBlock const* bb = nullptr;
		MachineFunction* parent = nullptr;
		IList<MachineInst> instructions;
		std::vector<MachineBasicBlock*> predecessors;
		std::vector<MachineBasicBlock*> successors;
	};
}