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

TEST(Sema, DerefNonPointer_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = 5; int y = *x; }");
}

TEST(Sema, DerefPointer_Ok)
{
	EXPECT_SEMA_OK("void foo() { int* p = new int; *p = 10; delete p; }");
}

TEST(Sema, PtrSubclassAssignment_Ok)
{
	EXPECT_SEMA_OK(
		"class Base { public int x; };"
		"class Derived : Base { public int y; };"
		"void foo() { Derived* d = new Derived; Base* b = d; delete d; }"
	);
}

TEST(Sema, PtrUnrelatedAssignment_Error)
{
	EXPECT_SEMA_ERROR(
		"class A { public int x; };"
		"class B { public int y; };"
		"void foo() { A* a = new A; B* b = a; delete a; }"
	);
}

TEST(Sema, NewCtorArgs_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo { Foo(int x) { this.val = x; } public int val; };"
		"void bar() { Foo* f = new Foo(42); delete f; }"
	);
}

TEST(Sema, NewCtorArgsMismatch_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { Foo(int x) { this.val = x; } public int val; };"
		"void bar() { Foo* f = new Foo(1, 2, 3); delete f; }"
	);
}

TEST(Sema, NewCtorOnNonClass_Ok)
{
	EXPECT_SEMA_OK("void foo() { int* p = new int(42); }");
}

// A method defined earlier calling one defined later, previously would fail
// with "undeclared identifier" during the second parse pass
TEST(Sema, ClassMethodForwardReference_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo {"
		"  public int Bar() { return Baz(); }"
		"  public int Baz() { return 42; }"
		"};"
	);
}

TEST(Sema, ClassMethodReverseOrder_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo {"
		"  public int Baz() { return 42; }"
		"  public int Bar() { return Baz(); }"
		"};"
	);
}

TEST(Sema, ClassMethodChainedForwardReference_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo {"
		"  public int A() { return B(); }"
		"  public int B() { return C(); }"
		"  public int C() { return 1; }"
		"};"
	);
}

TEST(Sema, TemplateClassMethodForwardReference_Ok)
{
	EXPECT_SEMA_OK(
		"class Box<T> {"
		"  public T Double(T x) { return Mul(x, 2); }"
		"  public T Mul(T a, T b) { return a * b; }"
		"};"
		"void foo() { Box<int> b; b.Double(3); }"
	);
}


TEST(Sema, ClassByValueField_Ok)
{
	EXPECT_SEMA_OK(
		"class Inner { public int x; };"
		"class Outer { Inner inner; };"
	);
}

TEST(Sema, ClassConstructorExprAsRValue_Ok)
{
	EXPECT_SEMA_OK(
		"class Vec { Vec(int x) { this.x = x; } public int x; };"
		"class Wrapper {"
		"  Vec v;"
		"  Wrapper(int n) { v = Vec(n); }"
		"};"
	);
}

TEST(Sema, MethodReturningClassByValue_Ok)
{
	EXPECT_SEMA_OK(
		"class Point { Point(int x) { this.x = x; } public int x; };"
		"class Factory {"
		"  public Point Make(int n) { return Point(n); }"
		"};"
	);
}

TEST(Sema, UndeclaredClassField_Error)
{
	EXPECT_SEMA_ERROR(
		"class Outer { Undeclared inner; };"
	);
}

// modifying_rvalue_expr
TEST(Sema, AssignToLiteral_Error)
{
	EXPECT_SEMA_ERROR("void foo() { 42 = 1; }");
}

// pure_must_be_virtual
TEST(Sema, PureWithoutVirtual_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public void Draw() pure; };"
	);
}

// final_must_be_virtual
TEST(Sema, FinalWithoutVirtual_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public void Draw() final {} };"
	);
}

// pure_cannot_be_final
TEST(Sema, PureAndFinal_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public void Draw() virtual pure final; };"
	);
}

// pure_method_cannot_have_body
TEST(Sema, PureMethodWithBody_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public void Draw() virtual pure {} };"
	);
}

TEST(Sema, VirtualPureMethod_Ok)
{
	EXPECT_SEMA_OK(
		"class Foo { public void Draw() virtual pure; };"
	);
}

