#pragma once
#include <vector>
#include "MIRFwd.h"
#include "MachineOperand.h"
#include "Utility/IntrusiveList.h"
#include "Utility/IteratorRange.h"

namespace ola
{
	enum class MachineOpCode : uint16
	{
		Invalid,
		Mov,
		Load,
		Store,
		Jump,
		Return,
		Alloca,
		Add,
		Sub,
		Mul,
		Div,
		Neg
	};

	class MachineBasicBlock;
	class MachineFunction;

	class MachineInst : public IListNode<MachineInst>
	{
		friend MachineFunction;
		friend MachineBasicBlock;

	public:
		explicit MachineInst(MachineOpCode opcode);
		MachineInst(MachineOpCode opcode, MachineBasicBlock* _parent) : MachineInst(opcode) 
		{
			parent = _parent;
		}
		OLA_NONCOPYABLE(MachineInst)
		~MachineInst();

		void SetInstrNumber(uint32 _instr_number) { instr_number = _instr_number; }
		uint32 GetInstrNumber() const { return instr_number; }
		void SetParent(MachineBasicBlock* _parent) { parent = _parent; }
		MachineBasicBlock const* GetParent() const { return parent; }
		MachineBasicBlock* GetParent() { return parent; }

		MachineFunction const* GetFunction() const;
		MachineFunction* GetFunction();

		MachineOpCode GetOpCode() const { return opcode; }
		uint32 GetNumOperands() const;

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

		void SetReg(uint32 r)
		{
			reg = r;
		}
		uint32 GetReg() const
		{
			return reg;
		}

	private:
		MachineBasicBlock* parent;
		uint32 instr_number = -1;
		std::vector<MachineOperand> operands;
		MachineOpCode opcode;
		uint32 reg = -1;
	};
}