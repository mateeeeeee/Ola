#include "Core/Types.h"
#include "Core/Macros.h"
#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"

#define NOLLVM 0

using namespace ola;


Int main()
{
	OLA_LOG_INIT();
	CompileRequest compile_request{};
#if NOLLVM
	Char const* argv[] = { "-i", "test", "--O1","--nollvm", "--emit-asm","--emit-ir","--emit-mir", "--directory", OLA_PLAYGROUND_PATH"Test"};
#else
	Char const* argv[] = { "-i", "test", "--O1","--timeout",  "--emit-asm","--emit-ir", "--directory", OLA_PLAYGROUND_PATH"Test" };
#endif
	if (compile_request.Parse(OLA_ARRAYSIZE(argv), const_cast<Char**>(argv)))
	{
		Int compile_result = Compile(compile_request);
		return compile_result;
	}
	return 0;
}