#pragma once
#include <string>
#include <variant>
#include <bit>

namespace ola
{
	constexpr Uint32 VIRTUAL_REG_BEGIN = 0b0101U << 28;
	constexpr Uint32 INVALID_REG = 0b1100U << 28;

	inline constexpr bool IsISAReg(Uint32 r) 
	{
		return r < VIRTUAL_REG_BEGIN;
	}
	inline constexpr bool IsVirtualReg(Uint32 r) 
	{
		return (r & VIRTUAL_REG_BEGIN) == VIRTUAL_REG_BEGIN;
	}

	enum class MachineType : Uint32
	{
		Unknown,
		Int8,
		Int64,
		Float64,
		Ptr,
		Other
	};

	inline constexpr bool IsIntegerType(MachineType type)
	{
		return type <= MachineType::Int64;
	}
	inline constexpr bool IsFPType(MachineType type)
	{
		return type == MachineType::Float64;
	}
	inline constexpr Uint32 GetOperandSize(MachineType type)
	{
		switch (type)
		{
		case MachineType::Int8:
			return 1;
		case MachineType::Int64:
			return 8;
		case MachineType::Float64:
			return 8;
		case MachineType::Ptr:
			//OLA_ASSERT_MSG(false, "Call TargetDataLayout::GetPointerSize");
			return 8;
		}
		OLA_ASSERT(false);
		return 0;
	}

	struct MachineRegister
	{
		Uint32 reg;

		bool operator==(const MachineRegister& rhs) const 
		{
			return reg == rhs.reg;
		}
		bool operator!=(const MachineRegister& rhs) const 
		{
			return reg != rhs.reg;
		}
	};

	struct MachineStackObject
	{
		Sint32 offset;

		bool operator==(MachineStackObject const& rhs) const
		{
			return offset == rhs.offset;
		}
		bool operator!=(MachineStackObject const& rhs) const
		{
			return offset != rhs.offset;
		}
	};

	class MachineRelocable;
	class MachineOperand
	{
	public:
		constexpr MachineOperand() = default;
		template <typename T>
		constexpr MachineOperand(T const& x, MachineType type) : storage{ x }, type{ type } {}
		OLA_DEFAULT_COPYABLE_MOVABLE(MachineOperand)
		~MachineOperand() = default;

		auto const& GetStorage() const
		{
			return storage;
		}
		MachineType GetType() const
		{
			return type;
		}
		void SetType(MachineType _type)
		{
			type = _type;
		}

		bool IsReg() const { return std::holds_alternative<MachineRegister>(storage); }
		MachineRegister GetReg() const
		{
			return std::get<MachineRegister>(storage);
		}
		MachineRegister& GetReg() 
		{ 
			return std::get<MachineRegister>(storage); 
		}

		bool IsStackObject() const
		{
			return std::holds_alternative<MachineStackObject>(storage);
		}
		Sint32 GetStackOffset() const
		{
			return std::get<MachineStackObject>(storage).offset;
		}

		bool IsImmediate() const { return std::holds_alternative<Sint64>(storage); }
		Sint64 GetImmediate() const
		{
			return std::get<Sint64>(storage);
		}

		bool IsRelocable() const { return std::holds_alternative<MachineRelocable*>(storage); }
		MachineRelocable* GetRelocable() const
		{
			return std::get<MachineRelocable*>(storage);
		}

		bool IsUnused() const 
		{
			return std::holds_alternative<std::monostate>(storage);
		}

		bool IsMemoryOperand() const
		{
			return IsStackObject() || IsRelocable();
		}

		bool operator==(MachineOperand const& rhs) const
		{
			return storage == rhs.storage;
		}
		bool operator!=(MachineOperand const& rhs) const
		{
			return storage != rhs.storage;
		}

		template <typename T>
		static MachineOperand Immediate(T val, MachineType type)
		{
			static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);
			if constexpr (std::is_floating_point_v<T>)
			{
				static_assert(std::is_same_v<T, Float64>);
				return MachineOperand(std::bit_cast<Sint64>(val), type);
			}
			else return MachineOperand(static_cast<Sint64>(val), type);
		}
		static MachineOperand ISAReg(Uint32 reg, MachineType type)
		{
			OLA_ASSERT(IsISAReg(reg));
			return MachineOperand(MachineRegister{ reg }, type);
		}
		static MachineOperand VirtualReg(Uint32 reg, MachineType type)
		{
			return MachineOperand(MachineRegister{ reg + VIRTUAL_REG_BEGIN }, type);
		}
		static MachineOperand StackObject(Sint32 offset, MachineType type) 
		{
			return MachineOperand(MachineStackObject{ offset }, type);
		}
		static MachineOperand InvalidReg() 
		{
			return MachineOperand(MachineRegister{ INVALID_REG }, MachineType::Other);
		}
		static MachineOperand Relocable(MachineRelocable* val) 
		{
			return MachineOperand(val, MachineType::Other);
		}

		Uint64 GetHash() const;

	private:
		std::variant<std::monostate, MachineRelocable*, Sint64, MachineRegister, MachineStackObject> storage;
		MachineType type = MachineType::Unknown;
	};

	inline bool IsOperandVReg(MachineOperand const& operand)
	{
		return operand.IsReg() && IsVirtualReg(operand.GetReg().reg);
	}
}

namespace std 
{
	template <>
	struct hash<ola::MachineRegister> 
	{
		size_t operator()(ola::MachineRegister const& reg) const 
		{
			return hash<uint32_t>{}(reg.reg);
		}
	};

	template <>
	struct hash<ola::MachineStackObject>
	{
		size_t operator()(ola::MachineStackObject const& so) const
		{
			return hash<int32_t>{}(so.offset);
		}
	};

	template <>
	struct hash<ola::MachineOperand>
	{
		size_t operator()(ola::MachineOperand const& op) const
		{
			return op.GetHash();
		}
	};
}