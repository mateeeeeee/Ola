#pragma once
#include <string>
#include <vector>

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

		void AddGlobalVar(GlobalVariable* gvar)
		{
			global_vars.push_back(gvar);
		}
		void AddFunction(IRFunction* func)
		{
			functions.push_back(func);
		}

		std::vector<GlobalVariable*> const& GetData() const { return global_vars; }
		std::vector<IRFunction*>     const& GetCode() const { return functions; }

		void PrintIR(std::string_view filename)
		{

		}

	private:
		IRContext& context;
		std::string module_id;
		std::vector<GlobalVariable*> global_vars;
		std::vector<IRFunction*> functions;
	};

}

