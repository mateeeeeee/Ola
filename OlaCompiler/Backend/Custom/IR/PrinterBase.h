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

	class NameManager
	{
		using ValueStringMap = std::unordered_map<Value const*, std::string>;
		using StringSlotMap  = std::unordered_map<std::string, Uint32>;
		enum class NamePrefix : Uint32
		{
			None,
			Global,
			Local,
			Label
		};

	public:
		NameManager() = default;
		OLA_NONCOPYABLE(NameManager)
		~NameManager() = default;

		std::string_view GetUniqueName(Value const* V);
		void ClearLocals();

	private:
		ValueStringMap global_name_map;
		StringSlotMap  global_slot_map;
		ValueStringMap local_name_map;
		StringSlotMap  local_slot_map;

	private:
		void RegisterValue(Value const* V);
		std::string GetPrefixedName(std::string_view name, NamePrefix prefix);
		std::string GetPrefixedName(Value const*);
	};

	class PrinterBase
	{
	protected:
		std::string output;
		NameManager name_manager;
		Bool use_line_break;

	protected:
		PrinterBase() : use_line_break(false){}
		std::string_view GetUniqueName(Value const* V)
		{
			return name_manager.GetUniqueName(V);
		}

		void PrintType(IRType*);
		void PrintGlobalVariable(GlobalVariable const*);
		void PrintFunction(Function const*);
		void PrintBasicBlock(BasicBlock const&);
		void PrintInstruction(Instruction const&);
		void PrintConstant(Constant const*);
		void PrintOperand(Value const*, Bool print_type = true);

		template<typename... Args>
		void EmitLn(Char const* fmt, Args&&... args)
		{
			std::string str = std::vformat(fmt, std::make_format_args(args...));
			if (use_line_break) str += "\\l";
			str += "\n";
			output += str;
		}
		template<typename... Args>
		void Emit(Char const* fmt, Args&&... args)
		{
			std::string str = std::vformat(fmt, std::make_format_args(args...));
			output += str;
		}
		void EmitSpace()
		{
			Emit(" ");
		}
		void EmitNewline()
		{
			EmitLn("");
		}
		template<Uint32 N>
		void PopOutput()
		{
			for (Uint32 i = 0; i < N; ++i) output.pop_back();
		}
	};

}