
#include <gtest/gtest.h>

#include <Hexagon/Daemus/Builds/ExtrapolateQuintessence.hpp>

TEST(Hexagon_Daemus_Builds_ExtrapolateQuintessenceTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::Builds::ExtrapolateQuintessence extrapolate_quintessence;
}

TEST(Hexagon_Daemus_Builds_ExtrapolateQuintessenceTest, type__returns_the_expected_value)
{
   Hexagon::Daemus::Builds::ExtrapolateQuintessence extrapolate_quintessence;
   EXPECT_EQ("ExtrapolateQuintessence", extrapolate_quintessence.get_type());
}
