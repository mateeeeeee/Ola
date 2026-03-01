#include <gtest/gtest.h>
#include "Frontend/Lexer.h"
#include "Frontend/Parser.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/FrontendContext.h"

using namespace ola;

// ---------------------------------------------------------------------------
// Harness — identical to the one used in TestParser.cpp.
// Diagnostics(false, false): warnings_as_errors=false, exit_on_error=false.
// The parser runs Sema internally during Parse().
// ---------------------------------------------------------------------------

struct SemaHelper
{
	Diagnostics     diag;
	FrontendContext ctx;
	Parser          parser;

	explicit SemaHelper(std::string_view src)
		: diag(false, false), ctx(), parser(&ctx, diag)
	{
		SourceBuffer buf(src.data(), src.size(), "<test>");
		Lexer lexer(diag);
		lexer.Lex(buf);
		parser.Parse(lexer.GetTokens());
	}

	Bool HasErrors() const { return diag.HasErrors(); }
};

// Convenience macros so each test reads like a sentence.
#define EXPECT_SEMA_ERROR(src)  { SemaHelper h(src); EXPECT_TRUE(h.HasErrors());  }
#define EXPECT_SEMA_OK(src)     { SemaHelper h(src); EXPECT_FALSE(h.HasErrors()); }

// ===========================================================================
// Variable / Declaration diagnostics
// ===========================================================================

// redefinition_of_identifier
TEST(Sema, RedefinitionOfIdentifier_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = 1; int x = 2; }");
}

TEST(Sema, RedefinitionOfIdentifier_DifferentScopes_Ok)
{
	// The same name in two separate functions is fine.
	EXPECT_SEMA_OK("void foo() { int x = 1; } void bar() { int x = 2; }");
}

// undeclared_identifier
TEST(Sema, UndeclaredIdentifier_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int y = x; }");
}

TEST(Sema, UndeclaredIdentifier_DeclaredFirst_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 1; int y = x; }");
}

// modifying_const_expr
TEST(Sema, ModifyingConstVar_Error)
{
	EXPECT_SEMA_ERROR("void foo() { const int x = 1; x = 2; }");
}

TEST(Sema, ModifyingNonConstVar_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 1; x = 2; }");
}

// void_invalid_context  — void used as a variable type
TEST(Sema, VoidVariableDeclaration_Error)
{
	EXPECT_SEMA_ERROR("void foo() { void x; }");
}

// global_variable_initializer_not_constexpr
TEST(Sema, GlobalInitializerNonConstExpr_Error)
{
	// A global variable cannot be initialized with the result of a function call.
	EXPECT_SEMA_ERROR("int helper() { return 5; } int g = helper();");
}

TEST(Sema, GlobalInitializerLiteral_Ok)
{
	EXPECT_SEMA_OK("int g = 42;");
}

// ===========================================================================
// Return statement diagnostics
// ===========================================================================

// incompatible_return_stmt_type — returning a value from a void function
TEST(Sema, ReturnValueFromVoidFunction_Error)
{
	EXPECT_SEMA_ERROR("void foo() { return 42; }");
}

// incompatible_return_stmt_type — returning no value from a non-void function
TEST(Sema, ReturnWithNoValueFromNonVoidFunction_Error)
{
	EXPECT_SEMA_ERROR("int foo() { return; }");
}

TEST(Sema, ReturnMatchingType_Ok)
{
	EXPECT_SEMA_OK("int foo() { return 42; }");
}

TEST(Sema, ReturnVoidFromVoidFunction_Ok)
{
	EXPECT_SEMA_OK("void foo() { return; }");
}

// ===========================================================================
// Control flow diagnostics
// ===========================================================================

// stray_break
TEST(Sema, BreakOutsideLoop_Error)
{
	EXPECT_SEMA_ERROR("void foo() { break; }");
}

TEST(Sema, BreakInsideLoop_Ok)
{
	EXPECT_SEMA_OK("void foo() { for (int i = 0; i < 10; ++i) { break; } }");
}

TEST(Sema, BreakInsideSwitch_Ok)
{
	EXPECT_SEMA_OK("void foo(int x) { switch (x) { case 0: break; default: break; } }");
}

// stray_continue
TEST(Sema, ContinueOutsideLoop_Error)
{
	EXPECT_SEMA_ERROR("void foo() { continue; }");
}

TEST(Sema, ContinueInsideLoop_Ok)
{
	EXPECT_SEMA_OK("void foo() { for (int i = 0; i < 10; ++i) { continue; } }");
}

