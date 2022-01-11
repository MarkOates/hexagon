
#include <gtest/gtest.h>

#include <Hexagon/Daemus/Builds/Base.hpp>

TEST(Hexagon_Daemus_Builds_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::Builds::Base base;
}

TEST(Hexagon_Daemus_Builds_BaseTest, type__has_the_expeced_value)
{
   Hexagon::Daemus::Builds::Base base;
   EXPECT_EQ("Base", base.get_type());
}
