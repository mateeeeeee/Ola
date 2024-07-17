#pragma once
#include <string>
#include <vector>
#include <memory>

namespace ola
{
	class IRContext;
	class Function;
	class GlobalVariable;
	class GlobalValue;

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

		void AddGlobal(GlobalValue* GV)
		{
			globals.push_back(GV);
		}
		std::vector<GlobalValue*> const& Globals() const { return globals; }

		void EmitIR(std::string_view filename) const;

	private:
		IRContext& context;
		std::string module_id;
		std::vector<GlobalValue*> globals;
	};

}

