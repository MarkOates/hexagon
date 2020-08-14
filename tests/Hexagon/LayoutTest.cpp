
#include <gtest/gtest.h>

#include <Hexagon/Layout.hpp>

TEST(Hexagon_LayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::Layout layout;
}

TEST(Hexagon_LayoutTest, concept_name__has_a_getter_with_the_expected_defaults)
{
   Hexagon::Layout layout;
   ASSERT_EQ("", layout.get_concept_name());
}

