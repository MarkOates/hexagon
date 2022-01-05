
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>

#include <Blast/StringSplitter.hpp>

static std::string FIXTURE_PASSAGE = R"PASSAGE(       - 64 -
Act without doing;
work without effort.
Think of the small as large
and the few as many.
Confront the difficult
while it is still easy;
accomplish the great task
by a series of small acts.

The Master never reaches for the great;
thus she achieves greatness.
When she runs into a difficulty,
she stops and gives herself to it.
She doesn't cling to her own comfort;
thus problems are no problem for her.
)PASSAGE";

const std::string SONNET_TEXT = R"END(Sonnet 15

When I consider every thing that grows
Holds in perfection but a little moment.
That this huge stage presenteth nought but shows
Whereon the stars in secret influence comment.
When I perceive that men as plants increase,
Cheered and checked even by the self-same sky:
Vaunt in their youthful sap, at height decrease,
And wear their brave state out of memory.
Then the conceit of this inconstant stay,
Sets you most rich in youth before my sight,
Where wasteful time debateth with decay
To change your day of youth to sullied night,
And all in war with Time for love of you,
As he takes from you, I engraft you new.)END";


TEST(Hexagon_AdvancedCodeEditor_SearchRegexToSelectionsConverterTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter search_regex_to_selections_converter;
}

TEST(Hexagon_AdvancedCodeEditor_SearchRegexToSelectionsConverterTest,
   convert__will_create_the_expected_selections)
{
   std::string search_regex_string = "of";
   std::vector<std::string> lines = Blast::StringSplitter(SONNET_TEXT, '\n').split();
   Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter converter(search_regex_string, lines);

   std::vector<CodeRange> expected = {
      CodeRange{ 31, 9, 33, 9 },
      CodeRange{ 17, 10, 19, 10 },
      CodeRange{ 19, 13, 21, 13 },
      CodeRange{ 34, 14, 36, 14 }
   };
   std::vector<CodeRange> actual = converter.convert();
 
   EXPECT_EQ(expected, actual);
}

