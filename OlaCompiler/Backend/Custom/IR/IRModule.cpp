#include <fstream>
#include "IRModule.h"
#include "IRType.h"
#include "GlobalValue.h"
#include "IRPrinter.h"

namespace ola
{

	IRModule::IRModule(IRContext& context, std::string_view module_id) : context(context), module_id(module_id)
	{
	}

	IRModule::~IRModule()
	{
		for (GlobalValue* GV : globals) delete GV;
	}

	
	void IRModule::EmitIR(std::string_view filename) const
	{
		std::ofstream ir_stream(filename.data());
		IRPrinter ir_printer(ir_stream);
		ir_printer.PrintModule(*this);
	}

}

