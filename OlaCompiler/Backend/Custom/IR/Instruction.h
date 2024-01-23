#pragma once
#include "User.h"

namespace ola
{
	class Instruction : public User, public IListNode<Instruction>
	{
	public:

		OLA_NONCOPYABLE(Instruction)
		~Instruction()
		{
			RemoveFromParent();
		}

		BasicBlock const* GetParent() const { return parent; }
		BasicBlock* GetParent() { return parent; }
		Function const* GetFunction() const;
		Function* GetFunction() { return const_cast<Function*>(static_cast<const Instruction*>(this)->GetFunction()); }
		IRModule& GetModule() const;

		void RemoveFromParent();

		void Insert(Instruction* position);
		void InsertAfter(Instruction* position);
		void Insert(BasicBlock* bb, Instruction* position);
		void InsertAfter(BasicBlock* bb, Instruction* position);
		void Insert(BasicBlock* bb);

		bool IsTerminator() const { return false; }
		bool IsUnaryOp()	const { return false; }
		bool IsBinaryOp()	const { return false; }
		bool IsModulo()		const { return false; }
		bool IsShift()		const { return false; }
		bool IsCast()		const { return false; }

		static bool ClassOf(Value const* V)
		{
			switch (V->GetKind())
			{
			case ValueKind::Alloca:
				return true;
			default:
				return false;
			}
			return false;
		}

	protected:
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, BasicBlock* parent = nullptr) : User(kind, type, num_operands), parent(parent)
		{
			if (parent) Insert(parent);
		}
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, Instruction* position) : User(kind, type, num_operands), parent(nullptr)
		{
			if (position) Insert(position);
		}

	private:
		BasicBlock* parent;

	private:
		void SetParent(BasicBlock* bb);
	};

}