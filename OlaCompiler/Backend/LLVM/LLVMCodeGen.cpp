#include <format>
#include "LLVMCodeGen.h"

namespace ola
{
	void LLVMCodeGen::Generate(std::string_view assembly_file)
	{
		std::string compile_cmd = std::format("clang -S {} -o {} -masm=intel", ir_file, assembly_file);
		system(compile_cmd.c_str());
	}
}

