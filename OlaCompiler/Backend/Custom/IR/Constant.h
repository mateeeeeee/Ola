#pragma once
#include <vector>
#include <span>
#include "Instruction.h"
#include "IRType.h"
#include "Utility/RTTI.h"

namespace ola
{
	enum class ConstantID : Uint8
	{ 
		Global, Integer, Float, String, Offset, Array, Struct, Undef
	};

	class Constant : public TrackableValue
	{
	public:
		OLA_NONCOPYABLE(Constant)
		~Constant() = default;

		ConstantID GetConstantID() const { return constant_id; }

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Constant;
		}

		static Constant* GetNullValue(IRType* Ty);

	protected:
		ConstantID constant_id;

	protected:
		Constant(ConstantID constant_id, IRType* type) : TrackableValue(ValueKind::Constant, type), constant_id(constant_id) {}
	};

	class ConstantInt final : public Constant
	{
	public:
		ConstantInt(IRType* type, Int64 V) : Constant(ConstantID::Integer, type), value(V), bitwidth(GetIntegerType()->GetWidth() * 8)
		{
			OLA_ASSERT(isa<IRIntType>(type));
		}
		ConstantInt(IRIntType* type, Int64 V) : Constant(ConstantID::Integer, type), value(V), bitwidth(type->GetWidth() * 8) {}

		IRIntType* GetIntegerType() const
		{
			return cast<IRIntType>(GetType());
		}
		Int64 GetValue() const { return value; }
		Uint32 GetBitWidth() const { return bitwidth; }

		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Integer;
		}
	private:
		Int64 value;
		Uint32 bitwidth;
	};

	class ConstantFloat final : public Constant
	{
	public:
		ConstantFloat(IRFloatType* type, Float64 V) : Constant(ConstantID::Float, type), value(V) {}
		ConstantFloat(IRType* type, Float64 V) : Constant(ConstantID::Float, type), value(V)
		{
			OLA_ASSERT(isa<IRFloatType>(type));
		}
		~ConstantFloat() = default;

		Float64 GetValue() const { return value; }

		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Float;
		}

	private:
		Float64 value;
	};

	class ConstantString final : public Constant
	{
	public:
		ConstantString(IRContext& C, std::string_view str) : Constant(ConstantID::String, IRArrayType::Get(IRIntType::Get(C, 1), str.size() + 1)), value(str) {}

		std::string_view GetValue() const { return value; }
		
		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::String;
		}
	private:
		std::string value;
	};

	class ConstantAggregate : public Constant
	{
	public:
		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Struct || C->GetConstantID() == ConstantID::Array;
		}

		std::vector<Constant*> const& Values() const 
		{
			return aggregate_values;
		}
		std::vector<Constant*>& Values() 
		{
			return aggregate_values;
		}

	protected:
		std::vector<Constant*> aggregate_values;

	protected:
		ConstantAggregate(ConstantID constant_id, IRType* type, std::span<Constant*> values) : Constant(constant_id, type)
		{
			aggregate_values.resize(values.size());
			for (Uint32 i = 0; i < values.size(); ++i)
			{
				if (IRStructType* ST = dyn_cast<IRStructType>(type))
				{
					OLA_ASSERT_MSG(ST->GetMemberType(i) == values[i]->GetType(), "Aggregate member type mismatch!");
				}
				else if (IRArrayType* AT = dyn_cast<IRArrayType>(type))
				{
					Bool const types_match = AT->GetElementType() == values[i]->GetType();
					Bool const both_pointers = AT->GetElementType()->IsPointer() && values[i]->GetType()->IsPointer();
					OLA_ASSERT_MSG(types_match || both_pointers, "Aggregate member type mismatch!");
				}
				aggregate_values[i] = values[i];
			}
		}
	};

	class ConstantArray final : public ConstantAggregate
	{
	public:
		ConstantArray(IRArrayType* type, std::span<Constant*> values)
			: ConstantAggregate(ConstantID::Array, type, values) {}

		template<typename... Cs> requires (std::is_base_of_v<Constant, Cs> && ...)
		ConstantArray(IRArrayType* type, Cs*... constants)
			: ConstantArray(type, std::span<Constant*>{constants...}) {}

		IRArrayType* GetArrayType() const
		{
			return cast<IRArrayType>(GetType());
		}

		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Array;
		}
	};

	class ConstantStruct final : public ConstantAggregate
	{
	public:
		ConstantStruct(IRStructType* type, std::span<Constant*> values)
			: ConstantAggregate(ConstantID::Struct, type, values)
		{}

		template<typename... Cs> requires (std::is_base_of_v<Constant, Cs> && ...)
		ConstantStruct(IRStructType* type, Cs*... constants) : ConstantStruct(type, std::span<Constant*>{constants...})
		{}

		IRStructType* GetStructType() const
		{
			return cast<IRStructType>(GetType());
		}

		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Struct;
		}
	};

	class UndefValue : public Constant
	{
	public:
		explicit UndefValue(IRType* type) : Constant(ConstantID::Undef, type) {}

		static Bool ClassOf(Value const* V)
		{
			return isa<Constant>(V) && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Undef;
		}
	};
}