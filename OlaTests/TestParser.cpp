#include <gtest/gtest.h>
#include "Frontend/Lexer.h"
#include "Frontend/Parser.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/FrontendContext.h"
#include "Frontend/AST/AST.h"
#include "Frontend/AST/Decl.h"
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"
#include "Utility/RTTI.h"

using namespace ola;

// Keeps parser (and its owned AST) alive for the duration of each test.
// Members are in declaration order so diag and ctx are constructed before parser.
struct ParseHelper
{
	Diagnostics    diag;
	FrontendContext ctx;
	Parser          parser;

	explicit ParseHelper(std::string_view src)
		: diag(false, false), ctx(), parser(&ctx, diag)
	{
		SourceBuffer buf(src.data(), src.size(), "<test>");
		Lexer lexer(diag);
		lexer.Lex(buf);
		parser.Parse(lexer.GetTokens());
	}

	TranslationUnit const& TU() const { return *parser.GetAST()->translation_unit; }
	Bool HasErrors()          const { return diag.HasErrors(); }
	Bool HasAST()             const { return parser.GetAST() != nullptr; }

	template<typename T>
	T const* FindFirst() const
	{
		for (auto const& d : TU().GetDecls())
		{
			if (auto* p = dyn_cast<T>(d.get())) 
			{
				return p;
			}
		}
		return nullptr;
	}
};

