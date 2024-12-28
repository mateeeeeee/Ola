#include "Core/Types.h"
#include "Core/Macros.h"
#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"

#define NOLLVM 1

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
#if NOLLVM
	Char const* argv[] = { "-i", "test", "--O1","--nollvm", "--timeout", "--emit-asm","--emit-ir","--emit-mir", "--directory", OLA_PLAYGROUND_PATH"Test"};
#else
	Char const* argv[] = { "-i", "test", "--O1","--timeout",  "--emit-asm","--emit-ir", "--directory", OLA_PLAYGROUND_PATH"Test" };
#endif
	if (compile_request.Parse(ArraySize(argv), const_cast<Char**>(argv)))
	{
		Int compile_result = Compile(compile_request);
		return compile_result;
	}
	LogDestroy();
	return 0;
}