#pragma once
#include <span>
#include "Value.h"
#include "User.h"

namespace ola
{
	class Constant : public User
	{
	public:
		OLA_NONCOPYABLE(Constant)
		~Constant() = default;

		static Constant* GetNullValue(IRType* Ty)
		{
			return nullptr;
		}
		static Constant* GetIntegerValue(IRType* Ty, uint64 V)
		{
			return nullptr;
		}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() >= ValueKind_ConstantInt && V->GetKind() <= ValueKind_Poison;
		}

	protected:
		Constant(ValueKind kind, IRType* ty, uint32 num_ops) : User(kind, ty, num_ops) {}
	};

	class ConstantData : public Constant 
	{
		friend class Constant;
	public:

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() >= ValueKind_ConstantInt && V->GetKind() <= ValueKind_ConstantFloat;
		}

	protected:
		ConstantData(ValueKind kind, IRType* ty) : Constant(kind, ty, 0) {}
	};

	class ConstantInt final : public ConstantData 
	{
	public:
		ConstantInt(IRIntType* type, int64 V) : ConstantData(ValueKind_ConstantInt, type), value(V), bitwidth(type->GetWidth() * 8)
		{}
		~ConstantInt() = default;

		IRIntType* GetIntegerType() const
		{
			return cast<IRIntType>(GetType());
		}
		int64 GetValue() const { return value; }
		uint32 GetBitWidth() const { return bitwidth; }

		static bool ClassOf(const Value* V) 
		{
			return V->GetKind() == ValueKind_ConstantInt;
		}

	private:
		int64 value;
		uint32 bitwidth;
	};

	class ConstantFloat final : public ConstantData 
	{
	public:
		ConstantFloat(IRFloatType* type, double V) : ConstantData(ValueKind_ConstantFloat, type), value(V) {}
		~ConstantFloat() = default;

		double GetValue() const { return value; }
		static bool ClassOf(const Value* V) 
		{
			return V->GetKind() == ValueKind_ConstantFloat;
		}

	private:
		double value;
	};

	class ConstantString final : public ConstantData
	{
	public:
		ConstantString(IRContext& C, std::string_view str) : ConstantData(ValueKind_ConstantFloat, IRArrayType::Get(IRIntType::Get(C, 1), str.size() + 1)), value(str) {}
		~ConstantString() = default;

		std::string_view GetValue() const { return value; }
		static bool ClassOf(const Value* V)
		{
			return V->GetKind() == ValueKind_ConstantString;
		}

	private:
		std::string value;
	};

	class ConstantAggregate : public Constant 
	{
	public:

		static bool ClassOf(const Value* V) 
		{
			return V->GetKind() >= ValueKind_ConstantArray &&
				   V->GetKind() <= ValueKind_ConstantStruct;
		}

	protected:
		ConstantAggregate(ValueKind kind, IRType* type, std::span<Constant*> values)
			: Constant(kind, type, values.size())
		{
			for (uint32 i = 0; i <= values.size(); ++i)
			{
				if (IRStructType* ST = dyn_cast<IRStructType>(type))
				{
					OLA_ASSERT_MSG(ST->GetMemberType(i) == values[i]->GetType(), "Calling a function with a bad signature!");
				}
				else if (IRArrayType* AT = dyn_cast<IRArrayType>(type))
				{
					OLA_ASSERT_MSG(AT->GetBaseType() == values[i]->GetType(), "Calling a function with a bad signature!");
				}
				SetOperand(i, values[i]);
			}
		}
	};

	class ConstantArray final : public ConstantAggregate 
	{
	public:
		ConstantArray(IRArrayType* type, std::span<Constant*> values)
			: ConstantAggregate(ValueKind_ConstantArray, type, values)
		{}

		template<typename... Cs> requires (std::is_base_of_v<Constant, Cs> && ...)
		ConstantArray(IRArrayType* type, Cs*... constants) 
			: ConstantArray(type, std::span<Constant*>{constants...})
		{}

		IRArrayType* GetArrayType() const 
		{
			return cast<IRArrayType>(GetType());
		}

		static bool ClassOf(const Value* V) 
		{
			return V->GetKind() == ValueKind_ConstantArray;
		}
	};

	class ConstantStruct final : public ConstantAggregate
	{
	public:

		ConstantStruct(IRStructType* type, std::span<Constant*> values)
			: ConstantAggregate(ValueKind_ConstantStruct, type, values)
		{}

		template<typename... Cs> requires (std::is_base_of_v<Constant, Cs> && ...)
		ConstantStruct(IRStructType* type, Cs*... constants) : ConstantStruct(type, std::span<Constant*>{constants...})
		{}

		IRStructType* GetStructType() const
		{
			return cast<IRStructType>(GetType());
		}

		static bool ClassOf(const Value* V)
		{
			return V->GetKind() == ValueKind_ConstantStruct;
		}
	};

	class ConstantPointerNull final : public ConstantData 
	{
	public:
		explicit ConstantPointerNull(IRPtrType* type) : ConstantData(ValueKind_ConstantPointerNull, type) {}

		IRPtrType* GetPointerType() const 
		{
			return cast<IRPtrType>(GetType());
		}

		static bool ClassOf(Value const* V) 
		{
			return V->GetKind() == ValueKind_ConstantPointerNull;
		}
	};

	class UndefValue : public ConstantData 
	{
		
	public:
		explicit UndefValue(IRType* type) : ConstantData(ValueKind_Undef, type) {}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Undef ||
				   V->GetKind() == ValueKind_Poison;
		}

	protected:
		UndefValue(ValueKind kind, IRType* type) : ConstantData(kind, type) {}
	};

	class PoisonValue final : public UndefValue 
	{
	public:
		explicit PoisonValue(IRType* type) : UndefValue(ValueKind_Poison, type) {}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Poison;
		}
	};
}