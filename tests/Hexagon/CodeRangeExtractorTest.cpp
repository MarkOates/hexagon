
#include <gtest/gtest.h>

#include <Hexagon/CodeRangeExtractor.hpp>

#include <Blast/StringSplitter.hpp>

static const std::string sonnet = R"END(Is it thy will thy image should keep open
My heavy eyelids to the weary night?
Dost thou desire my slumbers should be broken,
While shadows like to thee do mock my sight?
Is it thy spirit that thou send'st from thee
So far from home into my deeds to pry,
To find out shames and idle hours in me,
The scope and tenor of thy jealousy?
O, no! thy love, though much, is not so great:
It is my love that keeps mine eye awake;
Mine own true love that doth my rest defeat,
To play the watchman ever for thy sake:
For thee watch I whilst thou dost wake elsewhere,
From me far off, with others all too near.

- William Shakespere)END";

TEST(Hexagon_CodeRangeExtractorTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeRangeExtractor code_range_extractor;
}

TEST(Hexagon_CodeRangeExtractorTest,
   DISABLED__extract__given_a_range_that_is_within_the_bounds_of_a_line__extracts_the_expected_string)
{
   CodeRange code_range{ 6, 0, 14, 0 };
   std::vector<std::string> lines = Blast::StringSplitter(sonnet, '\n').split();

   Hexagon::CodeRangeExtractor code_range_extractor(&lines, &code_range);

   std::vector<std::string> expected_extracted_string = {"thy will"};
   std::vector<std::string> actual_extracted_string = code_range_extractor.extract();

   EXPECT_EQ(expected_extracted_string, actual_extracted_string);
}

