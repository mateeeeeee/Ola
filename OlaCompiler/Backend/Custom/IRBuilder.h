#pragma once
#include <string>
#include "IR/IRFwd.h"

namespace ola
{
	class IRType;
	class IntegerType;
	class FloatType;
	class VoidType;
	class PointerType;

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

		GlobalVariable* CreateGlobalString(std::string_view str, IRModule* module = nullptr);
		ConstantInt* GetConstantInt64(int64 value) const;
		ConstantInt* GetConstantInt8(int8 value) const;
		ConstantInt* GetTrueValue()  const;
		ConstantInt* GetFalseValue() const;

		IntegerType* GetInt8Type() const;
		IntegerType* GetInt64Type() const;
		FloatType* GetFloatType() const;
		VoidType* GetVoidType() const;
		PointerType* GetPtrType(IRType* type);

	private:
		IRContext& ctx;
		BasicBlock*  insert_block;
		Instruction* insert_point;
	};
}