// duplicate_case_value
TEST(Sema, DuplicateCaseValue_Error)
{
	EXPECT_SEMA_ERROR("void foo(int x) { switch (x) { case 1: break; case 1: break; } }");
}

TEST(Sema, UniqueCaseValues_Ok)
{
	EXPECT_SEMA_OK("void foo(int x) { switch (x) { case 1: break; case 2: break; } }");
}

// duplicate_default_case
TEST(Sema, DuplicateDefaultCase_Error)
{
	EXPECT_SEMA_ERROR("void foo(int x) { switch (x) { default: break; default: break; } }");
}

TEST(Sema, SingleDefaultCase_Ok)
{
	EXPECT_SEMA_OK("void foo(int x) { switch (x) { case 1: break; default: break; } }");
}

// undeclared_label  — goto target does not exist
TEST(Sema, GotoUndeclaredLabel_Error)
{
	EXPECT_SEMA_ERROR("void foo() { goto done; }");
}

TEST(Sema, GotoDeclaredLabel_Ok)
{
	EXPECT_SEMA_OK("void foo() { goto done; done: return; }");
}

// redefinition_of_label
TEST(Sema, RedefinitionOfLabel_Error)
{
	EXPECT_SEMA_ERROR("void foo() { L: int x = 1; L: int y = 2; }");
}

// ===========================================================================
// Operator type diagnostics
// ===========================================================================

// shift_operands_not_integral — float in shift
TEST(Sema, ShiftWithFloatOperand_Error)
{
	EXPECT_SEMA_ERROR("void foo() { float x = 1.5; int y = x << 2; }");
}

TEST(Sema, ShiftWithIntOperands_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 4; int y = x << 2; }");
}

// bitwise_operands_not_integral — float in bitwise op
TEST(Sema, BitwiseAndWithFloatOperand_Error)
{
	EXPECT_SEMA_ERROR("void foo() { float x = 1.5; int y = x & 1; }");
}

TEST(Sema, BitwiseAndWithIntOperands_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 3; int y = x & 1; }");
}

// modulo_operands_not_integral — float in modulo
TEST(Sema, ModuloWithFloatOperand_Error)
{
	EXPECT_SEMA_ERROR("void foo() { float x = 1.5; int y = x % 2; }");
}

TEST(Sema, ModuloWithIntOperands_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 7; int y = x % 3; }");
}

// bool_forbidden_in_increment
TEST(Sema, BoolIncrement_Error)
{
	EXPECT_SEMA_ERROR("void foo() { bool b = true; b++; }");
}

TEST(Sema, IntIncrement_Ok)
{
	EXPECT_SEMA_OK("void foo() { int i = 0; i++; }");
}

// ===========================================================================
// Function call diagnostics
// ===========================================================================

// too_many_args_to_function_call
TEST(Sema, TooManyArgs_Error)
{
	EXPECT_SEMA_ERROR("void bar(int x) {} void foo() { bar(1, 2); }");
}

// too_few_args_to_function_call
TEST(Sema, TooFewArgs_Error)
{
	EXPECT_SEMA_ERROR("void bar(int x, int y) {} void foo() { bar(1); }");
}

TEST(Sema, ExactArgCount_Ok)
{
	EXPECT_SEMA_OK("void bar(int x, int y) {} void foo() { bar(1, 2); }");
}

// ===========================================================================
// Array diagnostics
// ===========================================================================

// array_index_outside_of_bounds — constant index beyond declared size
TEST(Sema, ArrayIndexOutOfBounds_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int[3] a; int x = a[5]; }");
}

TEST(Sema, ArrayIndexInBounds_Ok)
{
	EXPECT_SEMA_OK("void foo() { int[3] a; int x = a[2]; }");
}

// subscripted_value_not_array — indexing a non-array
TEST(Sema, SubscriptOnNonArray_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = 5; int y = x[0]; }");
}

// array_size_not_positive
TEST(Sema, ArraySizeZero_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int[0] a; }");
}

TEST(Sema, ArraySizePositive_Ok)
{
	EXPECT_SEMA_OK("void foo() { int[4] a; }");
}

// ===========================================================================
// Class / member access diagnostics
// ===========================================================================

// private_member_access
TEST(Sema, AccessPrivateMember_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { private int x; };"
		"void bar() { Foo f; int v = f.x; }"
	);
}

TEST(Sema, AccessPublicMember_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo { public int x; };"
		"void bar() { Foo f; int v = f.x; }"
	);
}
