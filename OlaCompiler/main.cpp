#include <filesystem>
#include <cstdio>
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"


int main(int argc, char** argv)
{
	ola::CompileRequest compile_request{};
	compile_request.Parse(argc, argv);
	ola::int32 exit_code = ola::Compile(compile_request);
	return exit_code;
}
