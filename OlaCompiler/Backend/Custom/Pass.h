#pragma once
#include <concepts>
#include <string>
#include <string_view>
#include "PassManagerBase.h"

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
		Pass(char pass_id, PassKind kind) : ID(&pass_id), kind(kind), PM(nullptr) {}
		virtual ~Pass() = default;

		void SetPassManager(PassManagerBase* PM)
		{
			this->PM = PM;
		}

		PassID GetPassID() const { return ID; }
		PassKind GetPassKind() const { return kind; }
		std::string_view GetPassName() const;
		bool IsAnalysis() const;

		template<typename PassT> requires std::is_base_of_v<Pass, PassT>
		PassT& GetAnalysis()
		{
			PassT& pass = PM->GetPass<PassT>();
			OLA_ASSERT(static_cast<Pass&>(pass).IsAnalysis());
			return pass;
		}

	private:
		PassID ID;
		PassKind kind; 
		PassManagerBase* PM;
	};

}