TEST(Sema, VirtualFinalMethod_Ok)
{
	EXPECT_SEMA_OK(
		"class Base { public void Draw() virtual {} };"
		"class Derived : Base { public void Draw() virtual final {} };"
	);
}

// variable_type_abstract — cannot instantiate abstract class by value
TEST(Sema, InstantiateAbstractClass_Error)
{
	EXPECT_SEMA_ERROR(
		"class Abs { public void Do() virtual pure; };"
		"void foo() { Abs a; }"
	);
}

// base_final_error — inheriting from a final class
TEST(Sema, InheritFromFinalClass_Error)
{
	EXPECT_SEMA_ERROR(
		"final class Base { public int x; };"
		"class Derived : Base { public int y; };"
	);
}

// cannot_override_final_function
TEST(Sema, OverrideFinalMethod_Error)
{
	EXPECT_SEMA_ERROR(
		"class Base { public void Foo() virtual final {} };"
		"class Derived : Base { public void Foo() virtual {} };"
	);
}

// constructor_return_type_error
TEST(Sema, ConstructorWithReturnType_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public int Foo() {} };"
	);
}

// ref_var_needs_init
TEST(Sema, RefWithoutInit_Error)
{
	EXPECT_SEMA_ERROR("void foo() { ref int r; }");
}

// ref_var_rvalue_bind — reference cannot bind to rvalue
TEST(Sema, RefBindToRvalue_Error)
{
	EXPECT_SEMA_ERROR("void foo() { ref int r = 42; }");
}

// global_ref_not_allowed
TEST(Sema, GlobalRef_Error)
{
	EXPECT_SEMA_ERROR("int g = 0; ref int r = g;");
}

TEST(Sema, RefLocalVariable_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 5; ref int r = x; }");
}

// template_arg_count_mismatch
TEST(Sema, TemplateArgCountMismatch_Error)
{
	EXPECT_SEMA_ERROR(
		"class Box<T> { public T val; };"
		"void foo() { Box<int, float> b; }"
	);
}

// template_arg_missing
TEST(Sema, TemplateArgMissing_Error)
{
	EXPECT_SEMA_ERROR(
		"class Box<T> { public T val; };"
		"void foo() { Box b; }"
	);
}

// non_template_with_args
TEST(Sema, NonTemplateWithArgs_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public int x; };"
		"void foo() { Foo<int> f; }"
	);
}

TEST(Sema, TemplateInstantiation_Ok)
{
	EXPECT_SEMA_OK(
		"class Box<T> { public T val; };"
		"void foo() { Box<int> b; }"
	);
}

// delete_arg_not_pointer
TEST(Sema, DeleteNonPointer_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = 5; delete x; }");
}

// null_assigned_to_non_pointer
TEST(Sema, NullToNonPointer_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = null; }");
}

TEST(Sema, NullToPointer_Ok)
{
	EXPECT_SEMA_OK("void foo() { int* p = null; }");
}

// new_invalid_type — cannot allocate void
TEST(Sema, NewVoid_Error)
{
	EXPECT_SEMA_ERROR("void foo() { void* p = new void; }");
}

// array_subscript_not_integer
TEST(Sema, ArraySubscriptNotInteger_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int[3] a; int x = a[1.5]; }");
}

// length_operand_not_array
TEST(Sema, LengthOnNonArray_Error)
{
	EXPECT_SEMA_ERROR("void foo() { int x = 5; int n = length(x); }");
}

TEST(Sema, LengthOnArray_Ok)
{
	EXPECT_SEMA_OK("void foo() { int[5] a; int n = length(a); }");
}

// incompatible_function_attributes — inline + noinline
TEST(Sema, InlineAndNoinline_Error)
{
	EXPECT_SEMA_ERROR("inline noinline void foo() {}");
}

// function_attribute_repetition
TEST(Sema, DuplicateFunctionAttribute_Error)
{
	EXPECT_SEMA_ERROR("inline inline void foo() {}");
}

// function_def_cannot_be_extern
TEST(Sema, ExternWithBody_Error)
{
	EXPECT_SEMA_ERROR("extern void foo() {}");
}

// function_decl_needs_to_be_extern
TEST(Sema, DeclWithoutExtern_Error)
{
	EXPECT_SEMA_ERROR("void foo();");
}

