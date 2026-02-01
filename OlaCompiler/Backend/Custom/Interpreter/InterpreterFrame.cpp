#include "InterpreterFrame.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"

namespace ola
{
	InterpreterFrame::InterpreterFrame(Function* func, std::vector<InterpreterValue> const& args)
		: function(func)
	{
		for (Uint64 i = 0; i < func->GetArgCount() && i < args.size(); ++i)
		{
			Argument* arg = func->GetArg(static_cast<Uint32>(i));
			value_map[arg] = args[i];
		}
	}

	void InterpreterFrame::SetValue(Value* v, InterpreterValue val)
	{
		value_map[v] = val;
	}

	InterpreterValue InterpreterFrame::GetValue(Value* v) const
	{
		auto it = value_map.find(v);
		if (it != value_map.end())
		{
			return it->second;
		}
		return InterpreterValue::MakeVoid();
	}

	Bool InterpreterFrame::HasValue(Value* v) const
	{
		return value_map.find(v) != value_map.end();
	}

	void InterpreterFrame::SetCurrentBlock(BasicBlock* bb)
	{
		previous_block = current_block;
		current_block = bb;
	}
}
