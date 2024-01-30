#pragma once
#include <string>
#include "IR/IRFwd.h"

namespace ola
{
	class IRType;
	class IRIntType;
	class IRFloatType;
	class IRVoidType;
	class IRPtrType;

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

		IRIntType* GetInt8Type() const;
		IRIntType* GetInt64Type() const;
		IRFloatType* GetFloatType() const;
		IRVoidType* GetVoidType() const;
		IRPtrType* GetPtrType(IRType* type);

	private:
		IRContext& ctx;
		BasicBlock*  insert_block;
		Instruction* insert_point;
	};
}