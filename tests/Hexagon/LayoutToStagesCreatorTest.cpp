
#include <gtest/gtest.h>

#include <Hexagon/LayoutToStagesCreator.hpp>

TEST(Hexagon_LayoutToStagesCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::LayoutToStagesCreator layout_to_stages_creator;
}

TEST(Hexagon_LayoutToStagesCreatorTest, run__returns_the_expected_response)
{
   Hexagon::LayoutToStagesCreator layout_to_stages_creator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, layout_to_stages_creator.run());
}
