#include "x64Target.h"
#include "x64.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{

	class x64TargetDataLayout : public TargetDataLayout
	{
	public:
		virtual bool   IsLittleEndian() const override { return true; }
		virtual uint64 GetBuiltinAlignment(IRType const* type) const override
		{
			return type->GetSize();
		}
		virtual uint64 GetPointerSize() const override
		{
			return 8u;
		}
		virtual uint64 GetCodeAlignment() const override
		{
			return 8u;
		}
		virtual uint64 GetStorageAlignment() const override
		{
			return 8u;
		}
	};

	class x64TargetInstInfo : public TargetInstInfo
	{
	public:
		virtual InstInfo const& GetInstInfo(uint32 opcode) const override
		{
			InstInfo inst_info{};
			switch (opcode)
			{

			}
			return inst_info;
		}
	};

	class x64TargetISelInfo : public TargetISelInfo
	{

	public:
		virtual bool IsLegalInstruction(uint32) const override
		{
			return false;
		}

		virtual bool LowerInstruction(Instruction*, LoweringContext&) const override
		{
			return false;
		}


		virtual bool LegalizeInstruction(MIRInstruction&, LegalizeContext&) const override
		{
			return false;
		}

	};

	class x64TargetRegisterInfo : public TargetRegisterInfo
	{
	public:
		virtual uint32 GetStackPointerRegister() const override
		{
			return x64::RSP;
		}

		virtual uint32 GetFramePointerRegister() const override
		{
			return x64::RBP;
		}


		virtual uint32 GetReturnRegister() const override
		{
			return x64::RAX;
		}


		virtual std::vector<uint32> const& GetIntegerRegisters() const override
		{
			return {};
		}


		virtual std::vector<uint32> const& GetFPRegisters() const override
		{
			return {};
		}


		virtual bool IsCallerSaved(uint32) const override
		{
			return false;
		}


		virtual bool IsCalleeSaved(uint32) const override
		{
			return false;
		}

	};


	TargetDataLayout const& x64Target::GetDataLayout() const
	{
		static x64TargetDataLayout x64_target_data_layout{};
		return x64_target_data_layout;
	}

	TargetInstInfo const& x64Target::GetInstInfo() const
	{
		static x64TargetInstInfo x64_target_inst_info{};
		return x64_target_inst_info;
	}

	TargetRegisterInfo const& x64Target::GetRegisterInfo() const
	{
		static x64TargetRegisterInfo x64_target_reg_info{};
		return x64_target_reg_info;
	}

	TargetISelInfo const& x64Target::GetISelInfo() const
	{
		static x64TargetISelInfo x64_target_isel_info{};
		return x64_target_isel_info;
	}

}

