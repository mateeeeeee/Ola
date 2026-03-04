#include "gtest/gtest.h"
#include "Compiler/CompilerMacros.h"

#define RUN_TEST OLA_TEST_INTERPRET

TEST(Interpreter_Operators, Additive)       { EXPECT_EQ(RUN_TEST(-i test_additive),       0); }
TEST(Interpreter_Operators, Multiplicative) { EXPECT_EQ(RUN_TEST(-i test_multiplicative), 0); }
TEST(Interpreter_Operators, Relational)     { EXPECT_EQ(RUN_TEST(-i test_relational),     0); }
TEST(Interpreter_Operators, Shift)          { EXPECT_EQ(RUN_TEST(-i test_shift),          0); }
TEST(Interpreter_Operators, Bit)            { EXPECT_EQ(RUN_TEST(-i test_bit),            0); }
TEST(Interpreter_Operators, Logical)        { EXPECT_EQ(RUN_TEST(-i test_logical),        0); }
TEST(Interpreter_Operators, PlusMinus)      { EXPECT_EQ(RUN_TEST(-i test_plusminus),      0); }
TEST(Interpreter_Operators, Increment)      { EXPECT_EQ(RUN_TEST(-i test_increment),      0); }
TEST(Interpreter_Operators, Ternary)        { EXPECT_EQ(RUN_TEST(-i test_ternary),        0); }
TEST(Interpreter_Operators, Sizeof)         { EXPECT_EQ(RUN_TEST(-i test_sizeof),         0); }

TEST(Interpreter_Control, IfElse)  { EXPECT_EQ(RUN_TEST(-i test_ifelse),  0); }
TEST(Interpreter_Control, Switch)  { EXPECT_EQ(RUN_TEST(-i test_switch),  0); }
TEST(Interpreter_Control, Goto)    { EXPECT_EQ(RUN_TEST(-i test_goto),    0); }

TEST(Interpreter_Iteration, For)     { EXPECT_EQ(RUN_TEST(-i test_for),     0); }
TEST(Interpreter_Iteration, While)   { EXPECT_EQ(RUN_TEST(-i test_while),   0); }
TEST(Interpreter_Iteration, DoWhile) { EXPECT_EQ(RUN_TEST(-i test_dowhile), 0); }

TEST(Interpreter_Declarations, Import) {}
TEST(Interpreter_Declarations, Alias)  { EXPECT_EQ(RUN_TEST(-i test_alias), 0); }
TEST(Interpreter_Declarations, Enum)   { EXPECT_EQ(RUN_TEST(-i test_enum),  0); }
TEST(Interpreter_Declarations, Class)  { EXPECT_EQ(RUN_TEST(-i test_class), 0); }
TEST(Interpreter_Declarations, Ref)    { EXPECT_EQ(RUN_TEST(-i test_ref),   0); }
TEST(Interpreter_Declarations, Ptr)    { EXPECT_EQ(RUN_TEST(-i test_ptr),   0); }
TEST(Interpreter_Declarations, Array)  { EXPECT_EQ(RUN_TEST(-i test_array), 0); }
TEST(Interpreter_Declarations, Const)  { EXPECT_EQ(RUN_TEST(-i test_const), 0); }

TEST(Interpreter_Function, Calls)      { EXPECT_EQ(RUN_TEST(-i test_functioncalls), 0); }
TEST(Interpreter_Function, Overloading){ EXPECT_EQ(RUN_TEST(-i test_overloading),   0); }
TEST(Interpreter_Function, Returns)    { EXPECT_EQ(RUN_TEST(-i test_returns),       0); }

TEST(Interpreter_Misc, Strings)       { EXPECT_EQ(RUN_TEST(-i test_string),       0); }
TEST(Interpreter_Misc, ImplicitCasts) { EXPECT_EQ(RUN_TEST(-i test_implicitcasts),0); }
TEST(Interpreter_Misc, Literals)      { EXPECT_EQ(RUN_TEST(-i test_literals),     0); }
TEST(Interpreter_Misc, Floats)        { EXPECT_EQ(RUN_TEST(-i test_floats),       0); }

TEST(Interpreter_Classes, Inheritance)  { EXPECT_EQ(RUN_TEST(-i test_inheritance),  0); }
TEST(Interpreter_Classes, Polymorphism) { EXPECT_EQ(RUN_TEST(-i test_polymorphism), 0); }
TEST(Interpreter_Classes, Constructors) { EXPECT_EQ(RUN_TEST(-i test_constructors), 0); }
TEST(Interpreter_Classes, Templates)    { EXPECT_EQ(RUN_TEST(-i test_templates),    0); }
TEST(Interpreter_Classes, ReadmeExample){ EXPECT_EQ(RUN_TEST(-i test_readme_example), 0); }
