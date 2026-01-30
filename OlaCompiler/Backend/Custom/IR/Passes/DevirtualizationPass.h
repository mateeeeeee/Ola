#pragma once
#include <optional>
#include <unordered_map>
#include <vector>
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class LoadInst;
	class GlobalVariable;
	class ConstantInt;
	class CallInst;
	class PtrAddInst;
	class GetElementPtrInst;
	class Function;

	class DevirtualizationPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		DevirtualizationPass() : IRModulePass(id) {}

		virtual Bool RunOn(IRModule& M, IRModuleAnalysisManager& MAM) override;
		static void const* ID() { return &id; }

	private:
		struct VTableEntry
		{
			GlobalVariable* vtable;
			Function* func;
		};
		std::unordered_map<Uint32, std::vector<VTableEntry>> vtable_slot_map;
		std::unordered_map<GlobalVariable*, std::string> vtable_to_class;

		void BuildVTableMap(IRModule& M);
		Bool RunOnFunction(Function& F);
		std::optional<std::pair<LoadInst*, Uint32>> MatchVTablePattern(CallInst* CI);
		GlobalVariable* TraceVTableSource(LoadInst* vtable_load);
		Bool DevirtualizeCall(CallInst* CI, Function* target);
	};

	OLA_REGISTER_PASS(DevirtualizationPass, "Devirtualization Pass");
	inline IRModulePass* CreateDevirtualizationPass() { return new DevirtualizationPass(); }
}
