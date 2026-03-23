#include "gtest/gtest.h"
#include "Compiler/CompilerMacros.h"

#define OLA_E2E_TEST(suite, name, file) \
	TEST(suite, name) { EXPECT_EQ(OLA_TEST(-i file), 0); }
#include "TestE2ETests.inc"
#undef OLA_E2E_TEST

TEST(Declarations, Import) {}
