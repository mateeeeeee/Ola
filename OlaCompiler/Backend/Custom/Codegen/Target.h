#pragma once
#include <list>
#include <vector>
#include <string>
#include <string_view>

namespace ola
{
	class IRType;
	class Instruction;
	class CallInst;
	class ReturnInst;
	class MachineInstruction;
	class MachineFunction;

	class TargetDataLayout
	{
	public:
		virtual ~TargetDataLayout() = default;

		virtual Bool   IsLittleEndian() const = 0;
		virtual Uint64 GetBuiltinAlignment(IRType const* type) const = 0;
		virtual Uint64 GetPointerSize() const = 0;
		virtual Uint64 GetCodeAlignment() const = 0;
		virtual Uint64 GetStorageAlignment() const = 0;
	};

	enum OperandFlag : Uint32
	{
		OperandFlagNone = 0,
		OperandFlagUse = 1 << 0,
		OperandFlagDef = 1 << 1
	};
	enum InstFlag : Uint32
	{
		InstFlagNone = 0,
		InstFlagTerminator = 1 << 0,
		InstFlagBranch = 1 << 1,
		InstFlagCall = 1 << 2,
	};
	class InstInfo
	{
		static constexpr Uint32 MAX_OPERANDS = 7;
	public:
		InstInfo() = default;

		Bool HasOpFlag(Uint32 idx, OperandFlag flag) const
		{
			OLA_ASSERT(idx < operand_count);
			return (operand_flags[idx] & flag) == flag;
		}
		Bool HasInstFlag(InstFlag flag) const
		{
			return (instruction_flag & flag) == flag;
		}
		Uint32 GetOperandCount() const { return operand_count; }

		void SetOperandCount(Uint32 _operand_count)
		{
			operand_count = _operand_count;
		}
		void SetOpFlag(Uint32 idx, OperandFlag flag);
		void SetInstFlag(InstFlag inst_flag);
	private:
		Uint32 operand_count = 0;
		OperandFlag operand_flags[MAX_OPERANDS] = {};
		InstFlag instruction_flag = InstFlagNone;
	};

	class TargetInstInfo
	{
	public:
		virtual ~TargetInstInfo() = default;
		virtual InstInfo GetInstInfo(Uint32 opcode) const = 0;
		virtual std::string GetInstName(Uint32 opcode) const = 0;
		InstInfo GetInstInfo(MachineInstruction const& inst) const;
	};

	class TargetRegisterInfo
	{
	public:
		virtual ~TargetRegisterInfo() = default;

		virtual Uint32 GetStackPointerRegister() const = 0;
		virtual Uint32 GetFramePointerRegister() const = 0;
		virtual Uint32 GetGPScratchRegister() const = 0;
		virtual Uint32 GetFPScratchRegister() const = 0;
		virtual Uint32 GetReturnRegister() const = 0;
		virtual std::vector<Uint32> const& GetGPRegisters() const = 0;
		virtual std::vector<Uint32> GetGPCallerSavedRegisters() const = 0;
		virtual std::vector<Uint32> GetGPCalleeSavedRegisters() const = 0;
		virtual std::vector<Uint32> const& GetFPRegisters() const = 0;
		virtual std::vector<Uint32> GetFPCallerSavedRegisters() const = 0;
		virtual std::vector<Uint32> GetFPCalleeSavedRegisters() const = 0;
		virtual Bool IsCallerSaved(Uint32) const = 0;
		virtual Bool IsCalleeSaved(Uint32) const = 0;
	};

	class MachineContext;
	struct InstLegalizeContext
	{
		TargetRegisterInfo const& target_reg_info;
		MachineInstruction& instruction;
		std::list<MachineInstruction>& instructions;
		std::list<MachineInstruction>::iterator instruction_iterator;
	};
	class TargetISelInfo
	{
	public:
		virtual ~TargetISelInfo() = default;

		virtual Bool LowerInstruction(Instruction*, MachineContext&) const = 0;
		virtual void LegalizeInstruction(InstLegalizeContext&, MachineContext&) const = 0;
		virtual void PostLegalizeInstruction(InstLegalizeContext&) const = 0;
	};

	class TargetFrameInfo
	{
	public:
		virtual ~TargetFrameInfo() = default;

		virtual void EmitCall(CallInst* CI, MachineContext& ctx) const = 0;
		virtual void EmitPrologue(MachineFunction& MF, MachineContext& ctx) const = 0;
		virtual void EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const = 0;
		virtual void EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const = 0;
		virtual void EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const = 0;
		virtual void EmitReturn(ReturnInst* RI, MachineContext& ctx) const = 0;
	};

	class MachineModule;
	class Target
	{
	public:
		virtual ~Target() = default;
		virtual TargetDataLayout const& GetDataLayout() const = 0;
		virtual TargetInstInfo const& GetInstInfo() const = 0;
		virtual TargetRegisterInfo const& GetRegisterInfo() const = 0;
		virtual TargetISelInfo const& GetISelInfo() const = 0;
		virtual TargetFrameInfo const& GetFrameInfo() const = 0;
		virtual void EmitAssembly(MachineModule& M, std::string_view file) const = 0;
	};
}