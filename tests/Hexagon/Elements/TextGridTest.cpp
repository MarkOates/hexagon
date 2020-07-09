
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextGrid.hpp>

TEST(Hexagon_Elements_TextGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextGrid text_grid;
}

TEST(Hexagon_Elements_TextGridTest, run__returns_the_expected_response)
{
   Hexagon::Elements::TextGrid text_grid;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, text_grid.run());
}
