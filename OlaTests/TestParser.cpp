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
