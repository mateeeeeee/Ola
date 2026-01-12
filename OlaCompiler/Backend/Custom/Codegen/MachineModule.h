#pragma once
#include <iosfwd>
#include "MachineGlobal.h"
#include "MachineContext.h"
#include "ISel/ISelDriver.h"

namespace ola
{
	class IRModule;
	class Function;
	class BasicBlock;
	template<typename UnitT>
	class AnalysisManager;
	using FunctionAnalysisManager = AnalysisManager<Function>;

	class MachineInstruction;
	class MIRInstructionInfo;
	class MachineFunction;

	class Target;

	class MachineModule
	{
	public:
		MachineModule(IRModule& ir_module, Target const& target, FunctionAnalysisManager& FAM);
		virtual ~MachineModule() = default;

		Target const& GetTarget() const { return target; }
		auto   const& GetGlobals() const { return globals; }

		void SetISelMode(ISelMode mode) { isel_mode = mode; }
		ISelMode GetISelMode() const { return isel_mode; }

		void EmitMIR(std::string_view mir_file);
		void EmitAssembly(std::string_view assembly_file);

	protected:
		std::vector<MachineGlobal> globals;
		MachineContext machine_ctx;
		Target const& target;
		FunctionAnalysisManager& FAM;
		ISelMode isel_mode = ISelMode::TreePattern;

	private:
		void LowerModule(IRModule*);
		void LowerFunction(Function*);

		void LegalizeInstructions(MachineFunction& MF);
		void PostLegalizeInstructions(MachineFunction& MF);
	};
}