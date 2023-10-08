#pragma once
#include "Symbol.h"

namespace wave
{
	class Parser;
	struct AST;
	class ExprAST;
	class DeclAST;
	class StmtAST;
	class FunctionDeclAST;
	class VariableDeclAST;
	class CompoundStmtAST;
	class ExprStmtAST;
	class ReturnStmtAST;
	class IntLiteralAST;
	class StringLiteralAST;
	class IdentifierAST;

	class FunctionType;

	class Sema 
	{
		friend class Parser;
		struct Context
		{
			SymbolTable<Symbol> sym_table;
			FunctionType const* current_func = nullptr;
		};

	public:
		Sema() = default;
		WAVE_NONCOPYABLE(Sema);
		WAVE_DEFAULT_MOVABLE(Sema);
		~Sema() = default;

		void ActOnVariableDecl(std::unique_ptr<VariableDeclAST>& var_decl);
		void ActOnFunctionDecl(std::unique_ptr<FunctionDeclAST>& func_decl);

	private:
		Context ctx;
	};
}