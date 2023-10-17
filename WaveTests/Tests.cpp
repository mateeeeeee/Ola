#include "pch.h"
#include "TestMacros.h"

using namespace wave;

TEST(Arithmetic, AdditiveMultiplicativeOperators)
{
	EXPECT_EQ(WAVE_EX(return 0;), 0);
	EXPECT_EQ(WAVE_EX(return 42;), 42);
	EXPECT_EQ(WAVE_EX(return 5 + 20 - 4;), 21);
	EXPECT_EQ(WAVE_EX(return 12 + 34 - 5;), 41);
	EXPECT_EQ(WAVE_EX(return 5 + 6 * 7;), 47);
	EXPECT_EQ(WAVE_EX(return 5 * (9 - 6);), 15);
	EXPECT_EQ(WAVE_EX(return -10 + 20;), 10);
	EXPECT_EQ(WAVE_EX(return (3 + 5) / 2;), 4);
}