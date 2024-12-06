#pragma once
#include <memory>
#include <string>
#include "LLVMOptimizer.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace ola
{
	struct AST;
	class LLVMIRVisitor;

	class LLVMIRGenContext
	{
	public:
		explicit LLVMIRGenContext(std::string_view file_name);
		~LLVMIRGenContext();

		void Generate(AST const* ast);
		llvm::Module& GetModule() { return module; }

	private:
		llvm::LLVMContext context;
		llvm::Module module;
	};

}