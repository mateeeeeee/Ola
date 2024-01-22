#pragma once

namespace ola
{
	class IRContext;
	class Value;
	class BasicBlock;
	class Instruction;

	class IRBuilder
	{
	public:
	public:
		explicit IRBuilder(IRContext& ctx);
		explicit IRBuilder(BasicBlock* insert_block);
		explicit IRBuilder(Instruction* insert_point);
		OLA_NONCOPYABLE(IRBuilder)
		~IRBuilder();

		IRContext& GetContext() const { return ctx; }

		BasicBlock*  GetInsertBlock() const { return insert_block; }
		Instruction* GetInsertPoint() const { return insert_point; }

		void SetInsertPoint(BasicBlock* _insert_block);
		void SetInsertPoint(Instruction* _insert_point);

		void ClearInsertPoint()
		{
			insert_block = nullptr;
			insert_point = nullptr;
		}

		void Insert(Instruction* instruction);
		void Insert(Value* value);
		void InsertAfter(Instruction* instruction);
		void InsertAfter(Value* value);

	private:
		IRContext& ctx;
		BasicBlock*  insert_block;
		Instruction* insert_point;
	};
}