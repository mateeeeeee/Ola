#pragma once
#include <string>
#include "Values/IRFwd.h"

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

		Instruction* Insert(Instruction* instruction);
		Value* Insert(Value* value);
		Instruction* InsertAfter(Instruction* instruction);
		Value* InsertAfter(Value* value);

		GlobalVariable* CreateGlobalString(std::string_view str, IRModule* module = nullptr);
		ConstantInt* GetInt64(int64 value) const;
		ConstantInt* GetInt8(int8 value) const;
		ConstantInt* GetTrueValue()  const;
		ConstantInt* GetFalseValue() const;

		IRIntType* GetInt8Type() const;
		IRIntType* GetInt64Type() const;
		IRFloatType* GetFloatType() const;
		IRVoidType* GetVoidType() const;
		IRPtrType* GetPtrType(IRType* type);

		BranchInst* CreateBranch(BasicBlock* destination);
		StoreInst* CreateStore(Value* val, Value* ptr);
		LoadInst* CreateLoad(IRType* type, Value* ptr);
		AllocaInst* CreateAlloca(IRType* type, Value* array_size);
		ReturnInst* CreateRetVoid();
		ReturnInst* CreateRet(Value* V);

		UnaryOperator* CreateUnaryOp(UnaryOpcode opcode, Value* op);
		BinaryOperator* CreateBinaryOp(BinaryOpcode opcode, Value* op1, Value* op2);

		CmpInst* CreateCmp(CmpPredicate predicate, Value* lhs, Value* rhs);

	private:
		IRContext& ctx;
		BasicBlock*  insert_block;
		Instruction* insert_point;

	private:
		template<typename InstTy> requires std::is_base_of_v<Instruction, InstTy>
		InstTy* Insert(InstTy* inst);
	};


}