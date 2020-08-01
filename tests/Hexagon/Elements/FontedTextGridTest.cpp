
#include <gtest/gtest.h>

#include <Hexagon/Elements/FontedTextGrid.hpp>

TEST(Hexagon_Elements_FontedTextGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FontedTextGrid fonted_text_grid;
}

TEST(Hexagon_Elements_FontedTextGridTest, run__returns_the_expected_response)
{
   Hexagon::Elements::FontedTextGrid fonted_text_grid;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, fonted_text_grid.run());
}
