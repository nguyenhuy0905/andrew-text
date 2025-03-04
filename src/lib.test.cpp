#include <gtest/gtest.h>

#ifdef ADRTXT_MODULE
import lib;
#else
#include "lib.hpp"
#endif // ADRTXT_MODULE

TEST(Simply, TheTruth) {
  ASSERT_TRUE(lib::return_true()) << "return_true is not the truth"; 
}
