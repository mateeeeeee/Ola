#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	ola::LogInit();
	ola::CompileRequest compile_request{};
	if (compile_request.Parse(argc, argv) >= 0)
	{
		ola::Int compile_result = ola::Compile(compile_request);
		return compile_result;
	}
	ola::LogDestroy();
	return 0;
}
