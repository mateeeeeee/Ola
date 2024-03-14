#pragma once
#include <string>

namespace ola
{

	class IRContext;
	class IRType;
	class BasicBlock;

	enum class ValueKind : uint8
	{
		Instruction,
		Global,
		Constant,
		Argument
	};

	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
		virtual ~Value() = default;

		OLA_NODISCARD ValueKind GetKind() const { return kind; }
		OLA_NODISCARD IRType* GetType() const { return type; }
		OLA_NODISCARD IRContext& GetContext() const;

		bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		OLA_NODISCARD bool IsGlobal() const 
		{
			return kind == ValueKind::Global;
		}
		OLA_NODISCARD bool IsConstant() const
		{
			return kind == ValueKind::Constant;
		}
		OLA_NODISCARD bool IsInstruction() const 
		{
			return kind == ValueKind::Instruction;
		}
		OLA_NODISCARD bool IsArgument() const 
		{
			return kind == ValueKind::Argument;
		}

		OLA_NODISCARD virtual bool IsUndefined() const
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