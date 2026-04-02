#pragma once
#include "Backend/Custom/IR/PassRegistry.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Value;
	class Instruction;
	class AllocaInst;
	class GlobalVariable;

	enum class AliasResult : Uint8
	{
		NoAlias,       
		MayAlias,      
		MustAlias      
	};

	inline constexpr Int64 UNKNOWN_MEMORY_OFFSET = INT64_MIN;
	inline constexpr Uint64 UNKNOWN_MEMORY_SIZE = UINT64_MAX;

	struct MemoryLocation
	{
		Value* Ptr = nullptr;
		Int64 Offset = UNKNOWN_MEMORY_OFFSET;
		Uint64 Size = UNKNOWN_MEMORY_SIZE;
		Bool HasKnownOffset() const { return Offset != UNKNOWN_MEMORY_OFFSET; }
		Bool HasKnownSize() const { return Size != UNKNOWN_MEMORY_SIZE; }
	};

	class AliasAnalysis
	{
	public:
		AliasAnalysis() = default;

		AliasResult Alias(Value* P1, Value* P2) const;
		AliasResult Alias(MemoryLocation const& Loc1, MemoryLocation const& Loc2) const;

		Bool MayAlias(Value* P1, Value* P2) const
		{
			return Alias(P1, P2) != AliasResult::NoAlias;
		}
		Bool MustAlias(Value* P1, Value* P2) const
		{
			return Alias(P1, P2) == AliasResult::MustAlias;
		}
		Bool NoAlias(Value* P1, Value* P2) const
		{
			return Alias(P1, P2) == AliasResult::NoAlias;
		}

		static MemoryLocation GetMemoryLocation(Value* Ptr);

	private:
		static Value* GetUnderlyingObject(Value* V);
		static Bool IsIdentifiedObject(Value* V);
		static Bool IsIdentifiedFunctionLocal(Value* V);
		AliasResult AliasFromUnderlyingObjects(Value* O1, Value* O2) const;
	};

	class AliasAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = AliasAnalysis;

	public:
		AliasAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		AliasAnalysis const& GetResult() const { return AA; }

		static void const* ID() { return &id; }

	private:
		AliasAnalysis AA;
	};
	OLA_REGISTER_ANALYSIS_PASS(AliasAnalysisPass, "Alias Analysis");
}
