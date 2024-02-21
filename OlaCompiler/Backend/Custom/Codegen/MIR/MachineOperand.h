#pragma once
#include <bit>
#include <string>
#include "MIRFwd.h"

namespace ola
{
	enum MachineOperandKind : uint8
	{
		MO_Register,
		MO_IntImmediate,
		MO_FPImmediate,
		MO_MemoryRef, 
		MO_FrameIndex,
		MO_GlobalVariable
	};

	struct MemoryRef
	{
		uint32 base_reg = -1;
		int64 offset = 0;
		uint32 index_reg = -1;
		int32 scale;
	};

	class MachineOperand
	{
		friend class MachineInst;

	public:
		MachineOperand() : memory(), kind(MO_Register) {}
		OLA_DEFAULT_COPYABLE_MOVABLE(MachineOperand)
		explicit MachineOperand(MachineOperandKind kind) : kind(kind), memory() {}

		MachineOperandKind GetKind() const { return kind; }

		void SetParent(MachineInst* _parent) { parent = _parent; }
		MachineInst* GetParent() { return parent; }
		MachineInst const* GetParent() const { return parent; }

		bool IsReg() const { return kind == MO_Register; }
		bool IsFPImmediate() const { return kind == MO_FPImmediate; }
		bool IsIntImmediate() const { return kind == MO_IntImmediate; }
		bool IsMemoryRef() const { return kind == MO_MemoryRef; }
		bool IsFrameIndex() const { return kind == MO_FrameIndex; }
		bool IsGlobalVariable() const { return kind == MO_GlobalVariable; }

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
			return std::bit_cast<double>(fp_imm);
		}
		void SetFPImm(double v)
		{
			OLA_ASSERT(IsFPImmediate());
			fp_imm = std::bit_cast<uint64>(v);
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

		MemoryRef GetMemoryRef() const
		{
			OLA_ASSERT(IsMemoryRef());
			return memory;
		}
		void SetMemoryRef(uint32 base_reg, int64 offset, uint32 index_reg = -1, int32 scale = 1)
		{
			OLA_ASSERT(IsMemoryRef());
			memory.base_reg = base_reg;
			memory.offset = offset;
			memory.index_reg = index_reg;
			memory.scale = scale;
		}

		void SetGlobalVariable(std::string_view name)
		{
			global_variable_name = name;
		}
		std::string_view GetGlobalVariable() const { return global_variable_name; }

		void SetFrameOffset(int32 _frame_offset)
		{
			OLA_ASSERT(IsFrameIndex());
			frame_offset = _frame_offset;
		}
		int32 GetFrameOffset() const 
		{ 
			OLA_ASSERT(IsFrameIndex());
			return frame_offset; 
		}

		void SetDef(bool _is_def)
		{
			OLA_ASSERT(IsReg());
			is_def = _is_def;
		}
		void SetUse(bool _is_use)
		{
			SetDef(!_is_use);
		}
		bool IsDef() const { return is_def; }
		bool IsUse() const 
		{
			OLA_ASSERT(IsReg());
			return !is_def;
		}

	private:
		MachineOperandKind kind;
		MachineInst* parent = nullptr;
		union
		{
			uint32 reg;
			int64  int_imm;
			uint64 fp_imm;
			MemoryRef memory;
			int32 frame_offset;
		};
		std::string global_variable_name;

		bool is_def = false;
	};

}