// ternary_expr_types_incompatible
TEST(Sema, TernaryTypeMismatch_Error)
{
	EXPECT_SEMA_ERROR(
		"class A { public int x; };"
		"class B { public int y; };"
		"void foo() { A a; B b; auto r = true ? a : b; }"
	);
}

TEST(Sema, TernarySameTypes_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = true ? 1 : 2; }");
}

// super_used_in_wrong_context
TEST(Sema, SuperWithoutBaseClass_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { Foo() { super(); } };"
	);
}

// method_cannot_be_nomangle
TEST(Sema, MethodNomangle_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public nomangle void Bar() {} };"
	);
}

// non_pure_method_needs_definition
TEST(Sema, NonPureMethodNoBody_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public void Bar() virtual; };"
	);
}

TEST(Sema, SizeofInt_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = sizeof(int); }");
}

TEST(Sema, EnumMemberAccess_Ok)
{
	EXPECT_SEMA_OK(
		"enum Color { Red, Green, Blue };"
		"void foo() { Color c = Red; }"
	);
}

TEST(Sema, IntToFloatImplicitCast_Ok)
{
	EXPECT_SEMA_OK("void foo() { float f = 42; }");
}

TEST(Sema, BoolToIntImplicitCast_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = true; }");
}

TEST(Sema, ConstArrayDecl_Ok)
{
	EXPECT_SEMA_OK("void foo() { const int[3] a; }");
}

TEST(Sema, ForeachOnArray_Ok)
{
	EXPECT_SEMA_OK(
		"void foo() { int[5] a; foreach (int x : a) {} }"
	);
}

TEST(Sema, ForeachOnNonArray_Error)
{
	EXPECT_SEMA_ERROR(
		"void foo() { int x = 5; foreach (int y : x) {} }"
	);
}

TEST(Sema, ForeachTypeMismatch_Error)
{
	EXPECT_SEMA_ERROR(
		"class Foo { public int x; };"
		"void bar() { int[5] a; foreach (Foo x : a) {} }"
	);
}

TEST(Sema, IncompatibleFunctionArgument_Error)
{
	EXPECT_SEMA_ERROR(
		"class A { public int x; };"
		"void bar(A a) {}"
		"void foo() { bar(42); }"
	);
}

TEST(Sema, FunctionOverloadResolution_Ok)
{
	EXPECT_SEMA_OK(
		"void bar(int x) {}"
		"void bar(float x) {}"
		"void foo() { bar(42); bar(3.14); }"
	);
}

TEST(Sema, RefAssignThrough_Ok)
{
	// r = b assigns the value of b through the reference to a, not rebinding
	EXPECT_SEMA_OK(
		"void foo() { int a = 1; int b = 2; ref int r = a; r = b; }"
	);
}

TEST(Sema, RefParamMutation_Ok)
{
	EXPECT_SEMA_OK(
		"void inc(ref int x) { x = x + 1; }"
		"void foo() { int a = 5; inc(a); }"
	);
}

TEST(Sema, FloatToIntImplicit_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 3.14; }");
}

TEST(Sema, IntToBoolImplicit_Ok)
{
	EXPECT_SEMA_OK("void foo() { bool b = 42; }");
}
TEST(Sema, VariableShadowingInNestedScope_Ok)
{
	EXPECT_SEMA_OK(
		"void foo() {"
		"  int x = 1;"
		"  if (x > 0) {"
		"    int x = 2;"
		"  }"
		"}"
	);
}

TEST(Sema, VariableUsedAfterScope_Error)
{
	EXPECT_SEMA_ERROR(
		"void foo() {"
		"  if (true) { int x = 1; }"
		"  int y = x;"
		"}"
	);
}

TEST(Sema, AutoInferInt_Ok)
{
	EXPECT_SEMA_OK("void foo() { auto x = 42; }");
}

TEST(Sema, AutoInferFloat_Ok)
{
	EXPECT_SEMA_OK("void foo() { auto x = 3.14; }");
}

TEST(Sema, AutoInferBool_Ok)
{
	EXPECT_SEMA_OK("void foo() { auto x = true; }");
}