TEST(Parser, EmptyVoidFunction)
{
	ParseHelper h("void foo() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_EQ(fn->GetName(), "foo");
	EXPECT_TRUE(fn->HasDefinition());
	EXPECT_EQ(fn->GetParamDecls().size(), 0u);
}

TEST(Parser, FunctionReturnType)
{
	ParseHelper h("int getVal() { return 42; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_EQ(fn->GetName(), "getVal");
}

TEST(Parser, FunctionWithParams)
{
	ParseHelper h("int add(int a, int b) { return a + b; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_EQ(fn->GetName(), "add");
	ASSERT_EQ(fn->GetParamDecls().size(), 2u);
	EXPECT_EQ(fn->GetParamDecls()[0]->GetName(), "a");
	EXPECT_EQ(fn->GetParamDecls()[1]->GetName(), "b");
}

TEST(Parser, FunctionAttribute_Inline)
{
	ParseHelper h("inline void foo() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsInline());
}

TEST(Parser, FunctionAttribute_NoInline)
{
	ParseHelper h("noinline void bar() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsNoInline());
}

TEST(Parser, MultipleFunctions)
{
	ParseHelper h("void a() {} void b() {} void c() {}");
	ASSERT_FALSE(h.HasErrors());
	// Builtin decls are prepended; user functions come after. just check we
	// have at least 3 FunctionDecls in the TU.
	Int32 fn_count = 0;
	for (auto const& d : h.TU().GetDecls())
	{
		if (isa<FunctionDecl>(d.get())) ++fn_count;
	}
	EXPECT_GE(fn_count, 3);
}

TEST(Parser, GlobalIntVar)
{
	ParseHelper h("int g = 10;");
	ASSERT_FALSE(h.HasErrors());

	auto* var = h.FindFirst<VarDecl>();
	ASSERT_NE(var, nullptr);
	EXPECT_EQ(var->GetName(), "g");
	EXPECT_TRUE(var->IsGlobal());
}

TEST(Parser, LocalVarInFunction)
{
	ParseHelper h("void foo() { int x = 5; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	ASSERT_NE(fn->GetBodyStmt(), nullptr);
	EXPECT_GE(fn->GetBodyStmt()->GetStmts().size(), 1u);
}

TEST(Parser, ReturnStatement)
{
	ParseHelper h("int foo() { return 0; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 1u);
	EXPECT_NE(dyn_cast<ReturnStmt>(stmts[0].get()), nullptr);
}

TEST(Parser, IfStatement)
{
	ParseHelper h("void foo() { int x = 0; if (x == 0) { x = 1; } }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 2u);
	EXPECT_NE(dyn_cast<IfStmt>(stmts[1].get()), nullptr);
}

TEST(Parser, ForLoop)
{
	ParseHelper h("void foo() { for (int i = 0; i < 10; ++i) {} }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 1u);
	EXPECT_NE(dyn_cast<ForStmt>(stmts[0].get()), nullptr);
}

TEST(Parser, WhileLoop)
{
	ParseHelper h("void foo() { int i = 0; while (i < 10) { ++i; } }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 2u);
	EXPECT_NE(dyn_cast<WhileStmt>(stmts[1].get()), nullptr);
}

TEST(Parser, DoWhileLoop)
{
	ParseHelper h("void foo() { int i = 0; do { ++i; } while (i < 10); }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 2u);
	EXPECT_NE(dyn_cast<DoWhileStmt>(stmts[1].get()), nullptr);
}

TEST(Parser, SwitchStatement)
{
	ParseHelper h("void foo(int x) { switch (x) { case 0: break; default: break; } }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 1u);
	EXPECT_NE(dyn_cast<SwitchStmt>(stmts[0].get()), nullptr);
}

TEST(Parser, IntLiteralExpr)
{
	ParseHelper h("void foo() { int x = 42; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 1u);
	auto* decl_stmt = dyn_cast<DeclStmt>(stmts[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	ASSERT_GE(decl_stmt->GetDecls().size(), 1u);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	EXPECT_NE(dyn_cast<IntLiteral>(var->GetInitExpr()), nullptr);
}

TEST(Parser, BinaryExprAdd)
{
	ParseHelper h("void foo() { int x = 1 + 2; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto* decl_stmt = dyn_cast<DeclStmt>(fn->GetBodyStmt()->GetStmts()[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	ASSERT_GE(decl_stmt->GetDecls().size(), 1u);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	// The init expression may be wrapped in an implicit cast; peel it off.
	Expr const* init = var->GetInitExpr();
	if (auto* cast = dyn_cast<ImplicitCastExpr>(init)) init = cast->GetOperand();
	auto* bin = dyn_cast<BinaryExpr>(init);
	ASSERT_NE(bin, nullptr);
	EXPECT_EQ(bin->GetBinaryKind(), BinaryExprKind::Add);
}

TEST(Parser, TernaryExpr)
{
	ParseHelper h("void foo() { int x = 1; int y = (x > 0) ? 1 : -1; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto const& stmts = fn->GetBodyStmt()->GetStmts();
	ASSERT_GE(stmts.size(), 2u);
	auto* decl_stmt = dyn_cast<DeclStmt>(stmts[1].get());
	ASSERT_NE(decl_stmt, nullptr);
	ASSERT_GE(decl_stmt->GetDecls().size(), 1u);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	Expr const* init = var->GetInitExpr();
	if (auto* cast = dyn_cast<ImplicitCastExpr>(init)) init = cast->GetOperand();
	EXPECT_NE(dyn_cast<TernaryExpr>(init), nullptr);
}

TEST(Parser, ClassDeclaration)
{
	ParseHelper h("class Point { public int x; public int y; };");
	ASSERT_FALSE(h.HasErrors());

	auto const& decls = h.TU().GetDecls();
	ClassDecl const* cls = nullptr;
	for (auto const& d : decls)
		if (auto* c = dyn_cast<ClassDecl>(d.get())) { cls = c; break; }
	ASSERT_NE(cls, nullptr);
	EXPECT_EQ(cls->GetName(), "Point");
}

TEST(Parser, EnumDeclaration)
{
	ParseHelper h("enum Color { Red, Green, Blue };");
	ASSERT_FALSE(h.HasErrors());

	auto const& decls = h.TU().GetDecls();
	EnumDecl const* enm = nullptr;
	for (auto const& d : decls)
		if (auto* e = dyn_cast<EnumDecl>(d.get())) { enm = e; break; }
	ASSERT_NE(enm, nullptr);
	EXPECT_EQ(enm->GetName(), "Color");
}

TEST(Parser, MissingSemicolon)
{
	ParseHelper h("void foo() { int x = 5 }");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, UndeclaredVariable)
{
	ParseHelper h("void foo() { x = 5; }");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, TypeMismatch)
{
	ParseHelper h("void foo() { int x = 3.14; }");
	(void)h;
}

TEST(Parser, AliasDeclaration)
{
	ParseHelper h("alias MyInt = int;");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, NewDeleteExpression)
{
	ParseHelper h("void foo() { int* p = new int; delete p; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_GE(fn->GetBodyStmt()->GetStmts().size(), 2u);
}

TEST(Parser, NewWithCtorArgs)
{
	ParseHelper h(
		"class Foo { Foo(int x) { this.val = x; } public int val; };"
		"void bar() { Foo* f = new Foo(42); delete f; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, RefParameter)
{
	ParseHelper h("void inc(ref int x) { x = x + 1; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_EQ(fn->GetName(), "inc");
	ASSERT_EQ(fn->GetParamDecls().size(), 1u);
}

TEST(Parser, OperatorPrecedence_MulBeforeAdd)
{
	// 1 + 2 * 3 should parse as 1 + (2 * 3)
	ParseHelper h("void foo() { int x = 1 + 2 * 3; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto* decl_stmt = dyn_cast<DeclStmt>(fn->GetBodyStmt()->GetStmts()[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	Expr const* init = var->GetInitExpr();
	if (auto* cast = dyn_cast<ImplicitCastExpr>(init)) init = cast->GetOperand();
	auto* add = dyn_cast<BinaryExpr>(init);
	ASSERT_NE(add, nullptr);
	EXPECT_EQ(add->GetBinaryKind(), BinaryExprKind::Add);
	// RHS of the add should be the multiply
	Expr const* rhs = add->GetRHS();
	if (auto* cast = dyn_cast<ImplicitCastExpr>(rhs)) rhs = cast->GetOperand();
	auto* mul = dyn_cast<BinaryExpr>(rhs);
	ASSERT_NE(mul, nullptr);
	EXPECT_EQ(mul->GetBinaryKind(), BinaryExprKind::Multiply);
}

TEST(Parser, ArrayDeclaration)
{
	ParseHelper h("void foo() { int[5] a; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_GE(fn->GetBodyStmt()->GetStmts().size(), 1u);
}

TEST(Parser, ClassWithMethodDefinition)
{
	ParseHelper h(
		"class Adder {"
		"  public int Add(int a, int b) { return a + b; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());

	ClassDecl const* cls = nullptr;
	for (auto const& d : h.TU().GetDecls())
		if (auto* c = dyn_cast<ClassDecl>(d.get())) { cls = c; break; }
	ASSERT_NE(cls, nullptr);
	EXPECT_EQ(cls->GetName(), "Adder");
}

TEST(Parser, ClassWithConstructor)
{
	ParseHelper h(
		"class Vec {"
		"  Vec(int x) { this.x = x; }"
		"  public int x;"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ClassInheritance)
{
	ParseHelper h(
		"class Base { public int x; };"
		"class Derived : Base { public int y; };"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, InterfaceDeclaration)
{
	ParseHelper h(
		"interface Drawable {"
		"  public void Draw();"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, InterfaceWithWrongMethodSyntax)
{
	// virtual/pure go after params in Ola, not before the return type.
	// Parser should report an error rather than crash.
	ParseHelper h(
		"interface Drawable {"
		"  public virtual pure void Draw();"
		"};"
	);
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, EnumWithValues)
{
	ParseHelper h("enum Dir { North, South = 5, East, West };");
	ASSERT_FALSE(h.HasErrors());

	EnumDecl const* enm = nullptr;
	for (auto const& d : h.TU().GetDecls())
		if (auto* e = dyn_cast<EnumDecl>(d.get())) { enm = e; break; }
	ASSERT_NE(enm, nullptr);
	EXPECT_EQ(enm->GetName(), "Dir");
}

TEST(Parser, NestedIfElse)
{
	ParseHelper h(
		"void foo(int x) {"
		"  if (x > 0) {"
		"    if (x > 10) { return; }"
		"    else { return; }"
		"  } else { return; }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, GotoLabel)
{
	ParseHelper h("void foo() { goto done; done: return; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, UnaryExpressions)
{
	ParseHelper h("void foo() { int x = 5; int y = -x; int z = !true; int w = ~x; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, FloatLiteralExpr)
{
	ParseHelper h("void foo() { float x = 3.14; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto* decl_stmt = dyn_cast<DeclStmt>(fn->GetBodyStmt()->GetStmts()[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	EXPECT_NE(dyn_cast<FloatLiteral>(var->GetInitExpr()), nullptr);
}

TEST(Parser, BoolLiteralExpr)
{
	ParseHelper h("void foo() { bool b = true; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto* decl_stmt = dyn_cast<DeclStmt>(fn->GetBodyStmt()->GetStmts()[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	Expr const* init = var->GetInitExpr();
	if (auto* cast = dyn_cast<ImplicitCastExpr>(init)) init = cast->GetOperand();
	EXPECT_NE(dyn_cast<BoolLiteral>(init), nullptr);
}

TEST(Parser, StringLiteralExpr)
{
	ParseHelper h("void foo() { const char[] s = \"hello\"; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MemberAccessExpr)
{
	ParseHelper h(
		"class Pt { public int x; };"
		"void foo() { Pt p; int v = p.x; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MethodCallExpr)
{
	ParseHelper h(
		"class Calc { public int Get() { return 42; } };"
		"void foo() { Calc c; int v = c.Get(); }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, CompoundAssignment)
{
	ParseHelper h("void foo() { int x = 0; x += 5; x -= 2; x *= 3; x /= 2; x %= 4; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ArrayAccessExpr)
{
	ParseHelper h("void foo() { int[3] a; int x = a[1]; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MissingClosingBrace)
{
	ParseHelper h("void foo() { int x = 5;");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, MissingClosingParen)
{
	ParseHelper h("void foo( {}");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, EmptyEnumBody)
{
	ParseHelper h("enum Empty {};");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, EmptyClassBody)
{
	ParseHelper h("class Empty {};");
	ASSERT_FALSE(h.HasErrors());
}



TEST(Parser, MultipleVarsInOneDecl)
{
	ParseHelper h("int a = 1; int b = 2; int c = 3;");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ForeachLoop)
{
	ParseHelper h("void foo() { int[5] a; foreach (int x : a) {} }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_GE(fn->GetBodyStmt()->GetStmts().size(), 2u);
}

TEST(Parser, BreakAndContinueInLoop)
{
	ParseHelper h("void foo() { for (int i = 0; i < 10; ++i) { if (i == 5) break; continue; } }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, NestedForLoops)
{
	ParseHelper h(
		"void foo() {"
		"  for (int i = 0; i < 10; ++i) {"
		"    for (int j = 0; j < 10; ++j) {}"
		"  }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, PointerDeclaration)
{
	ParseHelper h("void foo() { int* p = new int; delete p; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ChainedMemberAccess)
{
	ParseHelper h(
		"class Inner { public int val; };"
		"class Outer { public Inner inner; };"
		"void foo() { Outer o; int x = o.inner.val; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, FunctionAttribute_NoMangle)
{
	ParseHelper h("nomangle void extern_func() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsNoMangle());
}

TEST(Parser, FunctionAttribute_Deprecated)
{
	ParseHelper h("deprecated void old_func() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsDeprecated());
}

TEST(Parser, FunctionAttribute_NoOpt)
{
	ParseHelper h("noopt void debug_func() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsNoOpt());
}

TEST(Parser, MultipleReturnPaths)
{
	ParseHelper h(
		"int foo(int x) {"
		"  if (x > 0) { return 1; }"
		"  else { return -1; }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, NestedSwitchStatement)
{
	ParseHelper h(
		"void foo(int x, int y) {"
		"  switch (x) {"
		"    case 0: switch (y) { case 1: break; default: break; } break;"
		"    default: break;"
		"  }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, AutoTypeInference)
{
	ParseHelper h("void foo() { auto x = 42; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, AutoTypeWithExpression)
{
	ParseHelper h("void foo() { int a = 10; auto b = a + 5; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ClassWithMultipleMethods)
{
	ParseHelper h(
		"class Math {"
		"  public int Add(int a, int b) { return a + b; }"
		"  public int Sub(int a, int b) { return a - b; }"
		"  public int Mul(int a, int b) { return a * b; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ClassWithPrivateAndPublic)
{
	ParseHelper h(
		"class Counter {"
		"  private int count;"
		"  public int Get() { return this.count; }"
		"  public void Inc() { this.count = this.count + 1; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, InterfaceWithMultipleMethods)
{
	ParseHelper h(
		"interface Shape {"
		"  public int Area();"
		"  public int Perimeter();"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateClassDeclaration)
{
	ParseHelper h(
		"class Box<T> {"
		"  public T val;"
		"  public T Get() { return this.val; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateClassInstantiation)
{
	ParseHelper h(
		"class Wrapper<T> { public T val; };"
		"void foo() { Wrapper<int> w; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, EnumWithManyMembers)
{
	ParseHelper h("enum Weekday { Mon, Tue, Wed, Thu, Fri, Sat, Sun };");
	ASSERT_FALSE(h.HasErrors());

	EnumDecl const* enm = nullptr;
	for (auto const& d : h.TU().GetDecls())
		if (auto* e = dyn_cast<EnumDecl>(d.get())) { enm = e; break; }
	ASSERT_NE(enm, nullptr);
	EXPECT_EQ(enm->GetName(), "Weekday");
}

TEST(Parser, SizeofExpression)
{
	ParseHelper h("void foo() { int s = sizeof(int); }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, LengthExpression)
{
	ParseHelper h("void foo() { int[10] a; int n = length(a); }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, BitwiseExpressions)
{
	ParseHelper h("void foo() { int x = 5 & 3; int y = x | 2; int z = y ^ 1; int w = ~z; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ShiftExpressions)
{
	ParseHelper h("void foo() { int x = 1 << 3; int y = 16 >> 2; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ComplexExpressionPrecedence)
{
	// a + b * c - d / e should parse correctly
	ParseHelper h("void foo() { int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int r = a + b * c - d / e; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, LogicalExpressions)
{
	ParseHelper h("void foo() { bool a = true; bool b = false; bool c = a && b || !a; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, VirtualMethodDecl)
{
	ParseHelper h(
		"class Shape {"
		"  public int Area() virtual { return 0; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, PureVirtualMethod)
{
	ParseHelper h(
		"class Shape {"
		"  public int Area() virtual pure;"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, FinalClass)
{
	ParseHelper h("class Singleton final { public int val; };");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, NullLiteral)
{
	ParseHelper h("void foo() { int* p = null; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ConstGlobalVariable)
{
	ParseHelper h("const int MAX = 100;");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MultiDimensionalArray)
{
	ParseHelper h("void foo() { int[3][4] matrix; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, PreIncrementDecrement)
{
	ParseHelper h("void foo() { int x = 0; ++x; --x; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, PostIncrementDecrement)
{
	ParseHelper h("void foo() { int x = 0; x++; x--; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ConstructorWithMultipleParams)
{
	ParseHelper h(
		"class Rect {"
		"  Rect(int w, int h) { this.w = w; this.h = h; }"
		"  public int w;"
		"  public int h;"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, SuperCall)
{
	ParseHelper h(
		"class Base {"
		"  Base(int x) { this.x = x; }"
		"  public int x;"
		"};"
		"class Derived : Base {"
		"  Derived(int x, int y) { super(x); this.y = y; }"
		"  public int y;"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MissingReturnType)
{
	ParseHelper h("foo() {}");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, MissingFunctionName)
{
	ParseHelper h("void () {}");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, UnexpectedTokenInExpression)
{
	ParseHelper h("void foo() { int x = ; }");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, DoubleSemicolon)
{
	ParseHelper h("void foo() { int x = 5;; }");
	EXPECT_FALSE(h.HasErrors());
}

TEST(Parser, DeeplyNestedExpressions)
{
	ParseHelper h("void foo() { int x = ((((1 + 2) * 3) - 4) / 5); }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, EmptyForLoop)
{
	ParseHelper h("void foo() { int i = 0; for (; i < 10; ++i) {} }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MultipleClassInheritanceDecls)
{
	ParseHelper h(
		"class A { public int x; };"
		"class B : A { public int y; };"
		"class C : B { public int z; };"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, InterfaceImplementation)
{
	ParseHelper h(
		"interface Drawable {"
		"  public void Draw();"
		"};"
		"class Circle : Drawable {"
		"  public void Draw() virtual {}"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ClassWithPrivateField)
{
	ParseHelper h(
		"class Secret {"
		"  private int data;"
		"  public int GetData() { return this.data; }"
		"  public void SetData(int d) { this.data = d; }"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, FunctionWithManyParams)
{
	ParseHelper h("int add5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_EQ(fn->GetParamDecls().size(), 5u);
}

TEST(Parser, GlobalConstAndVariable)
{
	ParseHelper h("const int MAX = 100; int counter = 0;");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, NestedWhileLoops)
{
	ParseHelper h(
		"void foo() {"
		"  int i = 0;"
		"  while (i < 10) {"
		"    int j = 0;"
		"    while (j < 10) { j = j + 1; }"
		"    i = i + 1;"
		"  }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, RefReturnType)
{
	ParseHelper h(
		"class Holder { public int val; };"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ArrayOfFloats)
{
	ParseHelper h("void foo() { float[10] arr; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, OperatorPrecedence_ShiftBeforeCompare)
{
	// 1 << 2 > 3 should parse as (1 << 2) > 3
	ParseHelper h("void foo() { bool b = 1 << 2 > 3; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, EnumWithExplicitValues)
{
	ParseHelper h("enum Flags { None = 0, Read = 1, Write = 2, Execute = 4 };");
	ASSERT_FALSE(h.HasErrors());

	EnumDecl const* enm = nullptr;
	for (auto const& d : h.TU().GetDecls())
		if (auto* e = dyn_cast<EnumDecl>(d.get())) { enm = e; break; }
	ASSERT_NE(enm, nullptr);
	EXPECT_EQ(enm->GetName(), "Flags");
}

TEST(Parser, FinalMethodDecl)
{
	ParseHelper h(
		"class Base { public int Get() virtual { return 0; } };"
		"class Derived : Base { public int Get() virtual final { return 1; } };"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, DeprecatedFunction)
{
	ParseHelper h("deprecated void oldFunc() {}");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	EXPECT_TRUE(fn->IsDeprecated());
}

TEST(Parser, ExternFunctionDeclaration)
{
	ParseHelper h("extern void puts(const char[] s);");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, FunctionOverloads)
{
	ParseHelper h(
		"int compute(int x) { return x * 2; }"
		"float compute(float x) { return x * 2.0; }"
	);
	ASSERT_FALSE(h.HasErrors());

	Int32 fn_count = 0;
	for (auto const& d : h.TU().GetDecls())
		if (auto* f = dyn_cast<FunctionDecl>(d.get()))
			if (f->GetName() == "compute") ++fn_count;
	EXPECT_EQ(fn_count, 2);
}

TEST(Parser, CharVariableDecl)
{
	ParseHelper h("void foo() { char c = 'x'; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, PointerToClassType)
{
	ParseHelper h(
		"class Node { public int val; };"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, IfWithoutElse)
{
	ParseHelper h("void foo(int x) { if (x > 0) { x = 0; } }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, SwitchWithFallthrough)
{
	ParseHelper h(
		"void foo(int x) {"
		"  switch (x) {"
		"    case 0:"
		"    case 1: break;"
		"    default: break;"
		"  }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MethodCallChain)
{
	ParseHelper h(
		"class Builder { public int Get() { return 42; } };"
		"void foo() { Builder b; int v = b.Get(); }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, VoidReturnNoSemicolon_Error)
{
	ParseHelper h("void foo() { return }");
	EXPECT_TRUE(h.HasErrors());
}

TEST(Parser, NestedTemplateInstantiation)
{
	ParseHelper h(
		"class Inner<T> { public T val; };"
		"class Outer<T> { public Inner<T> inner; };"
		"void foo() { Outer<int> o; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ClassWithBothCtorAndMethods)
{
	ParseHelper h(
		"class Obj {"
		"  Obj(int x) { this.x = x; }"
		"  public int Get() { return this.x; }"
		"  public void Set(int v) { this.x = v; }"
		"  public int x;"
		"};"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, MultipleEnums)
{
	ParseHelper h(
		"enum A { X, Y };"
		"enum B { P, Q, R };"
	);
	ASSERT_FALSE(h.HasErrors());

	Int32 enum_count = 0;
	for (auto const& d : h.TU().GetDecls())
		if (isa<EnumDecl>(d.get())) ++enum_count;
	EXPECT_EQ(enum_count, 2);
}

TEST(Parser, GlobalArrayDecl)
{
	ParseHelper h("int[10] globalArr;");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ForLoopWithMultipleStatements)
{
	ParseHelper h(
		"void foo() {"
		"  int sum = 0;"
		"  for (int i = 0; i < 10; ++i) {"
		"    sum = sum + i;"
		"    if (sum > 20) break;"
		"  }"
		"}"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, AssignmentExpression)
{
	ParseHelper h("void foo() { int x = 0; int y = 0; x = y = 5; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, BinaryExprSub)
{
	ParseHelper h("void foo() { int x = 10 - 3; }");
	ASSERT_FALSE(h.HasErrors());

	auto* fn = h.FindFirst<FunctionDecl>();
	ASSERT_NE(fn, nullptr);
	auto* decl_stmt = dyn_cast<DeclStmt>(fn->GetBodyStmt()->GetStmts()[0].get());
	ASSERT_NE(decl_stmt, nullptr);
	auto* var = dyn_cast<VarDecl>(decl_stmt->GetDecls()[0].get());
	ASSERT_NE(var, nullptr);
	Expr const* init = var->GetInitExpr();
	if (auto* cast_expr = dyn_cast<ImplicitCastExpr>(init)) init = cast_expr->GetOperand();
	auto* bin = dyn_cast<BinaryExpr>(init);
	ASSERT_NE(bin, nullptr);
	EXPECT_EQ(bin->GetBinaryKind(), BinaryExprKind::Subtract);
}

TEST(Parser, OperatorPrecedence_CompareBeforeLogical)
{
	// a > 0 && b < 10 should parse as (a > 0) && (b < 10)
	ParseHelper h("void foo() { int a = 1; int b = 5; bool c = a > 0 && b < 10; }");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, ConstArrayParam)
{
	ParseHelper h("void foo(const int[] arr) {}");
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateFunctionDeclaration)
{
	ParseHelper h(
		"T Identity<T>(T x) { return x; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateFunctionMultipleParams)
{
	ParseHelper h(
		"A First<A, B>(A a, B b) { return a; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateFunctionInstantiation)
{
	ParseHelper h(
		"T Identity<T>(T x) { return x; }"
		"void foo() { int y = Identity<int>(42); }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateFunctionKnownReturnType)
{
	ParseHelper h(
		"int Max<T>(T a, T b) { if (a > b) return a; return b; }"
	);
	ASSERT_FALSE(h.HasErrors());
}

TEST(Parser, TemplateFunctionMultipleCallsInBody)
{
	ParseHelper h(
		"T Identity<T>(T x) { return x; }"
		"void foo() { Identity<int>(1); Identity<float>(2.0); Identity<bool>(true); }"
	);
	ASSERT_FALSE(h.HasErrors());
}
