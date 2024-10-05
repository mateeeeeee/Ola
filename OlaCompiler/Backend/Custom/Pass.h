#pragma once
#include <concepts>
#include <string>
#include <string_view>

namespace ola
{
	class IRModule;

	using PassID = void const*;
	enum class PassKind
	{
		Function,
		MachineFunction,
		Module,
		MachineModule
	};

	class Pass
	{
	public:
		Pass(char pass_id, PassKind kind) : ID(&pass_id), kind(kind) {}
		virtual ~Pass() = default;

		PassID GetPassID() const { return ID; }
		PassKind GetPassKind() const { return kind; }
		std::string_view GetPassName() const;

	private:
		PassID ID;
		PassKind kind; 
	};

}