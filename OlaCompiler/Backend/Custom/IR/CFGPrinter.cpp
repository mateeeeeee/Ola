#include <fstream>
#include "CFGPrinter.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/CFGAnalysisPass.h"

namespace ola
{

	void CFGPrinter::PrintModule(IRModule const& M)
	{
		std::vector<GlobalValue*> const& globals = M.Globals();
		for (GlobalValue const* global : globals)
		{
			if (Function const* F = dyn_cast<Function>(global))
			{
				if (!F->IsDeclaration())
				{
					output.clear();
					name_manager.ClearLocals();
					PrintCFGPreamble(F->GetName());
					PrintFunction(F);
					EmitLn("}}");

					std::string file_name(F->GetName());
					file_name += ".dot";
					std::ofstream dot_stream(file_name);
					dot_stream << output;
				}
			}
		}
	}

	void CFGPrinter::PrintCFGPreamble(std::string_view function_name)
	{
		EmitLn(R"(digraph "CFG for '{} function" {{
			label="CFG for '{} function";
			)", function_name, function_name);
	}

	void CFGPrinter::PrintFunction(Function const* F)
	{
		CFGAnalysisPass cfg_analysis_pass;
		cfg_analysis_pass.RunOn(*F);
		CFG const& cfg = cfg_analysis_pass.GetResult();

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
