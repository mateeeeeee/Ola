#pragma once
#include <string>
#include <memory>
#include "ICodegen.h"

namespace wave
{
	struct AST;

	class LLVMCodegen : public ICodegen
	{
	public:
		explicit LLVMCodegen(std::string_view output_file);
		~LLVMCodegen();

		virtual void Generate(AST* ast) override;

	private:
		std::string output_file;
	};

}