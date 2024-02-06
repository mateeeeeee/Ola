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
		Jump,
		Return
	};

	class MachineInst : public IListNode<MachineInst>
	{
		friend class MachineFunction;
		friend class MachineBasicBlock;

	public:
		explicit MachineInst(MachineOpCode opcode);
		OLA_NONCOPYABLE(MachineInst)
		~MachineInst();

		MachineBasicBlock const* GetParent() const { return parent; }
		MachineBasicBlock* GetParent() { return parent; }

		MachineFunction const* GetFunction() const;
		MachineFunction* GetFunction();

		MachineOpCode GetOpCode() const { return opcode; }
		uint32 GetOpCount() const;

		template<uint32 i>
		MachineOperand& Op()
		{
			return operands[i];
		}
		template<uint32 i>
		MachineOperand const& Op() const
		{
			return operands[i];
		}
		MachineOperand const& GetOperand(uint32 i) const;
		MachineOperand& GetOperand(uint32 i);
		void AddOperand(MachineOperand const& op);

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