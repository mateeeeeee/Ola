#pragma once
#include "User.h"

namespace ola
{
	class Instruction : public User, public IListNode<Instruction>
	{
	public:

		OLA_NONCOPYABLE(Instruction)
		~Instruction()
		{
			RemoveFromParent();
		}

		BasicBlock const* GetParent() const { return parent; }
		BasicBlock* GetParent() { return parent; }
		Function const* GetFunction() const;
		Function* GetFunction() { return const_cast<Function*>(static_cast<const Instruction*>(this)->GetFunction()); }
		IRModule& GetModule() const;

		void RemoveFromParent();

		void Insert(Instruction* position);
		void InsertAfter(Instruction* position);
		void Insert(BasicBlock* bb, Instruction* position);
		void InsertAfter(BasicBlock* bb, Instruction* position);
		void Insert(BasicBlock* bb);

		bool IsTerminator() const;
		bool IsUnaryOp()	const;
		bool IsBinaryOp()	const;
		bool IsModulo()		const { return false; }
		bool IsShift()		const { return false; }
		bool IsCast()		const;

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() >= ValueKind_Call;
		}

	protected:
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, BasicBlock* parent = nullptr) : User(kind, type, num_operands), parent(parent)
		{
			if (parent) Insert(parent);
		}
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, Instruction* position) : User(kind, type, num_operands), parent(nullptr)
		{
			if (position) Insert(position);
		}

	private:
		BasicBlock* parent;

	private:
		void SetParent(BasicBlock* bb);
	};


	template<typename Derived> 
	class OpcodeConverter
	{
	protected:
		static auto ValueKindToOpcode(ValueKind kind)
		{
			using OpcodeType = typename Derived::OpcodeType;
			static constexpr ValueKind FirstValueKind = Derived::FirstValueKind;
			return (OpcodeType)(kind - FirstValueKind);
		}
		static ValueKind OpcodeToValueKind(auto opcode)
		{
			using OpcodeType = typename Derived::OpcodeType;
			static_assert(std::is_same_v<std::remove_cvref_t<decltype(opcode)>, OpcodeType>, "Opcode type mismatch");
			static constexpr ValueKind FirstValueKind = Derived::FirstValueKind;
			return (ValueKind)(opcode + FirstValueKind);
		}

	public:
		auto GetOpcode() const { return ValueKindToOpcode(static_cast<Derived const*>(this)->GetKind()); }
	};

#define OPCODE_CONVERTER_IMPL(_ClassName, _OpcodeType, _FirstValueKind) \
	friend class OpcodeConverter<_ClassName>; \
	static constexpr ValueKind FirstValueKind = _FirstValueKind; \
	using OpcodeType = _OpcodeType;
}