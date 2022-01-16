
#include <gtest/gtest.h>

#include <Hexagon/Fancy/Stage.hpp>

TEST(Hexagon_Fancy_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::Fancy::Stage stage;
}

TEST(Hexagon_Fancy_StageTest, run__returns_the_expected_response)
{
   Hexagon::Fancy::Stage stage;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage.run());
}
