#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	OLA_LOG_INIT();
	ola::CompileRequest compile_request{};
	if (compile_request.Parse(argc, argv))
	{
		ola::Int compile_result = ola::Compile(compile_request);
		return compile_result;
	}
	return 0;
}
