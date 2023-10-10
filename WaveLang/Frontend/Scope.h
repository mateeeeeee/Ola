#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <concepts>

namespace wave
{
	template<typename S>
	concept Symbol = requires(S* s)
	{
		{s->GetName()} -> std::convertible_to<std::string_view>;
	};

	template<typename T> requires Symbol<T>
	class Scope
	{
	public:
		using SymType = T;
	public:
		Scope() {}
		
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
	private:
		std::unordered_map<std::string_view, SymType*> sym_map;
	};

	template<typename T> requires Symbol<T>
	class ScopeStack 
	{
	public:
		using SymType = T;
	public:
		ScopeStack()
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
		SymType* LookUpCurrentScope(std::string_view sym_name)
		{
			if (SymType* sym = scopes.back().LookUp(sym_name)) return sym;
			return nullptr;
		}

		bool IsGlobal() const { return scopes.size() == 1; }

	private:
		std::vector<Scope<SymType>> scopes;
	};

	template<typename T>
	struct ScopeStackGuard
	{
		ScopeStackGuard(ScopeStack<T>& scope_stack) : scope_stack(scope_stack)
		{
			scope_stack.EnterScope();
		}
		~ScopeStackGuard()
		{
			scope_stack.ExitScope();
		}
		ScopeStack<T>& scope_stack;
	};
	#define SCOPE_STACK_GUARD(scope_stack) ScopeStackGuard<std::remove_reference_t<decltype(scope_stack)>::SymType> WAVE_CONCAT(_scope_stack_guard_,__COUNTER__)(scope_stack)
}