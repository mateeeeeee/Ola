#include "LLVMUtils.h"
#include "Core/Log.h"
#include "llvm/IR/Verifier.h"

namespace ola
{
	Bool VerifyLLVMModule(llvm::Module& module)
	{
		std::string error_msg;
		llvm::raw_string_ostream error_stream(error_msg);
		if (llvm::verifyModule(module, &error_stream))
		{
			error_stream.flush();
			OLA_ERROR("Module verification failed: {}", error_msg);
			return false;
		}
		return true;
	}

}
