#include "cli.h"
#include "logs.h"
#include <gtest/gtest.h>

TEST(Placeholder, Test) { ASSERT_EQ(1, 0 + 2 - 1); }

TEST(DebugLog, Test) { debug_log(INFO, "hello, %s and %s\n", "myself", "i"); }
