#include "User.h"
#include "Use.h"

namespace ola
{

	User::~User()
	{
		for (Use* op : operands) delete op;
	}

	Use** User::GetOperandList()
	{
		return const_cast<Use**>(static_cast<const User*>(this)->GetOperandList());
	}

	Use* const* User::GetOperandList() const
	{
		return operands.data();
	}

	uint32 User::GetNumOperands() const
	{
		return (uint32)operands.size();
	}

	Value* User::GetOperand(uint32 i) const
	{
		return *GetOperandList()[i];
	}

	void User::SetOperand(uint32 i, Value* val)
	{
		*GetOperandList()[i] = val;
	}

	Use& User::GetOperandUse(uint32 i)
	{
		return *GetOperandList()[i];
	}

	Use const& User::GetOperandUse(uint32 i) const
	{
		return *GetOperandList()[i];
	}

	void User::DropAllReferences()
	{
		for (Use* U : Operands()) U->Set(nullptr);
	}

	bool User::ReplaceUsesOfWith(Value* from, Value* to)
	{
		bool changed = false;
		if (from == to) return changed;
		for (uint32 i = 0, N = GetNumOperands(); i != N; ++i)
		{
			if (GetOperand(i) == from)
			{
				SetOperand(i, to);
				changed = true;
			}
		}
		return changed;
	}

	User::User(ValueKind kind, IRType* type, uint32 num_operands) : Value(kind, type)
	{
		operands.resize(num_operands);
		for (Use* op : operands) op = new Use(this);
	}

	void User::ResizeOperands(uint32 op_count)
	{
		for (Use* op : operands) delete op;
		operands.clear();
		operands.resize(op_count);
		for (Use* op : operands) op = new Use(this);
	}

}


