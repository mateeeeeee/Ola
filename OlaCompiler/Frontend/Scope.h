#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <concepts>

namespace ola
{
	template<typename S>
	concept Symbol = requires(S* s)
	{
		{s->GetName()} -> std::convertible_to<std::string_view>;
	};

	template<typename T> requires Symbol<T>
	class SymbolScope
	{
	public:
		using SymType = T;
	public:
		SymbolScope() {}
		
		Bool Insert(SymType* symbol)
		{
			std::string name_key(symbol->GetName());
			if (sym_map.contains(name_key)) return false;
			if (overload_sym_map.contains(name_key)) return false;
			sym_map[name_key] = symbol;
			return true;
		}
		Bool Insert_Overload(SymType* symbol)
		{
			std::string name_key(symbol->GetName());
			if (sym_map.contains(name_key)) return false;
			overload_sym_map[name_key].push_back(symbol);
			return true;
		}
		SymType* LookUp(std::string_view sym_name)
		{
			std::string name_key(sym_name);
			if (sym_map.contains(name_key))
			{
				return sym_map[name_key];
			}
			else if (overload_sym_map.contains(name_key) && !overload_sym_map[name_key].empty())
			{
				return overload_sym_map[name_key][0];
			}
			else return nullptr;
		}
		std::vector<SymType*>& LookUp_Overload(std::string_view sym_name)
		{
			std::string name_key(sym_name);
			return overload_sym_map[name_key];
		}

	private:
		std::unordered_map<std::string, SymType*> sym_map;
		std::unordered_map<std::string, std::vector<SymType*>> overload_sym_map;
	};

	template<typename T> requires Symbol<T>
	class SymbolTable 
	{
	public:
		using SymType = T;
	public:
		SymbolTable()
		{
			scopes.emplace_back();
		}

		void EnterScope()
		{
			scopes.emplace_back();
		}
		void ExitScope()
		{
			scopes.pop_back();
		}

		Bool Insert(SymType* symbol)
		{
			return scopes.back().Insert(symbol);
		}
		Bool Insert_Overload(SymType* symbol)
		{
			return scopes.back().Insert_Overload(symbol);
		}

		SymType* LookUp(std::string const& sym_name)
		{
			return LookUp(sym_name);
		}
		SymType* LookUp(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (SymType* sym = scope->LookUp(sym_name)) return sym;
			}
			return nullptr;
		}
		SymType* LookUpMember(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				SymType* sym = scope->LookUp(sym_name);
				if (sym && sym->IsMember()) return sym;
			}
			return nullptr;
		}
		SymType* LookUpCurrentScope(std::string_view sym_name)
		{
			if (SymType* sym = scopes.back().LookUp(sym_name)) return sym;
			return nullptr;
		}

		std::vector<SymType*>& LookUpMember_Overload(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				std::vector<SymType*>& syms = scope->LookUp_Overload(sym_name);
				for (SymType* sym : syms) if (sym->IsMember()) return syms;
			}
			return scopes.back().LookUp_Overload(sym_name);
		}
		std::vector<SymType*>& LookUp_Overload(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (std::vector<SymType*>& syms = scope->LookUp_Overload(sym_name); !syms.empty()) return syms;
			}
			return scopes.back().LookUp_Overload(sym_name);
		}
		std::vector<SymType*>& LookUpCurrentScope_Overload(std::string_view sym_name)
		{
			return scopes.back().LookUp_Overload(sym_name);
		}

		Bool IsGlobal() const { return scopes.size() == 1; }

	private:
		std::vector<SymbolScope<SymType>> scopes;
	};

	template<typename T>
	struct SymbolTableGuard
	{
		SymbolTableGuard(SymbolTable<T>& sym_table) : sym_table(sym_table)
		{
			sym_table.EnterScope();
		}
		~SymbolTableGuard()
		{
			sym_table.ExitScope();
		}
		SymbolTable<T>& sym_table;
	};
	#define SYM_TABLE_GUARD(sym_table) SymbolTableGuard<std::remove_reference_t<decltype(sym_table)>::SymType> OLA_CONCAT(_sym_table_guard_,__COUNTER__)(sym_table)
}