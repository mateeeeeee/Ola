#pragma once
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Pass.h"

namespace ola
{
	using AnalysisResult = void const*;

	template<typename UnitT>
	struct UnitTraits;

	template<typename UnitT>
	class AnalysisManager 
	{
		using BasePassT = typename UnitTraits<UnitT>::BasePassT;
		using ParentUnitT = typename UnitTraits<UnitT>::ParentUnitT;
		static_assert(std::is_base_of_v<Pass, BasePassT>);

		using AnalysisPassMapT = std::unordered_map<PassID, std::unique_ptr<BasePassT>>;
		using AnalysisResultMapT = std::unordered_map<PassID, AnalysisResult>;

		struct UnitAnalysisInfo
		{
			AnalysisPassMapT analysis_passes;
			AnalysisResultMapT analysis_results;
		};

	public:
		AnalysisManager() = default;
		~AnalysisManager() = default;

		template <typename PassT, typename... Args> requires std::is_base_of_v<Pass, PassT>
		void RegisterPass(UnitT& U, Args&&... args)
		{
			UnitAnalysisInfo& analysis_info = unit_analysis_info_map[&U];
			if (!analysis_info.analysis_passes.contains(PassT::ID()))
			{
				analysis_info.analysis_passes[PassT::ID()] = std::make_unique<PassT>(std::forward<Args>(args)...);
			}
		}

		template <typename PassT> requires std::is_base_of_v<Pass, PassT>
		auto const& GetResult(UnitT& U) const
		{
			using ResultT = typename PassT::Result;
			UnitAnalysisInfo const& analysis_info = unit_analysis_info_map[&U];
			if (!analysis_info.analysis_passes.contains(PassT::ID()))
			{
				OLA_ASSERT_MSG(false, "Pass was not registered! Did you forget to call RegisterPass?");
				return ResultT{};
			}
			if (!analysis_info.analysis_results.contains(PassT::ID()))
			{
				BasePassT* pass = analysis_info.analysis_passes[PassT::ID()];
				pass->RunOn(U);
				analysis_info.analysis_results[PassT::ID()] = static_cast<PassT*>(pass)->GetResult();
			}
			return *static_cast<ResultT const*>(analysis_info.analysis_results[PassT::ID()]);
		}

		template <typename PassT> requires std::is_base_of_v<Pass, PassT>
		void InvalidateCache(UnitT& U) const
		{
			UnitAnalysisInfo& analysis_info = unit_analysis_info_map[&U];
			analysis_info.analysis_results.erase(PassT::ID());
		}

		void InvalidateCache(UnitT& U) const
		{
			UnitAnalysisInfo& analysis_info = unit_analysis_info_map[&U];
			analysis_info.analysis_results.clear();
		}

	private:
		std::unordered_map<UnitT*, UnitAnalysisInfo> unit_analysis_info_map;
	};

}