#pragma once
#include <string>

namespace ola
{
	class IRType;
	class IRIntType;
	class IRFloatType;
	class IRVoidType;
	class IRPtrType;

	class Function;
	class BasicBlock;
	class IRContext;

	class IRBuilder
	{
	public:
	public:
		explicit IRBuilder(IRContext& ctx) : ctx(ctx) {}
		OLA_NONCOPYABLE(IRBuilder)
		~IRBuilder() {}

		IRContext& GetContext() const { return ctx; }

	private:
		IRContext& ctx;
		Function* mCurrentFunction;
		BasicBlock* mCurrentBlock;
		//IntrusiveListIterator<Instruction> mInsertPoint;

	};


}