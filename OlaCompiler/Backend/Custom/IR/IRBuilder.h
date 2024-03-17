#pragma once
#include <string>
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

		template <typename I, typename... Args>
		auto MakeInst(Args&&... args)
		{
			static_assert(std::is_base_of_v<Instruction, I>);
			I* inst = new I(std::forward<Args>(args)...);
			return inst->InsertBefore(current_block, insert_point);
		}

		BasicBlock* AddBlock(char const*);

	private:
		IRContext& ctx;
		Function* current_function;
		BasicBlock* current_block;
		IListIterator<Instruction> insert_point;
	};


}