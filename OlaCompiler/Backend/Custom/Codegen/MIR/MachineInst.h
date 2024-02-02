#pragma once
#include <vector>
#include "MIRFwd.h"
#include "Utility/IntrusiveList.h"
#include "Utility/IteratorRange.h"

namespace ola
{
	enum class MachineOpCode
	{
		Add,
		Subtract,
		Load,
		Store,
		Jump
	};

	class MachineInst : IListNode<MachineInst>
	{
		friend class MachineFunction;
		friend class MachineBasicBlock;

	public:
		explicit MachineInst(MachineOpCode opcode) : opcode(opcode)
		{

		}
		OLA_NONCOPYABLE(MachineInst)
		~MachineInst() {}

		MachineBasicBlock const* GetParent() const { return parent; }
		MachineBasicBlock* GetParent() { return parent; }

		MachineFunction const* GetMFunction() const
		{
			return nullptr;
		}
		MachineFunction* GetMFunction() 
		{
			return const_cast<MachineFunction*>(static_cast<const MachineInst*>(this)->GetMFunction());
		}

		MachineOpCode GetOpCode() const { return opcode; }
		uint32 GetOpCount() const { return operands.size(); }

		MachineOperand const& GetOperand(uint32 i) const 
		{
			return operands[i];
		}
		MachineOperand& GetOperand(uint32 i) 
		{
			return operands[i];
		}

		void AddOperand(MachineOperand const& op)
		{
			operands.push_back(op);
		}

		auto OperandsBegin() { return operands.begin(); }
		auto OperandsEnd() { return operands.end(); }
		auto OperandsBegin() const { return operands.begin(); }
		auto OperandsEnd() const { return operands.end(); }
		auto Operands() 
		{
			return MakeRange(OperandsBegin(), OperandsEnd());
		}
		auto Operands() const 
		{
			return MakeRange(OperandsBegin(), OperandsEnd());
		}

	private:
		MachineBasicBlock* parent;
		std::vector<MachineOperand> operands;
		MachineOpCode opcode;

	private:
		void SetParent(MachineBasicBlock* P) { parent = P; }
	};
}