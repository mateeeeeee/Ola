#pragma once
#include "Value.h"
#include "Instruction.h"
#include "Utility/IteratorRange.h"

namespace ola
{

	class BasicBlock : public Value, public IListNode<BasicBlock>
	{
		friend class IRBuilder;

	public:
		BasicBlock(IRContext& ctx, std::string_view name = "", Function* parent = nullptr, BasicBlock* insert_before = nullptr) : Value(ValueKind_BasicBlock, IRLabelType::Get(ctx)), parent(parent)
		{
			SetName(name);
			if (parent) InsertInto(parent, insert_before);
			else OLA_ASSERT_MSG(!insert_before, "Cannot insert block before another block with no function!");
		}

		OLA_NONCOPYABLE(BasicBlock)
		~BasicBlock() = default;

		void SetParent(Function* _parent)
		{
			InsertInto(parent, nullptr);
		}
		Function const* GetParent() const { return parent; }
		Function* GetParent() { return parent; }

		IList<Instruction>& GetInstructions() { return inst_list; }
		IList<Instruction> const& GetInstructions() const { return inst_list; }
		Instruction const* GetTerminator() const;
		Instruction* GetTerminator()
		{
			return const_cast<Instruction*>(static_cast<const BasicBlock*>(this)->GetTerminator());
		}
		uint32 GetID() const { return block_index; }

		auto begin() { return inst_list.begin(); }
		auto begin() const { return inst_list.begin(); }
		auto end() { return inst_list.end(); }
		auto end() const { return inst_list.end(); }
		auto rbegin() { return inst_list.rbegin(); }
		auto rbegin() const { return inst_list.rbegin(); }
		auto rend() { return inst_list.rend(); }
		auto rend() const { return inst_list.rend(); }

		uint64	Size() const;
		bool    Empty() const { return inst_list.Empty(); }

		auto Predecessors() { return MakeRange(predecessors.begin(), predecessors.end()); }
		auto Predecessors() const { return MakeRange(predecessors.begin(), predecessors.end()); }
		void AddPredecessor(BasicBlock* predecessor)
		{
			predecessors.push_back(predecessor);
		}
		auto Successors() { return MakeRange(successors.begin(), successors.end()); }
		auto Successors() const { return MakeRange(successors.begin(), successors.end()); }
		void AddSuccessor(BasicBlock* successor)
		{
			successors.push_back(successor);
		}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_BasicBlock;
		}

	private:
		Function* parent;
		IList<Instruction> inst_list;
		uint32 block_index = -1;

		std::vector<BasicBlock*> predecessors;
		std::vector<BasicBlock*> successors;

	private:
		void InsertInto(Function* parent, BasicBlock* insert_before = nullptr);
	};

}