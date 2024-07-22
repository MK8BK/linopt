#include <gtest/gtest.h>
#include "mathutils.h"

TEST(Factorial5, TrivialEquality){
  EXPECT_EQ(mathutils::fact(5), 120);
}

