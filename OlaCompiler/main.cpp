#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	ola::CompileRequest compile_request{};
	compile_request.Parse(argc, argv);
	return ola::Compile(compile_request);
}
