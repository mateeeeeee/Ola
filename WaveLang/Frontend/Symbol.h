#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Type.h"

namespace wave
{
	struct Symbol
	{
		std::string name;
		std::unique_ptr<Type> type;
	};

	template<typename SymType>
	class ScopeTable
	{
	public:
		explicit ScopeTable(uint32 scope_id) : scope_id(scope_id) {}
		uint32 GetScope() const { return scope_id; }

		bool Insert(SymType&& symbol)
		{
			if (scope_sym_table.contains(symbol.name)) return false;
			scope_sym_table.insert(std::make_pair(symbol.name, std::move(symbol)));
			return true;
		}

		SymType* LookUp(std::string const& sym_name)
		{
			if (auto it = scope_sym_table.find(sym_name); it != scope_sym_table.end())
			{
				return &it->second;
			}
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

		bool Insert(SymType&& symbol)
		{
			return scopes.back().Insert(std::move(symbol));
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
			return LookUp(sym_name);
		}
		SymType* LookUpCurrentScope(std::string_view sym_name)
		{
			if (SymType* sym = scopes.back().LookUp(sym_name)) return sym;
			return nullptr;
		}

		bool IsGlobal() const { return scopes.size() == 1; }

	private:
		std::vector<ScopeTable<SymType>> scopes;
		uint32 scope_id = 0;
	};
}