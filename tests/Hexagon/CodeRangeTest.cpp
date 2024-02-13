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


TEST(Hexagon_CodeRange, infer_line_numbers__returns_the_line_numbers_that_are_in_the_selection)
{
   CodeRange code_range(9, 118, 10, 120);
   std::set<int> expected_line_numbers = { 118, 119, 120 };
   std::set<int> actual_line_numbers = code_range.infer_line_numbers();
   EXPECT_EQ(expected_line_numbers, actual_line_numbers);
}



