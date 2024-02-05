#pragma once
#include "Value.h"
#include "Use.h"

namespace ola
{

	Value::Value(ValueKind kind, IRType* type) : kind(kind), type(type)
	{

	}
	Value::~Value() = default;

	uint64 Value::UseSize() const
	{
		return uses.Size();
	}

	void Value::AddUse(Use* u)
	{
		uses.PushBack(u);
	}

	void Value::RemoveUse(Use* u)
	{
		uses.Remove(u);
	}

	void Value::ReplaceAllUseWith(Value* v)
	{
		for (auto& use : uses) use.Set(v);
	}


}