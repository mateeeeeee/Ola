#pragma once
#include "IRContext.h"
#include "IRModule.h"

namespace ola::ir
{
	struct AST;

	class IRGen
	{
	public:
		explicit IRGen(std::string_view filename);
		~IRGen();

		void Generate(AST const* ast);
		void PrintIR(std::string_view output_file);

	private:
		IRContext context;
		IRModule  module;
	};
}