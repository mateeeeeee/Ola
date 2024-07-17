#pragma once
#include <iosfwd>

namespace ola
{
	class IRModule;
	void PrintIRModule(std::ostream&, IRModule const&);
}