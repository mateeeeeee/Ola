#include "IRVerifier.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "BasicBlock.h"
#include "Instruction.h"
#include "IRType.h"
#include "Utility/RTTI.h"
#include <format>

namespace ola
{
	void IRVerifier::Error(std::string msg)
	{
		errors.push_back({ std::move(msg) });
	}

	Bool IRVerifier::Verify(IRModule const& module)
	{
		errors.clear();
		for (GlobalValue* gv : module.Globals())
		{
			if (Function const* fn = dyn_cast<Function>(gv))
			{
				if (!fn->IsDeclaration())
				{
					VerifyFunction(*fn);
				}
			}
		}
		return !HasErrors();
	}

	Bool IRVerifier::Verify(Function const& function)
	{
		errors.clear();
		VerifyFunction(function);
		return !HasErrors();
	}

	void IRVerifier::VerifyFunction(Function const& function)
	{
		if (function.Empty())
		{
			return;
		}

		for (auto const& block : function)
		{
			VerifyBlock(function, block);
		}
	}

	void IRVerifier::VerifyBlock(Function const& function, BasicBlock const& block)
	{
		VerifyTerminator(function, block);
		for (auto const& inst : block)
		{
			VerifyInstruction(function, inst);
		}
	}

	void IRVerifier::VerifyTerminator(Function const& function, BasicBlock const& block)
	{
		Instruction const* term = block.GetTerminator();
		if (!term)
		{
			Error(std::format("function '{}': block {} has no terminator",
				function.GetName(), block.GetIndex()));
			return;
		}

		Bool found_terminator_before_end = false;
		for (auto it = block.begin(); it != block.end(); ++it)
		{
			auto next = it;
			++next;
			if (it->IsTerminator() && next != block.end())
			{
				found_terminator_before_end = true;
				break;
			}
		}
		if (found_terminator_before_end)
		{
			Error(std::format("function '{}': block {} has instructions after terminator",
				function.GetName(), block.GetIndex()));
		}
	}

	void IRVerifier::VerifyInstruction(Function const& function, Instruction const& inst)
	{
		if (isa<BranchInst>(&inst))
		{
			VerifyBranch(function, inst);
		}
		else if (isa<PhiInst>(&inst))
		{
			VerifyPhi(function, inst);
		}
		else if (inst.IsBinaryOp())
		{
			VerifyBinaryOp(inst);
		}
		else if (isa<CallInst>(&inst))
		{
			VerifyCall(inst);
		}
	}

	void IRVerifier::VerifyBranch(Function const& function, Instruction const& inst)
	{
		BranchInst const& branch = *cast<BranchInst>(&inst);
		BasicBlock* true_target = branch.GetTrueTarget();
		if (!true_target)
		{
			Error(std::format("function '{}': branch has null true target",
				function.GetName()));
		}
		if (branch.IsConditional())
		{
			BasicBlock* false_target = branch.GetFalseTarget();
			if (!false_target)
			{
				Error(std::format("function '{}': conditional branch has null false target",
					function.GetName()));
			}
			if (!branch.GetCondition())
			{
				Error(std::format("function '{}': conditional branch has null condition",
					function.GetName()));
			}
		}
	}

	void IRVerifier::VerifyPhi(Function const& function, Instruction const& inst)
	{
		PhiInst const& phi = *cast<PhiInst>(&inst);
		if (phi.GetNumIncomingValues() == 0)
		{
			Error(std::format("function '{}': phi node has no incoming values",
				function.GetName()));
			return;
		}

		for (Uint32 i = 0; i < phi.GetNumIncomingValues(); ++i)
		{
			Value* val = phi.GetIncomingValue(i);
			if (!val)
			{
				Error(std::format("function '{}': phi node has null incoming value at index {}",
					function.GetName(), i));
				continue;
			}
			if (val->GetType() != phi.GetType())
			{
				Error(std::format("function '{}': phi node incoming value type mismatch at index {}",
					function.GetName(), i));
			}
		}
	}

	void IRVerifier::VerifyBinaryOp(Instruction const& inst)
	{
		if (inst.GetNumOperands() != 2)
		{
			Error(std::format("{}: expected 2 operands, got {}",
				inst.GetOpcodeName(), inst.GetNumOperands()));
			return;
		}

		Value* lhs = inst.GetOperand(0);
		Value* rhs = inst.GetOperand(1);
		if (!lhs || !rhs)
		{
			Error(std::format("{}: null operand", inst.GetOpcodeName()));
			return;
		}
		if (lhs->GetType() != rhs->GetType())
		{
			Error(std::format("{}: operand type mismatch", inst.GetOpcodeName()));
		}
	}

	void IRVerifier::VerifyCall(Instruction const& inst)
	{
		CallInst const& call = *cast<CallInst>(&inst);
		Value* callee = call.GetCallee();
		if (!callee)
		{
			Error("call: null callee");
		}
	}
}
