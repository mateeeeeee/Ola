#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Type.h"

namespace wave
{


	template<typename SymType>
	class ScopeTable
	{
	public:
		explicit ScopeTable(uint32 scope_id) : scope_id(scope_id) {}
		uint32 GetScope() const { return scope_id; }

		bool Insert(SymType const& symbol)
		{
			if (scope_sym_table.contains(symbol.name)) return false;
			scope_sym_table[symbol.name] = symbol;
			return true;
		}

		SymType* LookUp(std::string const& sym_name)
		{
			if (scope_sym_table.contains(sym_name)) return &scope_sym_table[sym_name];
			else return nullptr;
		}


	private:
		uint32 const scope_id;
		std::unordered_map<std::string, SymType> scope_sym_table;
	};

	template<typename SymType>
	class SymbolTable
	{
	public:
		SymbolTable()
		{
			scopes.emplace_back(scope_id++);
		}

		void EnterScope()
		{
			scopes.emplace_back(scope_id++);
		}
		void ExitScope()
		{
			scopes.pop_back();
			--scope_id;
		}

		bool Insert(SymType const& symbol)
		{
			return scopes.back().Insert(symbol);
		}

		SymType* LookUp(std::string const& sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (SymType* sym = scope->LookUp(sym_name)) return sym;
			}
			return nullptr;
		}
		SymType* LookUp(std::string_view sym_name)
		{
			return LookUp(std::string(sym_name));
		}
		SymType* LookUpCurrentScope(std::string_view sym_name)
		{
			if (SymType* sym = scopes.back().LookUp(std::string(sym_name))) return sym;
			return nullptr;
		}

		bool IsGlobal() const { return scopes.size() == 1; }

	private:
		std::vector<ScopeTable<SymType>> scopes;
		uint32 scope_id = 0;
	};
}