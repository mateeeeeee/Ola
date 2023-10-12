#pragma once

namespace wave
{
	class NodeAST;
	class TranslationUnit;

	class Decl;
	class FunctionDecl;
	class VariableDecl;

	class Stmt;
	class CompoundStmt;
	class ExprStmt;
	class DeclStmt;
	class NullStmt;
	class IfStmt;
	class ReturnStmt;

	class Expr;
	class UnaryExpr;
	class BinaryExpr;
	class TernaryExpr;
	class IdentifierExpr;
	class DeclRefExpr;
	class ConstantInt;
	class ConstantString;
	class ConstantBool;
	class ConstantFloat;
	class CastExpr;
	class FunctionCallExpr;

	struct AST;
}

/*
//todo list for adding new ast node
1. add a class and member definitions
2. Add in Parser::Parse*
3. Add in Sema::ActOn*
4. Add forward declaration, add type alias, add it in visitor and implement it in all visitors
*/