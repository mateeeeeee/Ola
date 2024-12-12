#include "Core/Types.h"
#include "Core/Macros.h"
#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"

using namespace ola;

template<typename T, Uint N>
constexpr Uint ArraySize(T(&arr)[N])
{
	return N;
}

int main()
{
	LogInit();
	CompileRequest compile_request{};
	Char const* argv[] = { "-i", "test", "--O0","--nollvm", "--print-domfrontier", "--emit-asm","--emit-ir", "--directory", OLA_PLAYGROUND_PATH"Test"};
	//Char const* argv[] = { "-i", "test", "--O3", "--domtree","--cfg", "--print-domfrontier", "--emit-asm","--emit-ir", "--directory", OLA_PLAYGROUND_PATH"Test"};
	if (compile_request.Parse(ArraySize(argv), const_cast<Char**>(argv)))
	{
		Int compile_result = Compile(compile_request);
		return compile_result;
	}
	LogDestroy();
	return 0;
}