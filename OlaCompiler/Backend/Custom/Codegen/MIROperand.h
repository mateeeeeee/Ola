#pragma once
#include <string>
#include <variant>

namespace ola
{
	constexpr uint32 VIRTUAL_REG_BEGIN = 0b0101U << 28;
	constexpr uint32 STACK_OBJECT_BEGIN = 0b1010U << 28;
	constexpr uint32 INVALID_REG = 0b1100U << 28;

	inline constexpr bool IsISAReg(uint32 r) 
	{
		return r < VIRTUAL_REG_BEGIN;
	}
	inline constexpr bool IsVirtualReg(uint32 r) 
	{
		return (r & VIRTUAL_REG_BEGIN) == VIRTUAL_REG_BEGIN;
	}
	inline constexpr bool IsStackObject(uint32 r) 
	{
		return (r & STACK_OBJECT_BEGIN) == STACK_OBJECT_BEGIN;
	}

	enum class MIROperandType : uint32
	{
		Unknown,
		Bool,
		Int8,
		Int16,
		Int32,
		Int64,
		Float32,
		Float64,
		Ptr,
		Other
	};

	inline constexpr bool IsIntegerType(MIROperandType type)
	{
		return type <= MIROperandType::Int64;
	}
	inline constexpr bool IsFPType(MIROperandType type)
	{
		return type == MIROperandType::Float32 || type == MIROperandType::Float64;
	}
	inline constexpr uint32 GetOperandSize(MIROperandType type)
	{
		switch (type)
		{
		case MIROperandType::Int8:
			return 1;
		case MIROperandType::Int16:
			return 2;
		case MIROperandType::Int32:
			return 4;
		case MIROperandType::Int64:
			return 8;
		case MIROperandType::Float32:
			return 4;
		case MIROperandType::Float64:
			return 8;
		}
		OLA_ASSERT(false);
		return 0;
	}

	enum MIRRegisterFlag : uint32 
	{
		MIRRegisterFlag_None = 0,
		MIRRegisterFlag_Dead = 1 << 1,
	};

	struct MIRRegister
	{
		uint32 reg;
		MIRRegisterFlag flag = MIRRegisterFlag_None;

		bool operator==(const MIRRegister& rhs) const 
		{
			return reg == rhs.reg;
		}
		bool operator!=(const MIRRegister& rhs) const 
		{
			return reg != rhs.reg;
		}
	};

	class MIRRelocable;
	class MIROperand
	{
	public:
		constexpr MIROperand() = default;
		template <typename T>
		constexpr MIROperand(T const& x, MIROperandType type) : storage{ x }, type{ type } {}
		OLA_DEFAULT_COPYABLE_MOVABLE(MIROperand)
		~MIROperand() = default;

		auto const& GetStorage() const
		{
			return storage;
		}
		MIROperandType GetType() const
		{
			return type;
		}

		bool IsReg() const { return std::holds_alternative<MIRRegister>(storage); }
		MIRRegister GetReg() const
		{
			return std::get<MIRRegister>(storage);
		}

		bool IsImmediate() const { return std::holds_alternative<int64>(storage); }
		int64 GetImmediate() const
		{
			return std::get<int64>(storage);
		}

		bool IsRelocable() const { return std::holds_alternative<MIRRelocable*>(storage); }
		MIRRelocable* GetRelocable() const
		{
			return std::get<MIRRelocable*>(storage);
		}

		bool IsUnused() const 
		{
			return std::holds_alternative<std::monostate>(storage);
		}

		bool operator==(MIROperand const& rhs) const
		{
			return storage == rhs.storage;
		}
		bool operator!=(MIROperand const& rhs) const
		{
			return storage != rhs.storage;
		}

		template <typename T>
		static MIROperand Immediate(T val, MIROperandType type)
		{
			static_assert(std::is_integral_v<T> || std::is_enum_v<T>);
			return MIROperand(static_cast<int64>(val), type);
		}
		static MIROperand ISAReg(uint32 reg, MIROperandType type)
		{
			OLA_ASSERT(IsISAReg(reg));
			return MIROperand(MIRRegister{ reg }, type);
		}
		static MIROperand VirtualReg(uint32 reg, MIROperandType type)
		{
			return MIROperand(MIRRegister{ reg + VIRTUAL_REG_BEGIN }, type);
		}
		static MIROperand StackObject(uint32 reg, MIROperandType type) 
		{
			return MIROperand(MIRRegister{ reg + STACK_OBJECT_BEGIN }, type);
		}
		static MIROperand InvalidReg() 
		{
			return MIROperand(MIRRegister{ INVALID_REG }, MIROperandType::Other);
		}
		static MIROperand Relocable(MIRRelocable* val) 
		{
			return MIROperand(val, MIROperandType::Other);
		}

		uint64 GetHash() const;

	private:
		std::variant<std::monostate, MIRRelocable*, int64, MIRRegister> storage;
		MIROperandType type = MIROperandType::Unknown;
	};

	inline bool IsOperandVReg(MIROperand const& operand)
	{
		return operand.IsReg() && IsVirtualReg(operand.GetReg().reg);
	}
	inline bool IsOperandStackObject(MIROperand const& operand)
	{
		return operand.IsReg() && IsStackObject(operand.GetReg().reg);
	}
}

namespace std 
{
	template <>
	struct hash<ola::MIRRegister> 
	{
		size_t operator()(ola::MIRRegister const& reg) const 
		{
			return hash<uint32_t>{}(reg.reg);
		}
	};

	template <>
	struct hash<ola::MIROperand>
	{
		size_t operator()(ola::MIROperand const& op) const
		{
			return op.GetHash();
		}
	};
}