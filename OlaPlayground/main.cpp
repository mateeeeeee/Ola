#include "Core/Types.h"
#include "Core/Macros.h"
#include "Core/Log.h"
#include "Compiler/CompileRequest.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"

using namespace ola;

template<typename T, Uint32 N>
constexpr Uint32 ArraySize(T(&arr)[N])
{
	return N;
}

int main()
{
	ola::LogInit();
	ola::CompileRequest compile_request{};
	Char const* argv[] = { "-i", "test", "--nollvm", "--directory", OLA_PLAYGROUND_PATH"Test" };
	if (compile_request.Parse(ArraySize(argv), const_cast<Char**>(argv)) >= 0)
	{
		ola::Int compile_result = ola::Compile(compile_request);
		return compile_result;
	}
	ola::LogDestroy();
	return 0;
}