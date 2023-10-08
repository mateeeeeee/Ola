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
		QualifiedType type;
	};

	template<typename _Ty>
	class ScopeTable
	{
		using SymType = _Ty;
	public:
		explicit ScopeTable(uint32 scope_id) : scope_id(scope_id) {}
		uint32 GetScope() const { return scope_id; }

		bool Insert(SymType const& symbol)
		{
			if (scope_sym_table.contains(symbol.name)) return false;
			scope_sym_table[symbol.name] = symbol;
			return true;
		}

		SymType* LookUp(std::string_view sym_name)
		{
			std::string name(sym_name);
			if (scope_sym_table.contains(name))
			{
				return &scope_sym_table[name];
			}
			else return nullptr;
		}


	private:
		uint32 const scope_id;
		std::unordered_map<std::string, SymType> scope_sym_table;
	};

	template<typename _Ty>
	class SymbolTable
	{
	public:
		using SymType = _Ty;
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
			return scopes.back().Insert(std::move(symbol));
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

	template<typename T>
	struct ScopedSymbolTable
	{
		ScopedSymbolTable(SymbolTable<T>& sym_table) : sym_table(sym_table)
		{
			sym_table.EnterScope();
		}
		~ScopedSymbolTable()
		{
			sym_table.ExitScope();
		}
		SymbolTable<T>& sym_table;
	};
	#define SCOPED_SYMBOL_TABLE(sym_table) ScopedSymbolTable<std::remove_reference_t<decltype(sym_table)>::SymType> WAVE_CONCAT(_scoped_sym_table,__COUNTER__)(sym_table)
}