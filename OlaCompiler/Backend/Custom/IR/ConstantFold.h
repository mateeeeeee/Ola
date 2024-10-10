#pragma once
#include <concepts>
#include "Instruction.h"


namespace ola
{
	Value* TryConstantFold_BinaryInst(Opcode opcode, Value* lhs, Value* rhs);
	Value* TryConstantFold_UnaryInst(Opcode opcode, Value* val);
	Value* TryConstantFold_CompareInst(Opcode opcode, Value* lhs, Value* rhs);
	Value* TryConstantFold_GetElementPtrInst(Value* base, std::span<Value*> indices);
	Value* TryConstantFold_SelectInst(Value* predicate, Value* lhs, Value* rhs);
	Value* TryConstantFold_BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target);

	template <typename InstructionT, typename... Args> requires std::is_constructible_v<InstructionT, Args...>
	constexpr Value* TryConstantFold(Args&&... args)
	{
		if constexpr (std::is_same_v<InstructionT, BinaryInst>)
		{
			return TryConstantFold_BinaryInst(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same_v<InstructionT, UnaryInst>)
		{
			return TryConstantFold_UnaryInst(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same_v<InstructionT, CompareInst>)
		{
			return TryConstantFold_CompareInst(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same_v<InstructionT, GetElementPtrInst>)
		{
			return TryConstantFold_GetElementPtrInst(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same_v<InstructionT, SelectInst>)
		{
			return TryConstantFold_SelectInst(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same_v<InstructionT, BranchInst> && sizeof...(Args) == 3)
		{
			return TryConstantFold_BranchInst(std::forward<Args>(args)...);
		}
		return nullptr;
	}

}