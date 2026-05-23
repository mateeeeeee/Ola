// Cross-target X86 E2E tests.

#include "gtest/gtest.h"
#include "Compiler/CompilerMacros.h"

#define OLA_E2E_TEST(suite, name, file) \
	TEST(X86_##suite, name) { EXPECT_EQ(OLA_TEST_X86(-i file), 0); }
#include "TestE2ETests.inc"
#undef OLA_E2E_TEST

TEST(X86_Declarations, Import) {}
