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
	class PassManager 
	{
		using BasePassT = typename UnitTraits<UnitT>::BasePassT;
		using ParentUnitT = typename UnitTraits<UnitT>::ParentUnitT;
		static_assert(std::is_base_of_v<Pass, BasePassT>);
	public:

		template<typename PassT> requires std::is_base_of_v<BasePassT, PassT>
		void AddPass(PassT&& pass)
		{
			passes.emplace_back(new PassT(std::forward<PassT>(pass)));
		}
		void AddPass(BasePassT* pass)
		{
			passes.emplace_back(pass);
		}
		template<typename PassT, typename... Args> requires std::is_base_of_v<BasePassT, PassT>
		void AddPass(Args&&... args)
		{
			passes.emplace_back(new PassT(std::forward<Args>(args)...));
		}

		bool Run(UnitT& U)
		{
			bool changed = false;
			for (auto& pass : passes)
			{
				changed |= pass->RunOn(U);
			}
			return changed;
		}
		bool Run(UnitT& U, ParentUnitT& PU)
		{
			bool changed = false;
			for (auto& pass : passes)
			{
				pass->Init(PU);
			}
			for (auto& pass : passes)
			{
				changed |= pass->RunOn(U);
			}
			for (auto& pass : passes)
			{
				pass->Deinit(PU);
			}
			return changed;
		}

	private:
		std::vector<std::unique_ptr<BasePassT>> passes;
	};


}