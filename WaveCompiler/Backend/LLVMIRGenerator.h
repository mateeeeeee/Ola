#pragma once
#include <memory>
#include <string>
#include "LLVMOptimizer.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace wave
{
	struct AST;
	class LLVMVisitor;

	class LLVMIRGenerator
	{
	public:
		explicit LLVMIRGenerator(std::string_view file_name);
		~LLVMIRGenerator();

		void Generate(AST const* ast);
		void Optimize(OptimizationLevel);
		void PrintIR(std::string_view output_file);

	private:
		llvm::LLVMContext context;
		llvm::Module module;

	private:
		static bool VerifyModule(llvm::Module&);
	};

}