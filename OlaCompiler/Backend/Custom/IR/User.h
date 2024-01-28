#pragma once
#include <vector>
#include "Value.h"
#include "Utility/IteratorRange.h"

namespace ola
{

	class User : public Value
	{
	public:
		~User();
		Use* const* GetOperandList() const;
		Use** GetOperandList();
		uint32 GetNumOperands() const;

		Value* GetOperand(uint32 i) const;
		void SetOperand(uint32 i, Value* val);

		Use const& GetOperandUse(uint32 i) const;
		Use& GetOperandUse(uint32 i);

		using OpIterator = Use**;
		using ConstOpIterator = Use* const*;
		using OpRange = IteratorRange<OpIterator>;
		using ConstOpRange = IteratorRange<ConstOpIterator>;

		OpIterator      OpBegin() { return GetOperandList(); }
		ConstOpIterator OpBegin()  const { return GetOperandList(); }
		OpIterator      OpEnd() { return GetOperandList() + GetNumOperands(); }
		ConstOpIterator OpEnd()    const { return GetOperandList() + GetNumOperands(); }
		OpRange			Operands() { return OpRange(OpBegin(), OpEnd()); }
		ConstOpRange	Operands() const { return ConstOpRange(OpBegin(), OpEnd()); }

		void DropAllReferences();

		bool ReplaceUsesOfWith(Value* from, Value* to);

	private:
		std::vector<Use*> operands;

	protected:
		User(ValueKind kind, IRType* type, uint32 num_operands);


		void ResizeOperands(uint32 op_count);

		template <uint32 Idx, typename U>
		static Use& OpFrom(U const* that)
		{
			return *that->operands[Idx];
		}

		template <uint32 Idx>
		Use& Op()
		{
			return OpFrom<Idx>(this);
		}
		template <uint32 Idx>
		Use const& Op() const
		{
			return OpFrom<Idx>(this);
		}
	};

}