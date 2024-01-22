#pragma once


namespace ola
{
	class IRContext;
	class BasicBlock;
	class Instruction;

	class IRBuilder
	{
	public:
		explicit IRBuilder(IRContext& ctx);
		explicit IRBuilder(BasicBlock* insert_block);
		explicit IRBuilder(Instruction* insert_point);
		OLA_NONCOPYABLE(IRBuilder)
		~IRBuilder();

		void SetInsertPoint(BasicBlock* _insert_block)
		{
			insert_block = _insert_block;
			insert_point = &insert_block->back();
		}

	private:
		IRContext& ctx;
		BasicBlock*  insert_block;
		Instruction* insert_point;
	
	};
}