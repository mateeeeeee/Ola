#pragma once
#include <string>

namespace wave
{
	struct AST;

	class LLVMCodegen
	{
	public:
		explicit LLVMCodegen(std::string_view output_file);
		~LLVMCodegen();

		void Generate(AST const* ast);

	private:
		std::string output_file;
	};

}