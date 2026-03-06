#include "gtest/gtest.h"
#define LLVM_BACKEND 0
#define USE_INTERPRETER 0
#include "Compiler/CompilerMacros.h"

#define RUN_TEST OLA_TEST

TEST(Operators, Additive)       { EXPECT_EQ(RUN_TEST(-i test_additive),       0); }
TEST(Operators, Multiplicative) { EXPECT_EQ(RUN_TEST(-i test_multiplicative), 0); }
TEST(Operators, Relational)     { EXPECT_EQ(RUN_TEST(-i test_relational),     0); }
TEST(Operators, Shift)          { EXPECT_EQ(RUN_TEST(-i test_shift),          0); }
TEST(Operators, Bit)            { EXPECT_EQ(RUN_TEST(-i test_bit),            0); }
TEST(Operators, Logical)        { EXPECT_EQ(RUN_TEST(-i test_logical),        0); }
TEST(Operators, PlusMinus)      { EXPECT_EQ(RUN_TEST(-i test_plusminus),      0); }
TEST(Operators, Increment)      { EXPECT_EQ(RUN_TEST(-i test_increment),      0); }
TEST(Operators, Ternary)        { EXPECT_EQ(RUN_TEST(-i test_ternary),        0); }
TEST(Operators, Sizeof)         { EXPECT_EQ(RUN_TEST(-i test_sizeof),         0); }

TEST(Control, IfElse)  { EXPECT_EQ(RUN_TEST(-i test_ifelse),  0); }
TEST(Control, Switch)  { EXPECT_EQ(RUN_TEST(-i test_switch),  0); }
TEST(Control, Goto)    { EXPECT_EQ(RUN_TEST(-i test_goto),    0); }

TEST(Iteration, For)     { EXPECT_EQ(RUN_TEST(-i test_for),     0); }
TEST(Iteration, While)   { EXPECT_EQ(RUN_TEST(-i test_while),   0); }
TEST(Iteration, DoWhile) { EXPECT_EQ(RUN_TEST(-i test_dowhile), 0); }

TEST(Declarations, Import) {}
TEST(Declarations, Alias)  { EXPECT_EQ(RUN_TEST(-i test_alias), 0); }
TEST(Declarations, Enum)   { EXPECT_EQ(RUN_TEST(-i test_enum),  0); }
TEST(Declarations, Class)  { EXPECT_EQ(RUN_TEST(-i test_class), 0); }
TEST(Declarations, Ref)    { EXPECT_EQ(RUN_TEST(-i test_ref),   0); }
TEST(Declarations, Ptr)    { EXPECT_EQ(RUN_TEST(-i test_ptr),   0); }
TEST(Declarations, Array)  { EXPECT_EQ(RUN_TEST(-i test_array), 0); }
TEST(Declarations, Const)  { EXPECT_EQ(RUN_TEST(-i test_const), 0); }

TEST(Function, Calls)      { EXPECT_EQ(RUN_TEST(-i test_functioncalls), 0); }
TEST(Function, Overloading){ EXPECT_EQ(RUN_TEST(-i test_overloading),   0); }
TEST(Function, Returns)    { EXPECT_EQ(RUN_TEST(-i test_returns),       0); }

TEST(Misc, Strings)       { EXPECT_EQ(RUN_TEST(-i test_string),       0); }
TEST(Misc, ImplicitCasts) { EXPECT_EQ(RUN_TEST(-i test_implicitcasts),0); }
TEST(Misc, Literals)      { EXPECT_EQ(RUN_TEST(-i test_literals),     0); }
TEST(Misc, Floats)        { EXPECT_EQ(RUN_TEST(-i test_floats),       0); }

TEST(Classes, Inheritance)  { EXPECT_EQ(RUN_TEST(-i test_inheritance),  0); }
TEST(Classes, Polymorphism) { EXPECT_EQ(RUN_TEST(-i test_polymorphism), 0); }
TEST(Classes, Constructors) { EXPECT_EQ(RUN_TEST(-i test_constructors), 0); }
TEST(Classes, Templates)    { EXPECT_EQ(RUN_TEST(-i test_templates),    0); }
TEST(Classes, ReadmeExample){ EXPECT_EQ(RUN_TEST(-i test_readme_example), 0); }

TEST(Operators, Dereference)   { EXPECT_EQ(RUN_TEST(-i test_dereference),   0); }
TEST(Declarations, New)        { EXPECT_EQ(RUN_TEST(-i test_new),           0); }

TEST(Containers, Vector)       { EXPECT_EQ(RUN_TEST(-i test_vector),        0); }
TEST(Containers, Pair)         { EXPECT_EQ(RUN_TEST(-i test_pair),          0); }
TEST(Containers, Optional)     { EXPECT_EQ(RUN_TEST(-i test_optional),      0); }
TEST(Containers, List)         { EXPECT_EQ(RUN_TEST(-i test_list),          0); }
TEST(Containers, Set)          { EXPECT_EQ(RUN_TEST(-i test_set),           0); }
