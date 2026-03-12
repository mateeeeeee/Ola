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

	template<typename SymbolT> requires Symbol<SymbolT>
	class SymbolScope
	{
	public:
		SymbolScope() {}

		Bool Insert(SymbolT* symbol)
		{
			std::string name_key(symbol->GetName());
			if (symbols.contains(name_key) || overload_sets.contains(name_key))
			{
				return false;
			}
			symbols[name_key] = symbol;
			return true;
		}
		Bool InsertOverload(SymbolT* symbol)
		{
			std::string name_key(symbol->GetName());
			if (symbols.contains(name_key))
			{
				return false;
			}
			overload_sets[name_key].push_back(symbol);
			return true;
		}
		SymbolT* Lookup(std::string_view sym_name)
		{
			std::string name_key(sym_name);
			if (symbols.contains(name_key))
			{
				return symbols[name_key];
			}
			if (overload_sets.contains(name_key) && !overload_sets[name_key].empty())
			{
				return overload_sets[name_key][0];
			}
			return nullptr;
		}
		std::vector<SymbolT*>& LookupOverload(std::string_view sym_name)
		{
			std::string name_key(sym_name);
			auto it = overload_sets.find(name_key);
			if (it != overload_sets.end())
			{
				return it->second;
			}
			static const std::vector<SymbolT*> empty_overload_result{};
			return const_cast<std::vector<SymbolT*>&>(empty_overload_result);
		}

	private:
		std::unordered_map<std::string, SymbolT*> symbols;
		std::unordered_map<std::string, std::vector<SymbolT*>> overload_sets;
	};

	template<typename SymbolT> requires Symbol<SymbolT>
	class SymbolTable
	{
	public:
		using Symbol = SymbolT;

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

		Bool Insert(SymbolT* symbol)
		{
			return scopes.back().Insert(symbol);
		}
		Bool InsertOverload(SymbolT* symbol)
		{
			return scopes.back().InsertOverload(symbol);
		}
		Bool InsertGlobalOverload(SymbolT* symbol)
		{
			return scopes.front().InsertOverload(symbol);
		}

		SymbolT* Lookup(std::string const& sym_name)
		{
			return Lookup(std::string_view(sym_name));
		}
		SymbolT* Lookup(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (SymbolT* sym = scope->Lookup(sym_name))
				{
					return sym;
				}
			}
			return nullptr;
		}
		SymbolT* LookupMember(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				SymbolT* sym = scope->Lookup(sym_name);
				if (sym && sym->IsMember())
				{
					return sym;
				}
			}
			return nullptr;
		}
		SymbolT* LookupCurrentScope(std::string_view sym_name)
		{
			if (SymbolT* sym = scopes.back().Lookup(sym_name))
			{
				return sym;
			}
			return nullptr;
		}

		std::vector<SymbolT*>& LookupMemberOverload(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				std::vector<SymbolT*>& syms = scope->LookupOverload(sym_name);
				for (SymbolT* sym : syms) if (sym->IsMember())
				{
					return syms;
				}
			}
			return scopes.back().LookupOverload(sym_name);
		}
		std::vector<SymbolT*>& LookupOverload(std::string_view sym_name)
		{
			for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
			{
				if (std::vector<SymbolT*>& syms = scope->LookupOverload(sym_name); !syms.empty())
				{
					return syms;
				}
			}
			return scopes.back().LookupOverload(sym_name);
		}
		std::vector<SymbolT*>& LookupCurrentScopeOverload(std::string_view sym_name)
		{
			return scopes.back().LookupOverload(sym_name);
		}

		Bool IsGlobal() const { return scopes.size() == 1; }

	private:
		std::vector<SymbolScope<SymbolT>> scopes;
	};

	template<typename SymbolT>
	struct SymbolTableGuard
	{
		SymbolTableGuard(SymbolTable<SymbolT>& sym_table) : sym_table(sym_table)
		{
			sym_table.EnterScope();
		}
		~SymbolTableGuard()
		{
			sym_table.ExitScope();
		}
		SymbolTable<SymbolT>& sym_table;
	};
	#define SYM_TABLE_GUARD(sym_table) SymbolTableGuard<std::remove_reference_t<decltype(sym_table)>::Symbol> OLA_CONCAT(_sym_table_guard_,__COUNTER__)(sym_table)
}
