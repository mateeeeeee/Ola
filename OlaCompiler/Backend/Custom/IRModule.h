#pragma once
#include <string>
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRContext;
	class IRFunction;
	class GlobalVariable;

	class IRModule
	{
	public:
		IRModule(IRContext& context, std::string_view module_id) : context(context), module_id(module_id) {}
		OLA_NONCOPYABLE_NONMOVABLE(IRModule)
		~IRModule() {}

		IRContext& GetContext() const { return context; }
		std::string_view GetModuleId() const
		{
			return module_id;
		}

		void AddVariable(GlobalVariable* gvar);
		void RemoveVariable(GlobalVariable* gvar);
		void AddFunction(IRFunction* func);
		void RemoveFunction(IRFunction* func);

		IList<GlobalVariable> const& GetVariableList() const;
		IList<IRFunction>     const& GetFunctionList() const;

		void PrintIR(std::string_view filename);

	private:
		IRContext& context;
		std::string module_id;
		IList<GlobalVariable> variables;
		IList<IRFunction> functions;
	};

}

