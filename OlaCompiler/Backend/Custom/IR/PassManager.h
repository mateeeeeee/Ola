#pragma once
#include <concepts>
#include <vector>
#include <memory>
#include "PassRegistry.h"
#include "Pass.h"

namespace ola
{
	template<typename UnitT>
	struct UnitTraits;

	template<typename UnitT>
	class AnalysisManager;

	template<typename UnitT>
	class PassManager 
	{
		using BasePassT = typename UnitTraits<UnitT>::BasePassT;
		using ParentUnitT = typename UnitTraits<UnitT>::ParentUnitT;
		static_assert(std::is_base_of_v<Pass, BasePassT>);

	public:
		void AddPass(BasePassT* pass)
		{
			Verify(pass->GetPassID());
			passes.emplace_back(pass);
		}
		template<typename PassT, typename... Args> requires std::is_base_of_v<BasePassT, PassT>
		void AddPass(Args&&... args)
		{
			Verify(PassT::ID());
			passes.emplace_back(new PassT(std::forward<Args>(args)...));
		}

		Bool Run(UnitT& U, AnalysisManager<UnitT>& AM)
		{
			Bool changed = false;
			for (auto& pass : passes)
			{
				changed |= pass->RunOn(U, AM);
			}
			return changed;
		}
		Bool Run(UnitT& U, ParentUnitT& PU, AnalysisManager<UnitT>& AM)
		{
			Bool changed = false;
			for (auto& pass : passes)
			{
				pass->Init(PU);
			}
			for (auto& pass : passes)
			{
				changed |= pass->RunOn(U, AM);
			}
			for (auto& pass : passes)
			{
				pass->Deinit(PU);
			}
			return changed;
		}

		Bool IsEmpty() const
		{
			return passes.empty();
		}

	private:
		std::vector<std::unique_ptr<BasePassT>> passes;

	private:
		void Verify(void const* pass_id)
		{
			PassInfo const* pass_info = g_PassRegistry.GetInfo(pass_id);
			OLA_ASSERT_MSG(pass_info, "Pass was not registered! Did you forget to declare OLA_REGISTER_PASS or OLA_REGISTER_ANALYSIS_PASS? ");
			OLA_ASSERT_MSG(!pass_info->IsAnalysis(), "You can only register analysis pass to analysis manager!");
		}
	};


}