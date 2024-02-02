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
		MachineBasicBlock() = default;
		MachineBasicBlock(MachineFunction& mf, const BasicBlock* bb)
			: bb(bb), number(-1), parent(&mf)
		{
		}
		~MachineBasicBlock() = default;


		BasicBlock const* GetBasicBlock() const { return bb; }
		MachineFunction const* GetParent() const { return parent; }
		MachineFunction* GetParent() { return parent; }


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

		uint32 Size() const { return (uint32)instructions.Size(); }
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

		//add predecessor/successor stuff

	private:
		uint32 number;
		BasicBlock const* bb;
		MachineFunction* parent;
		IList<MachineInst> instructions;
		std::vector<MachineBasicBlock*> Predecessors;
		std::vector<MachineBasicBlock*> Successors;
	};
}