
#include <gtest/gtest.h>

#include <Hexagon/NewComponentMaker/NewComponentMaker.hpp>

TEST(Hexagon_NewComponentMaker_NewComponentMakerTest, can_be_created_without_blowing_up)
{
   Hexagon::NewComponentMaker::NewComponentMaker new_component_maker;
}

TEST(Hexagon_NewComponentMaker_NewComponentMakerTest, run__returns_the_expected_response)
{
   Hexagon::NewComponentMaker::NewComponentMaker new_component_maker;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, new_component_maker.run());
}
