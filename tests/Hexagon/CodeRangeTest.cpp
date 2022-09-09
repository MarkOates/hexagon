#include <gtest/gtest.h>


#include <Hexagon/CodeRange.hpp>


TEST(Hexagon_CodeRange, can_be_created_without_blowing_up)
{
   CodeRange code_range;
}


TEST(Hexagon_CodeRange, in_range__will_return_true_with_this_specific_test_data)
{
   CodeRange code_range(9, 118, 10, 120);
   EXPECT_EQ(true, code_range.in_range(0, 119)); // the position in question is inside the range lines
}



