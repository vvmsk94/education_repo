#include "allocator.h"
#include <gtest/gtest.h>

TEST(Hello, foo) { ASSERT_STREQ("Hello", "Hello"); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}