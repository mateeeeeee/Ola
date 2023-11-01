#pragma once

namespace wave
{
	class NodeAST;
	class TranslationUnit;

	class Decl;
	class FunctionDecl;
	class VariableDecl;
	class TagDecl;
	class EnumDecl;
	class EnumMemberDecl;

	class Stmt;
	class CompoundStmt;
	class ExprStmt;
	class DeclStmt;
	class NullStmt;
	class ReturnStmt;
	class IfStmt;
	class BreakStmt;
	class ContinueStmt;
	class ForStmt;
	class WhileStmt;
	class DoWhileStmt;
	class CaseStmt;
	class SwitchStmt;
	class GotoStmt;
	class LabelStmt;

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
	class ImplicitCastExpr;
	class FunctionCallExpr;
	class InitializerListExpr;
	class ArrayAccessExpr;

	struct AST;
}

/*
//todo list for adding new ast node
0. Add forward declaration, type alias, add to visitor interface and implement it in all visitors (debug,llvm)
1. add a class and member definitions
2. Add in Parser::Parse*
3. Add in Sema::ActOn*
*/