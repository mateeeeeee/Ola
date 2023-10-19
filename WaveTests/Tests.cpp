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
	EXPECT_EQ(WAVE_EX(let i = 2; i += 5; return i;), 7);
	EXPECT_EQ(WAVE_EX(let i = 5; i -= 7; return i;), -2);
	EXPECT_EQ(WAVE_EX(let i = 5; i *= 4; return i - 15;), 5);
	EXPECT_EQ(WAVE_EX(let i = 7; i /= 3; return i;), 2);
}

TEST(Arithmetic, RelationOperations)
{
	EXPECT_EQ(WAVE_EX(return 42 == 42;), 1);
	EXPECT_EQ(WAVE_EX(return 0 != 1;), 1);
	EXPECT_EQ(WAVE_EX(return 42 != 42;), 0);
	EXPECT_EQ(WAVE_EX(return 0 < 1;), 1);
	EXPECT_EQ(WAVE_EX(return 1 < 1;), 0);
	EXPECT_EQ(WAVE_EX(return 2 < 1;), 0);
	EXPECT_EQ(WAVE_EX(return 0 <= 1;), 1);
	EXPECT_EQ(WAVE_EX(return 1 <= 1;), 1);
	EXPECT_EQ(WAVE_EX(return 2 <= 1;), 0);
	EXPECT_EQ(WAVE_EX(return 1 > 0;), 1);
	EXPECT_EQ(WAVE_EX(return 1 > 1;), 0);
	EXPECT_EQ(WAVE_EX(return 1 > 2;), 0);
	EXPECT_EQ(WAVE_EX(return 1 >= 0;), 1);
	EXPECT_EQ(WAVE_EX(return 1 >= 1;), 1);
	EXPECT_EQ(WAVE_EX(return 1 >= 2;), 0);
}