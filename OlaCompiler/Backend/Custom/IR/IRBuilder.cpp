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

	Instruction* IRBuilder::Insert(Instruction* instruction)
	{
		return insert_block->GetInstructions().Insert(instruction, insert_point);
	}

	Value* IRBuilder::Insert(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) return Insert(I);
		return nullptr;
	}

	Instruction* IRBuilder::InsertAfter(Instruction* instruction)
	{
		return insert_block->GetInstructions().InsertAfter(instruction, insert_point);
	}

	Value* IRBuilder::InsertAfter(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) InsertAfter(I);
		return nullptr;
	}

	GlobalVariable* IRBuilder::CreateString(std::string_view str, IRModule* module)
	{
		if (!module) module = &insert_block->GetParent()->GetModule();
		ConstantString* string_constant = Create<ConstantString>(ctx, str);
		//todo create unique name
		GlobalVariable* GV = Create<GlobalVariable>(string_constant->GetType(), *module, Linkage::Internal, string_constant, true);
		return GV;
	}

	ConstantInt* IRBuilder::GetInt64(int64 value) const
	{
		return ctx.GetInt64(value);
	}

	ConstantInt* IRBuilder::GetInt8(int8 value) const
	{
		return ctx.GetInt8(value);
	}

	ConstantInt* IRBuilder::GetTrueValue() const
	{
		return ctx.GetTrueValue();
	}

	ConstantInt* IRBuilder::GetFalseValue() const
	{
		return ctx.GetFalseValue();
	}

	IRIntType* IRBuilder::GetInt8Type() const
	{
		return ctx.GetIntegerType(1);
	}

	IRIntType* IRBuilder::GetInt64Type() const
	{
		return ctx.GetIntegerType(8);
	}

	IRFloatType* IRBuilder::GetFloatType() const
	{
		return ctx.GetFloatType();
	}

	IRVoidType* IRBuilder::GetVoidType() const
	{
		return ctx.GetVoidType();
	}

	IRPtrType* IRBuilder::GetPtrType(IRType* type)
	{
		return ctx.GetPointerType(type);
	}

	BranchInst* IRBuilder::CreateBranch(BasicBlock* destination)
	{
		return Insert(Create<BranchInst>(destination));
	}

	StoreInst* IRBuilder::CreateStore(Value* val, Value* ptr)
	{
		return Insert(Create<StoreInst>(val, ptr));
	}

	LoadInst* IRBuilder::CreateLoad(IRType* type, Value* ptr)
	{
		return Insert(Create<LoadInst>(type, ptr));
	}

	AllocaInst* IRBuilder::CreateAlloca(IRType* type, Value* array_size)
	{
		return Insert(Create<AllocaInst>(type, array_size));
	}

	ReturnInst* IRBuilder::CreateRetVoid()
	{
		return Insert(Create<ReturnInst>(ctx));
	}

	ReturnInst* IRBuilder::CreateRet(Value* V)
	{
		return Insert(Create<ReturnInst>(ctx, V));
	}

	UnaryOperator* IRBuilder::CreateUnaryOp(UnaryOpcode opcode, Value* op)
	{
		return Insert(Create<UnaryOperator>(opcode, op));
	}

	BinaryOperator* IRBuilder::CreateBinaryOp(BinaryOpcode opcode, Value* op1, Value* op2)
	{
		return Insert(Create<BinaryOperator>(opcode, op1, op2));
	}

	CmpInst* IRBuilder::CreateCmp(CmpPredicate predicate, Value* lhs, Value* rhs)
	{
		return Insert(Create<CmpInst>(predicate, lhs, rhs));
	}

	NoopInstruction* IRBuilder::CreateNoop()
	{
		return Insert(Create<NoopInstruction>());
	}

	template<typename InstTy> requires std::is_base_of_v<Instruction, InstTy>
	InstTy* IRBuilder::Insert(InstTy* inst)
	{
		Insert((Instruction*)inst);
		return inst;
	}
}

