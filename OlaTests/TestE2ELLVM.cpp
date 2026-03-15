#include "gtest/gtest.h"
#define LLVM_BACKEND 1
#include "Compiler/CompilerMacros.h"

#define RUN_TEST OLA_TEST

TEST(LLVM_Operators, Additive)       { EXPECT_EQ(RUN_TEST(-i test_additive),       0); }
TEST(LLVM_Operators, Multiplicative) { EXPECT_EQ(RUN_TEST(-i test_multiplicative), 0); }
TEST(LLVM_Operators, Relational)     { EXPECT_EQ(RUN_TEST(-i test_relational),     0); }
TEST(LLVM_Operators, Shift)          { EXPECT_EQ(RUN_TEST(-i test_shift),          0); }
TEST(LLVM_Operators, Bit)            { EXPECT_EQ(RUN_TEST(-i test_bit),            0); }
TEST(LLVM_Operators, Logical)        { EXPECT_EQ(RUN_TEST(-i test_logical),        0); }
TEST(LLVM_Operators, PlusMinus)      { EXPECT_EQ(RUN_TEST(-i test_plusminus),      0); }
TEST(LLVM_Operators, Increment)      { EXPECT_EQ(RUN_TEST(-i test_increment),      0); }
TEST(LLVM_Operators, Ternary)        { EXPECT_EQ(RUN_TEST(-i test_ternary),        0); }
TEST(LLVM_Operators, Sizeof)         { EXPECT_EQ(RUN_TEST(-i test_sizeof),         0); }
TEST(LLVM_Operators, Dereference)    { EXPECT_EQ(RUN_TEST(-i test_dereference),    0); }

TEST(LLVM_Control, IfElse)  { EXPECT_EQ(RUN_TEST(-i test_ifelse),  0); }
TEST(LLVM_Control, Switch)  { EXPECT_EQ(RUN_TEST(-i test_switch),  0); }
TEST(LLVM_Control, Goto)    { EXPECT_EQ(RUN_TEST(-i test_goto),    0); }

TEST(LLVM_Iteration, For)     { EXPECT_EQ(RUN_TEST(-i test_for),     0); }
TEST(LLVM_Iteration, While)   { EXPECT_EQ(RUN_TEST(-i test_while),   0); }
TEST(LLVM_Iteration, DoWhile) { EXPECT_EQ(RUN_TEST(-i test_dowhile), 0); }
TEST(LLVM_Iteration, Foreach) { EXPECT_EQ(RUN_TEST(-i test_foreach), 0); }

TEST(LLVM_Declarations, Import) {}
TEST(LLVM_Declarations, Alias)  { EXPECT_EQ(RUN_TEST(-i test_alias), 0); }
TEST(LLVM_Declarations, Enum)   { EXPECT_EQ(RUN_TEST(-i test_enum),  0); }
TEST(LLVM_Declarations, Class)  { EXPECT_EQ(RUN_TEST(-i test_class), 0); }
TEST(LLVM_Declarations, Ref)    { EXPECT_EQ(RUN_TEST(-i test_ref),   0); }
TEST(LLVM_Declarations, Ptr)    { EXPECT_EQ(RUN_TEST(-i test_ptr),   0); }
TEST(LLVM_Declarations, Array)  { EXPECT_EQ(RUN_TEST(-i test_array), 0); }
TEST(LLVM_Declarations, Const)  { EXPECT_EQ(RUN_TEST(-i test_const), 0); }
TEST(LLVM_Declarations, New)    { EXPECT_EQ(RUN_TEST(-i test_new),   0); }
TEST(LLVM_Declarations, Auto)	{ EXPECT_EQ(RUN_TEST(-i test_auto),  0); }

TEST(LLVM_Function, Calls)       { EXPECT_EQ(RUN_TEST(-i test_functioncalls), 0); }
TEST(LLVM_Function, Overloading) { EXPECT_EQ(RUN_TEST(-i test_overloading),   0); }
TEST(LLVM_Function, Returns)     { EXPECT_EQ(RUN_TEST(-i test_returns),       0); }
TEST(LLVM_Function, Recursion)	 { EXPECT_EQ(RUN_TEST(-i test_recursion), 	  0); }
TEST(LLVM_Function, Templates)   { EXPECT_EQ(RUN_TEST(-i test_function_templates), 0); }

TEST(LLVM_Misc, Strings)       { EXPECT_EQ(RUN_TEST(-i test_string),        0); }
TEST(LLVM_Misc, ImplicitCasts) { EXPECT_EQ(RUN_TEST(-i test_implicitcasts), 0); }
TEST(LLVM_Misc, Literals)      { EXPECT_EQ(RUN_TEST(-i test_literals),      0); }
TEST(LLVM_Misc, Floats)        { EXPECT_EQ(RUN_TEST(-i test_floats),        0); }
TEST(LLVM_Misc, Scope)		   { EXPECT_EQ(RUN_TEST(-i test_scope), 		0); }

TEST(LLVM_Classes, Inheritance)  { EXPECT_EQ(RUN_TEST(-i test_inheritance),  0); }
TEST(LLVM_Classes, Polymorphism) { EXPECT_EQ(RUN_TEST(-i test_polymorphism), 0); }
TEST(LLVM_Classes, Constructors) { EXPECT_EQ(RUN_TEST(-i test_constructors), 0); }
TEST(LLVM_Classes, Templates)    { EXPECT_EQ(RUN_TEST(-i test_templates),    0); }
TEST(LLVM_Classes, ReadmeExample){ EXPECT_EQ(RUN_TEST(-i test_readme_example), 0); }
TEST(LLVM_Classes, Static)		 { EXPECT_EQ(RUN_TEST(-i test_static), 0); }


TEST(LLVM_Containers, Vector)       { EXPECT_EQ(RUN_TEST(-i test_vector),        0); }
TEST(LLVM_Containers, Pair)         { EXPECT_EQ(RUN_TEST(-i test_pair),          0); }
TEST(LLVM_Containers, Optional)     { EXPECT_EQ(RUN_TEST(-i test_optional),      0); }
TEST(LLVM_Containers, List)         { EXPECT_EQ(RUN_TEST(-i test_list),          0); }
TEST(LLVM_Containers, Set)          { EXPECT_EQ(RUN_TEST(-i test_set),           0); }
TEST(LLVM_Containers, Stack)        { EXPECT_EQ(RUN_TEST(-i test_stack),         0); }
TEST(LLVM_Containers, Queue)        { EXPECT_EQ(RUN_TEST(-i test_queue),         0); }
TEST(LLVM_Containers, Map)          { EXPECT_EQ(RUN_TEST(-i test_map),           0); }
