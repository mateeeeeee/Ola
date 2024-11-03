#pragma once
#include <string>

namespace ola
{

	class IRContext;
	class IRType;
	class BasicBlock;

	enum class ValueKind : Uint8
	{
		Instruction,
		Constant,
		Argument,
		BasicBlock
	};

	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
		virtual ~Value() = default;

		OLA_NODISCARD ValueKind GetKind() const { return kind; }
		OLA_NODISCARD IRType* GetType() const { return type; }
		OLA_NODISCARD IRContext& GetContext() const;

		Bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		OLA_NODISCARD Bool IsConstant() const
		{
			return kind == ValueKind::Constant;
		}
		OLA_NODISCARD Bool IsInstruction() const 
		{
			return kind == ValueKind::Instruction;
		}
		OLA_NODISCARD Bool IsArgument() const 
		{
			return kind == ValueKind::Argument;
		}
		OLA_NODISCARD Bool IsBasicBlock() const
		{
			return kind == ValueKind::BasicBlock;
		}

		OLA_NODISCARD virtual Bool IsUndefined() const
		{
			return false;
		}
		
	protected:
		Value(ValueKind kind, IRType* type = nullptr) : kind(kind), type(type)
		{}

	private:
		ValueKind kind;
		IRType* type;
		std::string name;
	};
}