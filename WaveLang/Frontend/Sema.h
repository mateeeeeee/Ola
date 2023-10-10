#pragma once
#include "Scope.h"
#include "AST.h"

namespace wave
{
	namespace diag
	{
		enum DiagCode : uint32;
	}

	class Parser;
	class Diagnostics;
	struct SourceLocation;

	class Sema 
	{
		friend class Parser;
		struct Context
		{
			ScopeStack<DeclAST> decl_scope_stack;
			class QualifiedType const* current_func = nullptr;
			bool return_stmt_encountered = false;
		};

	public:
		explicit Sema(Diagnostics& diagnostics);
		WAVE_NONCOPYABLE(Sema);
		WAVE_DEFAULT_MOVABLE(Sema);
		~Sema();

	private:
		UniqueVariableDeclPtr ActOnVariableDecl(std::string_view name, QualifiedType const& type, SourceLocation const& loc, UniqueExprPtr&& init_expr);
		UniqueFunctionDeclPtr ActOnFunctionDecl(std::string_view name, QualifiedType const& type, SourceLocation const& loc, UniqueVariableDeclPtrList&& param_decls);
		void ActOnFunctionDecl(UniqueFunctionDeclPtr& function_decl, UniqueCompoundStmtPtr&& definition);

	private:
		Diagnostics& diagnostics;
		Context ctx;
	};
}