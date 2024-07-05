#pragma once
#include <unordered_map>
#include <string>
#include <string_view>

namespace ola
{
	struct PassInfo
	{
	public:
		std::string_view GetName() const { return pass_name; }
		void const* GetID() const { return pass_id; }
		bool IsAnalysis() const { return is_analysis; }

	private:		
		   std::string pass_name;
		   void const* pass_id;
		   bool is_analysis;

	protected:
		PassInfo(std::string_view name, void const* id, bool analysis)
			: pass_name(name), pass_id(id), is_analysis(analysis) {}
	};

	class PassRegistry
	{
	public:
		static PassRegistry& Get()
		{
			static PassRegistry instance;
			return instance;
		}

		void RegisterPass(PassInfo const& info)
		{
			name_info_map[info.GetName()] = &info;
			id_info_map[info.GetID()] = &info;
		}

		PassInfo const* GetInfo(std::string_view name)
		{
			return name_info_map[name];
		}
		PassInfo const* GetInfo(void const* id)
		{
			return id_info_map[id];
		}

	private:
		std::unordered_map<std::string_view, PassInfo const*> name_info_map;
		std::unordered_map<void const*, PassInfo const*> id_info_map;
	};
	#define g_PassRegistry PassRegistry::Get()


	template<typename PassT>
	class RegisterPass : public PassInfo
	{
	public:
		RegisterPass(std::string_view name, bool analysis) : PassInfo(name, &PassT::ID, analysis)
		{
			g_PassRegistry.RegisterPass(*this);
		}
	};

	#define REGISTER_PASS(type, name, analysis) \
	static RegisterPass<type> OLA_CONCAT(_pass,__COUNTER__)(name, analysis)
}