#pragma once
#include <string>

namespace wave
{
	struct AST;

	class LLVMIRGenerator
	{
	public:
		explicit LLVMIRGenerator(std::string_view output_file);
		~LLVMIRGenerator();

		void Generate(AST const* ast);

	private:
		std::string output_file;
	};

}