#include "Core/Types.h"
#include "Core/Defines.h"
#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"

using namespace ola;

static constexpr Char const* BACKEND = "--nollvm";
static constexpr Char const* OPT_LEVEL = "--O2";

Int main()
{
	OLA_LOG_INIT();
	CompileRequest compile_request{};
	Char const* argv[] = { "-i", "test", OPT_LEVEL, BACKEND, "--timeout",  "--emit-asm", "--emit-mir", "--emit-ir", "--directory", OLA_PLAYGROUND_PATH"Test"};
	if (compile_request.Parse(OLA_ARRAYSIZE(argv), const_cast<Char**>(argv)))
	{
		Int compile_result = Compile(compile_request);
		return compile_result;
	}
	return 0;
}