TEST(Sema, NewCtorArgCountMismatch_Error)
{
	// Constructor takes (int, int) but called with 3 args via new
	EXPECT_SEMA_ERROR(
		"class Foo { Foo(int x, int y) { this.val = x; } public int val; };"
		"void bar() { Foo* f = new Foo(1, 2, 3); delete f; }"
	);
}

TEST(Sema, ClassWithVirtualAndOverride_Ok)
{
	EXPECT_SEMA_OK(
		"class Base { public int Get() virtual { return 0; } };"
		"class Derived : Base { public int Get() virtual { return 1; } };"
	);
}

TEST(Sema, AbstractClassPointer_Ok)
{
	EXPECT_SEMA_OK(
		"class Abs { public void Do() virtual pure; };"
		"class Concrete : Abs { public void Do() virtual {} };"
		"void foo() { Concrete c; }"
	);
}

TEST(Sema, BitwiseOrWithFloat_Error)
{
	EXPECT_SEMA_ERROR("void foo() { float x = 1.5; int y = x | 1; }");
}

TEST(Sema, BitwiseXorWithFloat_Error)
{
	EXPECT_SEMA_ERROR("void foo() { float x = 1.5; int y = x ^ 1; }");
}

TEST(Sema, BitwiseNotOnFloat_Ok)
{
	// ~float implicitly casts to int, then applies bitwise not
	EXPECT_SEMA_OK("void foo() { float x = 1.5; int y = ~x; }");
}

TEST(Sema, ArrayLargeIndex_Error)
{
	// Constant index 100 is clearly outside bounds for size-3 array
	EXPECT_SEMA_ERROR("void foo() { int[3] a; int x = a[100]; }");
}

TEST(Sema, EnumMemberUndeclared_Error)
{
	EXPECT_SEMA_ERROR(
		"enum Color { Red, Green, Blue };"
		"void foo() { Color c = Purple; }"
	);
}

TEST(Sema, EnumUsedAsInt_Ok)
{
	EXPECT_SEMA_OK(
		"enum Color { Red, Green, Blue };"
		"void foo() { int x = Red; }"
	);
}

TEST(Sema, ChainedArithmeticOperations_Ok)
{
	EXPECT_SEMA_OK("void foo() { int x = 1 + 2 * 3 - 4 / 2; }");
}

TEST(Sema, NestedFunctionCalls_Ok)
{
	EXPECT_SEMA_OK(
		"int add(int a, int b) { return a + b; }"
		"int mul(int a, int b) { return a * b; }"
		"void foo() { int r = add(mul(2, 3), mul(4, 5)); }"
	);
}

TEST(Sema, CompoundAssignOnConst_Error)
{
	EXPECT_SEMA_ERROR("void foo() { const int x = 5; x += 1; }");
}

TEST(Sema, IncrementConst_Error)
{
	EXPECT_SEMA_ERROR("void foo() { const int x = 5; x++; }");
}

TEST(Sema, DeleteNull_Ok)
{
	EXPECT_SEMA_OK("void foo() { int* p = null; delete p; }");
}

TEST(Sema, NewArrayType_Ok)
{
	EXPECT_SEMA_OK("void foo() { int* p = new int(10); }");
}

TEST(Sema, ExternDeclaration_Ok)
{
	EXPECT_SEMA_OK("extern void puts(const char[] s);");
}

TEST(Sema, FunctionCallOrder_CalleeDeclaredFirst_Ok)
{
	// Functions must be declared before being called at global scope
	EXPECT_SEMA_OK(
		"void bar() { }"
		"void foo() { bar(); }"
	);
}

TEST(Sema, SwitchOnEnum_Ok)
{
	EXPECT_SEMA_OK(
		"enum Color { Red, Green, Blue };"
		"void foo(Color c) { switch (c) { case 0: break; case 1: break; default: break; } }"
	);
}

TEST(Sema, MultiLevelInheritance_Ok)
{
	EXPECT_SEMA_OK(
		"class A { public int x; };"
		"class B : A { public int y; };"
		"class C : B { public int z; };"
	);
}

TEST(Sema, VirtualOverrideChain_Ok)
{
	EXPECT_SEMA_OK(
		"class A { public int Do() virtual { return 0; } };"
		"class B : A { public int Do() virtual { return 1; } };"
		"class C : B { public int Do() virtual { return 2; } };"
	);
}
