#pragma once
#include "IRType.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include "GlobalValue.h"
#include "Constant.h"

namespace ola
{

	Use::Use(Value* val, Instruction* user) : value(val), user(user)
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

	Use::~Use()
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

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

	void Instruction::InsertBefore(BasicBlock* block, Instruction* pos)
	{

	}

	bool Instruction::CanBeOperand() const
	{
		return true;
	}

	LoadInst::LoadInst(Value* address) 
		: Instruction( InstructionID::Load, cast<IRPtrType>(address->GetType())->GetPointeeType(), {address})
	{
		OLA_ASSERT(isa<IRPtrType>(address->GetType()));
	}

	StoreInst::StoreInst(Value* address, Value* value) : Instruction(InstructionID::Store, IRVoidType::Get(value->GetContext()), { address, value })
	{
	}

	BranchInst::BranchInst(IRContext& C, BasicBlock* target) : Instruction(InstructionID::Branch, IRVoidType::Get(C)) , true_target(target), false_target(nullptr)
	{
	}

	BranchInst::BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target) : Instruction(InstructionID::Branch, IRVoidType::Get(condition->GetContext()), { condition }),
		true_target(true_target), false_target(false_target)
	{
	}

	ReturnInst::ReturnInst(IRContext& C) : Instruction(InstructionID::Ret, IRVoidType::Get(C), {})
	{
	}

	ReturnInst::ReturnInst(Value* ret_value) : Instruction(InstructionID::Ret, IRVoidType::Get(ret_value->GetContext()), { ret_value })
	{
	}

	SwitchInst::SwitchInst(Value* val, BasicBlock* default_block) : Instruction{ InstructionID::Switch, IRVoidType::Get(val->GetContext()), { val } }, default_block{ default_block }
	{

	}

	CallInst::CallInst(Value* callee, std::span<Value*> args) : Instruction(InstructionID::Call, cast<IRFuncType>(callee->GetType())->GetReturnType(), {})
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

	AllocaInst::AllocaInst(IRType* type, Value* array_size /*= nullptr*/) : Instruction(InstructionID::Alloca, IRPtrType::Get(type), { array_size }), allocated_type(type)
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
		: Instruction{ InstructionID::GetElementPtr, IRPtrType::Get(GetValueType(base, indices)), {} }
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


}