#pragma once
#include <iosfwd>
#include <string>
#include <format>

namespace ola
{
	class IRModule;
	class Function;
	class GlobalVariable;
	class BasicBlock;
	class IRType;

	class IRPrinter
	{
	public:
		explicit IRPrinter(std::ostream& os) : os(os) {}
		void PrintModule(IRModule const& M);

	private:
		std::ostream& os;
		std::string output;

	private:
		void PrintGlobalVariable(GlobalVariable const*);
		void PrintFunction(Function const*);
		void PrintBasicBlock(BasicBlock const&);

		std::string GetTypeAsString(IRType*, bool space = true);

		template<typename... Args>
		void EmitLn(char const* fmt, Args&&... args)
		{
			std::string str = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			str += "\n";
			output += str;
		}
		template<typename... Args>
		void Emit(char const* fmt, Args&&... args)
		{
			std::string str = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			output += str;
		}
	};
}