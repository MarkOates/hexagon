
#include <gtest/gtest.h>

#include <Hexagon/Elements/FontCharacterMapGrid.hpp>

TEST(Hexagon_Elements_FontCharacterMapGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
}

TEST(Hexagon_Elements_FontCharacterMapGridTest, create__returns_nullptr)
{
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
   EXPECT_EQ(nullptr, font_character_map_grid.create());
}
