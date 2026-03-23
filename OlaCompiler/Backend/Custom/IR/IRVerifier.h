#pragma once
#include <string>
#include <vector>

namespace ola
{
	class IRModule;
	class Function;
	class BasicBlock;
	class Instruction;

	struct VerifyError
	{
		std::string message;
	};

	class IRVerifier
	{
	public:
		Bool Verify(IRModule const& module);
		Bool Verify(Function const& function);

		std::vector<VerifyError> const& GetErrors() const { return errors; }
		Bool HasErrors() const { return !errors.empty(); }

	private:
		std::vector<VerifyError> errors;

	private:
		void VerifyFunction(Function const& function);
		void VerifyBlock(Function const& function, BasicBlock const& block);
		void VerifyInstruction(Function const& function, Instruction const& inst);

		void VerifyTerminator(Function const& function, BasicBlock const& block);
		void VerifyBranch(Function const& function, Instruction const& inst);
		void VerifyPhi(Function const& function, Instruction const& inst);
		void VerifyBinaryOp(Instruction const& inst);
		void VerifyCall(Instruction const& inst);

		void Error(std::string msg);
	};
}
