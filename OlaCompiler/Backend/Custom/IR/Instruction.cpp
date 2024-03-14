#pragma once
#include "Instruction.h"

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

}