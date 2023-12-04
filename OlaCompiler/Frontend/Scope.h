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
		
		bool Insert(SymType* symbol)
		{
			if (sym_map.contains(symbol->GetName())) return false;
			sym_map[symbol->GetName()] = symbol;
			return true;
		}
		SymType* LookUp(std::string_view sym_name)
		{
			std::string name(sym_name);
			if (sym_map.contains(name))
			{
				return sym_map[name];
			}
			else return nullptr;
		}

		bool Remove(std::string_view sym_name)
		{
			std::string name(sym_name);
			return sym_map.erase(name) == 1;
		}

	private:
		std::unordered_map<std::string_view, SymType*> sym_map;
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

		bool Insert(SymType* symbol)
		{
			return scopes.back().Insert(symbol);
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

		bool Remove(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (scope->Remove(sym_name)) return true;
			}
			return false;
		}

		bool IsGlobal() const { return scopes.size() == 1; }

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