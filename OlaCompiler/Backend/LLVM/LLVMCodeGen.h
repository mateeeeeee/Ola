#pragma once
#include <string>

namespace ola
{
	class LLVMCodeGen
	{
	public:
		explicit LLVMCodeGen(std::string_view ir_file) : ir_file(ir_file) {}
		~LLVMCodeGen() = default;

		void Generate(std::string_view assembly_file);

	private:
		std::string ir_file;
	};
}