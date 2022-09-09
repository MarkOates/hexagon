
#include <gtest/gtest.h>

#include <Hexagon/Testing/Comparison/Hexagon/CodeRange.hpp>


TEST(Hexagon_Testing_Comparison_Hexagon_CodeRangeTest,
   PrintTo__with_an_AllegroFlare_CodeRange__will_output_as_expected)
{
   std::stringstream ss;
   CodeRange vec(0, 1, 2, 3);

   PrintTo(vec, &ss);

   std::string expected_output = "CodeRange(start: {0, 1}, end: {2, 3})";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(Hexagon_Testing_Comparison_Hexagon_CodeRangeTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   CodeRange object(0, 1, 2, 3);
   CodeRange other_object(0, 1, 2, 3);

   EXPECT_EQ(object, other_object);
}


