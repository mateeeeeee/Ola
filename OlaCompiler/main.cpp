#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	ola::LogInit();
	ola::CompileRequest compile_request{};
	compile_request.Parse(argc, argv);
	ola::Int compile_result = ola::Compile(compile_request);
	ola::LogDestroy();
	return compile_result;
}
