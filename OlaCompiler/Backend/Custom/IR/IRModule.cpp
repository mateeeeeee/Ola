#include <fstream>
#include "IRModule.h"
#include "IRType.h"
#include "GlobalValue.h"
#include "IRWriter.h"

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
		std::ofstream ola_ir_stream(filename.data());
		IRWriter ir_writer(ola_ir_stream);
		ir_writer.PrintModule(*this);
	}

}

