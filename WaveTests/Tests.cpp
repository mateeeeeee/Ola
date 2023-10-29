#include "pch.h"
#include "TestMacros.h"
#include "Core/Defines.h"

using namespace wave;


TEST(Operators, Additive)
{
	EXPECT_EQ(WAVE(-i test_additive), 0);
}

TEST(Operators, Multiplicative)
{
	EXPECT_EQ(WAVE(-i test_multiplicative), 0);
}

TEST(Operators, Relational)
{
	EXPECT_EQ(WAVE(-i test_relational), 0);
}

TEST(Operators, Shift)
{
	EXPECT_EQ(WAVE(-i test_shift), 0);
}

TEST(Operators, Bit)
{
	EXPECT_EQ(WAVE(-i test_bit), 0);
}

TEST(Operators, Logical)
{
	EXPECT_EQ(WAVE(-i test_logical), 0);
}

TEST(Operators, PlusMinus)
{
	EXPECT_EQ(WAVE(-i test_plusminus), 0);
}

TEST(Operators, Increment)
{
	EXPECT_EQ(WAVE(-i test_increment), 0);
}

TEST(Operators, TernaryOperator)
{
	EXPECT_EQ(WAVE(-i test_ternary), 0);
}

TEST(Operators, Sizeof)
{
	EXPECT_EQ(WAVE(-i test_sizeof), 0);
}

TEST(Control, IfElse)
{
	EXPECT_EQ(WAVE(-i test_ifelse), 0);
}

TEST(Control, Switch)
{
	EXPECT_EQ(WAVE(-i test_switch), 0);
}

TEST(Control, Goto)
{
	EXPECT_EQ(WAVE(-i test_goto), 0);
}

TEST(Iteration, For)
{
	EXPECT_EQ(WAVE(-i test_for), 0);
}

TEST(Iteration, While)
{
	EXPECT_EQ(WAVE(-i test_while), 0);
}

TEST(Iteration, DoWhile)
{
	EXPECT_EQ(WAVE(-i test_dowhile), 0);
}

TEST(Declarations, Functions) 
{
	
}

TEST(Declarations, Variables)
{

}

TEST(Declarations, Import)
{

}

TEST(Function, Calls)
{
	EXPECT_EQ(WAVE(-i test_functioncalls), 0);
}

TEST(Misc, Const)
{
	EXPECT_EQ(WAVE(-i test_const), WAVE_COMPILATION_FAILED_EXIT_CODE);
}


TEST(Misc, Constexpr)
{

}

TEST(Misc, Enum)
{

}
