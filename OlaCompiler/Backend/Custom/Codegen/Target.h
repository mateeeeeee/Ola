#pragma once
#include <list>
#include <vector>
#include <string_view>

namespace ola
{
	class IRType;
	class Instruction;
	class CallInst;
	class ReturnInst;
	class MIRInstruction;
	class MIRFunction;

	class TargetDataLayout
	{
	public:
		virtual ~TargetDataLayout() = default;

		virtual bool   IsLittleEndian() const = 0;
		virtual uint64 GetBuiltinAlignment(IRType const* type) const = 0;
		virtual uint64 GetPointerSize() const = 0;
		virtual uint64 GetCodeAlignment() const = 0;
		virtual uint64 GetStorageAlignment() const = 0;
	};

	enum OperandFlag : uint32
	{
		OperandFlagNone = 0,
		OperandFlagUse = 1 << 0,
		OperandFlagDef = 1 << 1
	};
	enum InstFlag : uint32
	{
		InstFlagNone = 0,
		InstFlagTerminator = 1 << 0,
		InstFlagBranch = 1 << 1,
		InstFlagCall = 1 << 2,
	};
	class InstInfo
	{
		static constexpr uint32 MAX_OPERANDS = 7;
	public:
		InstInfo() = default;

		bool HasOpFlag(uint32 idx, OperandFlag flag) const
		{
			OLA_ASSERT(idx < operand_count);
			return (operand_flags[idx] & flag) == flag;
		}
		bool HasInstFlag(InstFlag flag) const
		{
			return (instruction_flag & flag) == flag;
		}
		uint32 GetOperandCount() const { return operand_count; }

		void SetOperandCount(uint32 _operand_count)
		{
			operand_count = _operand_count;
		}
		void SetOpFlag(uint32 idx, OperandFlag flag);
		void SetInstFlag(InstFlag inst_flag);
	private:
		uint32 operand_count = 0;
		OperandFlag operand_flags[MAX_OPERANDS] = {};
		InstFlag instruction_flag = InstFlagNone;
	};

	class TargetInstInfo
	{
	public:
		virtual ~TargetInstInfo() = default;
		virtual InstInfo GetInstInfo(uint32 opcode) const = 0;
		InstInfo GetInstInfo(MIRInstruction const& inst) const;
	};

	class TargetRegisterInfo
	{
	public:
		virtual ~TargetRegisterInfo() = default;

		virtual uint32 GetStackPointerRegister() const = 0;
		virtual uint32 GetFramePointerRegister() const = 0;
		virtual uint32 GetReturnRegister() const = 0;
		virtual std::vector<uint32> const& GetIntegerRegisters() const = 0;
		virtual std::vector<uint32> const& GetFPRegisters() const = 0;
		virtual bool IsCallerSaved(uint32) const = 0;
		virtual bool IsCalleeSaved(uint32) const = 0;
	};

	class LoweringContext;
	struct InstLegalizeContext
	{
		MIRInstruction& instruction;
		std::list<MIRInstruction>& instructions;
		std::list<MIRInstruction>::iterator instruction_iterator;
	};
	class TargetISelInfo
	{
	public:
		virtual ~TargetISelInfo() = default;

		virtual bool LowerInstruction(Instruction*, LoweringContext&) const = 0;
		virtual void LegalizeInstruction(InstLegalizeContext&, LoweringContext&) const = 0;
	};

	class TargetFrameInfo
	{
	public:
		virtual ~TargetFrameInfo() = default;

		virtual void EmitCall(CallInst* CI, LoweringContext& ctx) const = 0;
		virtual void EmitPrologue(MIRFunction& MF, LoweringContext& ctx) const = 0;
		virtual void EmitEpilogue(MIRFunction& MF, LoweringContext& ctx) const = 0;
		virtual void ReserveShadowSpace(MIRFunction& MF, LoweringContext& ctx) const = 0;
		virtual void EmitReturn(ReturnInst* RI, LoweringContext& ctx) const = 0;
	};

	class MIRModule;
	class Target
	{
	public:
		virtual ~Target() = default;
		virtual TargetDataLayout const& GetDataLayout() const = 0;
		virtual TargetInstInfo const& GetInstInfo() const = 0;
		virtual TargetRegisterInfo const& GetRegisterInfo() const = 0;
		virtual TargetISelInfo const& GetISelInfo() const = 0;
		virtual TargetFrameInfo const& GetFrameInfo() const = 0;
		virtual void EmitAssembly(MIRModule& M, std::string_view file) const = 0;
	};
}