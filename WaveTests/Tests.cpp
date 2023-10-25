#include "pch.h"
#include "TestMacros.h"

using namespace wave;

TEST(BinaryOperators, Additive)
{
	EXPECT_EQ(WAVE_DEBUG(-i test_additive.wv), 0);
}

TEST(BinaryOperators, Multiplicative)
{
	EXPECT_EQ(WAVE_DEBUG(-i test_multiplicative.wv), 0);
}

TEST(BinaryOperators, Relation)
{

}

TEST(BinaryOperators, Shift)
{

}

TEST(BinaryOperators, Bit)
{

}

TEST(UnaryOperators, PreIncrementDecrement)
{

}


TEST(UnaryOperators, PostIncrementDecrement)
{

}

TEST(Control, IfElse)
{

}

TEST(Control, Switch)
{
}

TEST(Control, Goto)
{

}

TEST(Control, TernaryOperator)
{
	
}

TEST(Iteration, For)
{
	
}
TEST(Iteration, While)
{
	
}
TEST(Iteration, DoWhile)
{
	
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

TEST(Functions, Calling)
{

}

TEST(Functions, Return)
{

}

TEST(Linkage, PublicPrivate)
{

}

TEST(Linkage, Extern)
{

}


TEST(Misc, Sizeof)
{

}

TEST(Misc, Const)
{

}

TEST(Misc, Constexpr)
{

}

TEST(Misc, Enum)
{

}
