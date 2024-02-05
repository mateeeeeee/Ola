#pragma once
#include <string>
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRContext;
	class Function;
	class GlobalVariable;

	class IRModule
	{
	public:
		IRModule(IRContext& context, std::string_view module_id);
		OLA_NONCOPYABLE_NONMOVABLE(IRModule)
		~IRModule();

		IRContext& GetContext() const { return context; }
		std::string_view GetModuleId() const
		{
			return module_id;
		}

		void AddVariable(GlobalVariable* gvar);
		void RemoveVariable(GlobalVariable* gvar);
		void AddFunction(Function* func);
		void RemoveFunction(Function* func);

		IList<GlobalVariable> const& GetVariableList() const;
		IList<Function>     const& GetFunctionList() const;

		void PrintIR(std::string_view filename);

	private:
		IRContext& context;
		std::string module_id;
		IList<GlobalVariable> variables;
		IList<Function> functions;
	};

}

