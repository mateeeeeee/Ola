#pragma once


namespace llvm
{
	class Module;
}

namespace ola
{
	Bool VerifyLLVMModule(llvm::Module& module);
}