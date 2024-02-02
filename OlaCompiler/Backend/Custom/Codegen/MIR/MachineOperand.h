#pragma once
#include "MIRFwd.h"

namespace ola
{
	enum MachineOperandKind : uint8
	{
		MO_Register,
		MO_IntImmediate,
		MO_FPImmediate,
		MO_MemoryRef
	};
	class MachineOperand
	{
		friend class MachineInst;
	public:
		explicit MachineOperand(MachineOperandKind kind) : kind(kind), address(0) {}

		MachineOperandKind GetKind() const { return kind; }

		MachineInst* GetParent() { return parent; }
		MachineInst const* GetParent() const { return parent; }

		uint32 GetOperandIdx() const
		{
			return -1;
		}

		bool IsReg() const { return kind == MO_Register; }
		bool IsFPImmediate() const { return kind == MO_FPImmediate; }
		bool IsIntImmediate() const { return kind == MO_IntImmediate; }
		bool IsMemoryRef() const { return kind == MO_MemoryRef; }

		int64 GetImm() const 
		{
			OLA_ASSERT(IsIntImmediate());
			return int_imm;
		}
		void SetImm(int64 v)
		{
			OLA_ASSERT(IsIntImmediate());
			int_imm = v;
		}
		double GetFPImm() const
		{
			OLA_ASSERT(IsFPImmediate());
			return fp_imm;
		}
		void SetFPImm(double v)
		{
			OLA_ASSERT(IsFPImmediate());
			fp_imm = v;
		}

		uint32 GetReg() const
		{
			OLA_ASSERT(IsReg());
			return reg;
		}
		void SetReg(uint32 r)
		{
			OLA_ASSERT(IsReg());
			reg = r;
		}

		uint64 GetAddress() const
		{
			OLA_ASSERT(IsMemoryRef());
			return address;
		}
		void SetAddress(uint64 addr)
		{
			OLA_ASSERT(IsMemoryRef());
			address = addr;
		}

	private:
		MachineOperandKind kind;
		MachineInst* parent = nullptr;
		union
		{
			uint32 reg;
			int64  int_imm;
			double fp_imm;
			uint64 address;
		};
	};
}