#pragma once
#include "Symbol.h"
#include "ForwardAST.h"

namespace wave
{
	namespace diag
	{
		enum DiagCode : uint32;
	}

	class Parser;
	struct SourceLocation;

	class Sema 
	{
		friend class Parser;
		struct Context
		{
			SymbolTable<Symbol> sym_table;
			class QualifiedType const* current_func = nullptr;
			bool return_stmt_encountered = false;
		};

	public:
		Sema();
		~Sema();

	private:
		WAVE_NONCOPYABLE(Sema);
		WAVE_DEFAULT_MOVABLE(Sema);

		void ActOnVariableDecl(VariableDeclAST* var_decl);
		void ActOnFunctionDecl(FunctionDeclAST* function_decl);
		void ActOnReturnStmt(ReturnStmtAST* return_stmt);
		void ActOnExpr(ExprAST* expr);
		void ActOnIdentifier(IdentifierAST* identifier);

	private:
		Context ctx;

	private:
		void Diag(diag::DiagCode, SourceLocation const&);

		void ActOnUnaryExpr(UnaryExprAST* unary_expr);
		void ActOnBinaryExpr(BinaryExprAST* binary_expr);
		void ActOnCastExpr(CastExprAST* cast_expr);
	};
}