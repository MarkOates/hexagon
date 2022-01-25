
#include <gtest/gtest.h>

#include <Hexagon/WordRangesFinder.hpp>

TEST(Hexagon_WordRangesFinderTest, can_be_created_without_blowing_up)
{
   Hexagon::WordRangesFinder word_ranges_finder;
}

TEST(Hexagon_WordRangesFinderTest, run__returns_the_expected_response)
{
   Hexagon::WordRangesFinder word_ranges_finder;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, word_ranges_finder.run());
}
