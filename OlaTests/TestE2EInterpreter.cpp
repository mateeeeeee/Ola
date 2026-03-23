#include "gtest/gtest.h"
#include "Compiler/CompilerMacros.h"

#define OLA_E2E_TEST(suite, name, file) \
	TEST(Interpreter_##suite, name) { EXPECT_EQ(OLA_TEST_INTERPRET(-i file), 0); }
#include "TestE2ETests.inc"
#undef OLA_E2E_TEST

TEST(Interpreter_Declarations, Import) {}
