#pragma once
#include <string>
#include <list>
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRType;
	class IRIntType;
	class IRFloatType;
	class IRVoidType;
	class IRPtrType;

	class Function;
	class BasicBlock;
	class Instruction;
	class IRContext;

	class IRBuilder
	{
	public:
		explicit IRBuilder(IRContext& ctx) : ctx(ctx), current_function(nullptr), current_block(nullptr) {}
		OLA_NONCOPYABLE(IRBuilder)
		~IRBuilder() {}

		IRContext& GetContext() const { return ctx; }
		Function* GetCurrentFunction() const { return current_function; }
		void SetCurrentFunction(Function* func)
		{
			current_function = func;
			current_block = nullptr;
		}
		BasicBlock* GetCurrentBlock() const { return current_block; }
		void SetCurrentBlock(BasicBlock* block);
		void SetInsertPoint(BasicBlock* block, IListIterator<Instruction> insertPoint);
		void SetInsertPoint(BasicBlock* block, Instruction* beforeInst);
		void NextInsertPoint();
		IListIterator<Instruction> GetInsertPoint() const { return insert_point; }

		template <typename I, typename... Args> requires std::is_constructible_v<I, Args...>
		auto MakeInst(Args&&... args)
		{
			static_assert(std::is_base_of_v<Instruction, I>);
			I* inst = new I(std::forward<Args>(args)...);
			inst->InsertBefore(current_block, insert_point);
			return inst;
		}

		BasicBlock* AddBlock();
		BasicBlock* AddBlock(BasicBlock* before);
		BasicBlock* AddBlock(Function* F);
		BasicBlock* AddBlock(Function* F, BasicBlock* before);

	private:
		IRContext& ctx;
		Function* current_function;
		BasicBlock* current_block;
		IListIterator<Instruction> insert_point;

		uint32 bb_label_counter = 0;
	};
}