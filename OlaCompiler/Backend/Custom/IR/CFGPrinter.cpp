#include <fstream>
#include "CFGPrinter.h"
#include "CFG.h"
#include "GlobalValue.h"

namespace ola
{
	void CFGPrinter::Print(Function const* F, CFG const& cfg)
	{
		if (!F->IsDeclaration())
		{
			output.clear();
			name_manager.ClearLocals();

			EmitLn(R"(digraph "CFG for '{} function" {{
			label="CFG for '{} function";
			)", F->GetName(), F->GetName());

			PrintFunction(F, cfg);
			EmitLn("}}");

			std::string file_name(F->GetName());
			file_name += ".dot";
			std::ofstream dot_stream(file_name);
			dot_stream << output;
		}
	}

	void CFGPrinter::PrintFunction(Function const* F, CFG const& cfg)
	{
		for (BasicBlock const& BB : F->Blocks())
		{
			Emit("Node{}[shape = record, color = \"#b70d28ff\", style = filled,  fillcolor = \"#b70d2870\", label = \"{{ \n", static_cast<const void*>(&BB));
			use_line_break = true;
			PrintBasicBlock(BB);
			use_line_break = false;
			EmitLn("}}\"];\n");

			for (BasicBlock const* succ : cfg.GetSuccessors(&BB))
			{
				EmitLn(R"(Node{}->Node{})", static_cast<const void*>(&BB), static_cast<const void*>(succ));
			}
			EmitLn("");
		}
	}

}
