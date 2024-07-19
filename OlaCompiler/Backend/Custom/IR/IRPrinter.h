#pragma once
#include <iosfwd>
#include <string>
#include <format>
#include <unordered_map>

namespace ola
{
	class IRModule;
	class Function;
	class GlobalVariable;
	class BasicBlock;
	class Value;
	class Constant;
	class Instruction;
	class IRType;

	class IRPrinter
	{
		enum class NamePrefix : uint32
		{
			None,
			Global,
			Local,
			Label
		};

	public:
		explicit IRPrinter(std::ostream& os) : os(os) {}
		void PrintModule(IRModule const& M);

	private:
		std::ostream& os;
		std::string output;

		std::unordered_map<std::string_view, uint32> names_count;
		std::unordered_map<Value const*, std::string> unique_names;

	private:
		void PrintGlobalVariable(GlobalVariable const*);
		void PrintFunction(Function const*);
		void PrintBasicBlock(BasicBlock const&);
		void PrintInstruction(Instruction const&);
		void PrintConstant(Value*);
		void PrintOperand(Value const*, bool print_type = true);

		std::string GetPrefixedName(std::string_view name, NamePrefix prefix);
		std::string GetPrefixedName(Value const*);
		void PrintFullName(Value const*);

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
		template<uint32 N>
		void OutputPopBack()
		{
			for (uint32 i = 0; i < N; ++i) output.pop_back();
		}
	};
}