#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <library/header.h>

TEST(library_tests, check_sum_is_correct)
{
   EXPECT_EQ(library::sum(1.0, 2.0), 3.0);
}
