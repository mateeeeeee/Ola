#include "IRType.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include "GlobalValue.h"
#include "Constant.h"

namespace ola
{
	static char const* OpcodeNames[] = 
	{
		"none",

		"ret",
		"br",
		"switch",

		"load",
		"store",

		"add",
		"sub",
		"mul",
		"sdiv",
		"udiv",
		"srem",
		"urem",
		"neg",
		"not",
		"and",
		"or",
		"xor",
		"shl",
		"lshr",
		"ashr",

		"fadd",
		"fsub",
		"fmul",
		"fdiv",
		"fneg",
		"ffma",

		"icmp eq",
		"icmp ne",
		"icmp slt",
		"icmp sle",
		"icmp sgt",
		"icmp sge",
		"icmp ult",
		"icmp ule",
		"icmp ugt",
		"icmp uge",

		"fcmp oeq",
		"fcmp one",
		"fcmp olt",
		"fcmp ole",
		"fcmp ogt",
		"fcmp oge",
		"fcmp ueq",
		"fcmp une",
		"fcmp ult",
		"fcmp ule",
		"fcmp ugt",
		"fcmp uge",

		"sext",
		"zext",
		"signed trunc",
		"unsigned trunc",
		"bitcast",
		"f2u",
		"f2s",
		"u2f",
		"s2f",
		"fcast",

		"alloca",
		"gep",
		"select",
		"call",
		"phi"
	};


	Use::Use(Value* val, Instruction* user) : value(val), user(user)
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

	Use::~Use() {}

	void Use::Set(Value* V)
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->RemoveUse(this);
		}
		value = V;
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

	bool TrackableValue::ReplaceWith(Value* value)
	{
		return false;
	}

	bool TrackableValue::ReplaceWithInBlock(BasicBlock* block, Value* value)
	{
		return false;
	}

	char const* Instruction::GetOpcodeName() const
	{
		return OpcodeNames[(uint32)GetOpcode()];
	}

	IListIterator<Instruction> Instruction::InsertBefore(BasicBlock* BB, Instruction* I)
	{
		return InsertBefore(BB, I->GetIterator());
	}

	IListIterator<Instruction> Instruction::InsertBefore(BasicBlock* BB, IListIterator<Instruction> IT)
	{
		if (basic_block) 
		{
			basic_block->Instructions().Remove(this);
		}
		basic_block = BB;
		return BB->Instructions().Insert(IT, this);
	}

	bool Instruction::CanBeOperand() const
	{
		return true;
	}

	LoadInst::LoadInst(Value* address) 
		: Instruction( Opcode::Load, cast<IRPtrType>(address->GetType())->GetPointeeType(), {address})
	{
		OLA_ASSERT(isa<IRPtrType>(address->GetType()));
	}

	LoadInst::LoadInst(Value* address, IRType* type)
		: Instruction(Opcode::Load, type, { address })
	{
		OLA_ASSERT(isa<IRPtrType>(address->GetType()));
	}

	StoreInst::StoreInst(Value* value, Value* address) : Instruction(Opcode::Store, IRVoidType::Get(value->GetContext()), { value, address })
	{
	}

	BranchInst::BranchInst(IRContext& C, BasicBlock* target) 
		: Instruction(Opcode::Branch, IRVoidType::Get(C), { target }), true_target(target), false_target(nullptr)
	{
	}

	BranchInst::BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target) 
		: Instruction(Opcode::Branch, IRVoidType::Get(condition->GetContext()), { true_target, false_target, condition }),
		true_target(true_target), false_target(false_target)
	{
	}

	ReturnInst::ReturnInst(IRContext& C) : Instruction(Opcode::Ret, IRVoidType::Get(C), {})
	{
	}

	ReturnInst::ReturnInst(Value* ret_value) : Instruction(Opcode::Ret, IRVoidType::Get(ret_value->GetContext()), { ret_value })
	{
	}

	SwitchInst::SwitchInst(Value* val, BasicBlock* default_block) : Instruction{ Opcode::Switch, IRVoidType::Get(val->GetContext()), { val } }, default_block{ default_block }
	{

	}

	CallInst::CallInst(Value* callee, std::span<Value*> args) : Instruction(Opcode::Call, cast<Function>(callee)->GetReturnType(), {})
	{
		for (Value* arg : args) AddOperand(arg);
		AddOperand(callee);
	}

	Function* CallInst::GetCalleeAsFunction() const
	{
		if (Function* F = dyn_cast<Function>(GetCallee())) return F;
		else return nullptr;
	}

	Function* CallInst::GetCaller() const
	{
		return GetBasicBlock()->GetFunction();
	}

	AllocaInst::AllocaInst(IRType* type, Value* array_size /*= nullptr*/) : Instruction(Opcode::Alloca, IRPtrType::Get(type), { array_size }), allocated_type(type)
	{
	}

	IRPtrType* AllocaInst::GetPtrType() const
	{
		return cast<IRPtrType>(GetType());
	}

	IRType* GetElementPtrInst::GetValueType(Value* base, std::span<Value*> indices)
	{
		OLA_ASSERT(base->GetType()->IsPointerType());
		IRType* current_type = base->GetType();
		for (Value* index : indices)
		{
			if (index->GetType()->IsIntegerType()) 
			{
				if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type)) 
				{
					current_type = array_type->GetBaseType();
				}
				else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
				{
					current_type = pointer_type->GetPointeeType();
				}
				else OLA_ASSERT(false);
			}
			else if (auto offset = dyn_cast<ConstantOffset>(index))
			{
				OLA_ASSERT(isa<IRStructType>(current_type));
				current_type = cast<IRStructType>(current_type)->GetMemberType(offset->GetIndex());
			}
			else OLA_ASSERT(false);
		}
		return current_type;
	}

	GetElementPtrInst::GetElementPtrInst(Value* base, std::span<Value*> indices)
		: Instruction{ Opcode::GetElementPtr, IRPtrType::Get(GetValueType(base, indices)), {} }
	{
		for (Value* index : indices) AddOperand(index);
		AddOperand(base);
	}

	void PhiInst::AddIncoming(BasicBlock* block, Value* value)
	{
		OLA_ASSERT(GetType() == value->GetType());
		OLA_ASSERT(!incomings.contains(block));
		incomings.emplace(block, Use(value, nullptr));
		AddOperand(value);
	}


	CompareInst::CompareInst(Opcode id, Value* lhs, Value* rhs) : Instruction(id, IRIntType::Get(lhs->GetContext(), 1), {lhs, rhs})
	{
		uint32 id_int = (uint32)id;
		OLA_ASSERT(id_int >= (uint32)Opcode::CompareOpBegin && id_int <= (uint32)Opcode::CompareOpEnd);
		cmp = (CompareOp)(id_int - (uint32)Opcode::CompareOpBegin);
	}

}