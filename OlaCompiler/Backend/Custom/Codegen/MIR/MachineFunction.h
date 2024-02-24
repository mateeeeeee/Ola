#pragma once
#include <vector>
#include <string>
#include "MIRFwd.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class Function;
	class MachineFunction : public IListNode<MachineFunction>
	{
	public:
		MachineFunction(Function const& func, uint32 number) : func(func), function_number(number)
		{
		}
		~MachineFunction();

		Function const& GetFunction() const { return func; }

		std::string_view GetName() const;
		uint32 GetFunctionNumber() const { return function_number; }

		MachineBasicBlock* GetBlockNumbered(uint32 N) const 
		{
			return mbb_numbering[N];
		}
		uint32 GetNumBlockIDs() const { return (uint32)mbb_numbering.size(); }

		auto  begin() { return basic_blocks.begin(); }
		auto  begin() const { return basic_blocks.begin(); }
		auto  end() { return basic_blocks.end(); }
		auto  end() const { return basic_blocks.end(); }
		auto  rbegin() { return basic_blocks.rbegin(); }
		auto  rbegin() const { return basic_blocks.rbegin(); }
		auto  rend() { return basic_blocks.rend(); }
		auto  rend() const { return basic_blocks.rend(); }

		uint32 Size() const;
		bool Empty() const { return basic_blocks.Empty(); }
		MachineBasicBlock const& Front() const { return basic_blocks.Front(); }
		MachineBasicBlock& Front() { return basic_blocks.Front(); }
		MachineBasicBlock const& Back() const { return basic_blocks.Back(); }
		MachineBasicBlock& Back() { return basic_blocks.Back(); }

		void PushBack(MachineBasicBlock* MBB) { basic_blocks.PushBack(MBB); }
		void PushFront(MachineBasicBlock* MBB) { basic_blocks.PushFront(MBB); }
		void insert(MachineBasicBlock* MBB, MachineBasicBlock* insert_before)
		{
			basic_blocks.Insert(MBB, insert_before);
		}
		void Remove(MachineBasicBlock* MBBI) { basic_blocks.Remove(MBBI); }

		uint32 AllocateStack(uint32 size)
		{
			uint32 offset = stack_size;
			stack_size += size;
			return offset;
		}
		uint32 GetStackSize() const { return stack_size; }
		std::string GetEndLabel() const { return std::string(GetName()) + "_End"; }

	private:
		uint32 function_number;
		Function const& func;
		IList<MachineBasicBlock> basic_blocks;
		std::vector<MachineBasicBlock*> mbb_numbering;

		uint32 stack_size = 0;

	private:
		uint32 NumberBlock(MachineBasicBlock* MBB)
		{
			mbb_numbering.push_back(MBB);
			return (uint32)mbb_numbering.size() - 1;
		}
		void UnnumberBlock(uint32 N) 
		{
			mbb_numbering[N] = nullptr;
		}
	};
}