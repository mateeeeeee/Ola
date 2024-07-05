#pragma once
#include "IRContext.h"
#include "IRModule.h"

namespace ola
{
	struct AST;

	class IRGenContext
	{
	public:
		explicit IRGenContext(std::string_view filename);
		~IRGenContext();

		void Generate(AST const* ast);
		void EmitIR(std::string_view output_file);

		IRModule& GetModule() { return module; }

	private:
		IRContext context;
		IRModule  module;
	};
}