#pragma once
#include <string>
#include <list>
#include "ConstantFold.h"
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

		template <typename InstructionT, typename... Args> requires std::is_constructible_v<InstructionT, Args...>
		Value* MakeInst(Args&&... args)
		{
			static_assert(std::is_base_of_v<Instruction, InstructionT>);
			if (Value* V = TryConstantFold<InstructionT>(std::forward<Args>(args)...))
			{
				if (Instruction* I = dyn_cast<Instruction>(V))
				{
					I->InsertBefore(current_block, insert_point);
				}
				return V;
			}
			InstructionT* I = new InstructionT(std::forward<Args>(args)...);
			I->InsertBefore(current_block, insert_point);
			return I;
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