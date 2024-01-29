#include "IRBuilder.h"
#include "IRContext.h"
#include "IR.h"

namespace ola
{

	IRBuilder::IRBuilder(IRContext& ctx) : ctx(ctx), insert_point(nullptr), insert_block(nullptr)
	{
	}

	IRBuilder::IRBuilder(BasicBlock* insert_block) : ctx(insert_block->GetContext()), insert_point(nullptr)
	{
		SetInsertPoint(insert_block);
	}

	IRBuilder::IRBuilder(Instruction* insert_point) : ctx(insert_point->GetContext()), insert_point(nullptr)
	{
		SetInsertPoint(insert_point);
	}

	IRBuilder::~IRBuilder() = default;

	void IRBuilder::SetInsertPoint(Instruction* _insert_point)
	{
		insert_point = _insert_point;
		insert_block = _insert_point->GetParent();
	}

	void IRBuilder::SetInsertPoint(BasicBlock* _insert_block)
	{
		insert_block = _insert_block;
		insert_point = nullptr;
	}

	void IRBuilder::Insert(Instruction* instruction)
	{
		instruction->Insert(insert_block, insert_point);
	}

	void IRBuilder::Insert(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) return Insert(I);
	}

	void IRBuilder::InsertAfter(Instruction* instruction)
	{
		instruction->InsertAfter(insert_block, insert_point);
	}

	void IRBuilder::InsertAfter(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) return InsertAfter(I);
	}

	GlobalVariable* IRBuilder::CreateGlobalString(std::string_view str, IRModule* module)
	{
		if (!module) module = &insert_block->GetParent()->GetModule();
		ConstantString* string_constant = new ConstantString(ctx, str);
		GlobalVariable* GV = new GlobalVariable(string_constant->GetType(), *module, Linkage::Internal,string_constant);
		return GV;
	}

	ConstantInt* IRBuilder::GetConstantInt64(int64 value) const
	{
		return ctx.GetConstantInt64(value);
	}

	ConstantInt* IRBuilder::GetConstantInt8(int8 value) const
	{
		return ctx.GetConstantInt8(value);
	}

	ConstantInt* IRBuilder::GetTrueValue() const
	{
		return ctx.GetTrueValue();
	}

	ConstantInt* IRBuilder::GetFalseValue() const
	{
		return ctx.GetFalseValue();
	}

	IntegerType* IRBuilder::GetInt8Type() const
	{
		return ctx.GetIntegerType(1);
	}

	IntegerType* IRBuilder::GetInt64Type() const
	{
		return ctx.GetIntegerType(8);
	}

	FloatType* IRBuilder::GetFloatType() const
	{
		return ctx.GetFloatType();
	}

	VoidType* IRBuilder::GetVoidType() const
	{
		return ctx.GetVoidType();
	}

	PointerType* IRBuilder::GetPtrType(IRType* type)
	{
		return ctx.GetPointerType(type);
	}

}

