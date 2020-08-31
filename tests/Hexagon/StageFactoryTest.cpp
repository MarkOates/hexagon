
#include <gtest/gtest.h>

#include <Hexagon/StageFactory.hpp>

TEST(Hexagon_StageFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::StageFactory stage_factory;
}

TEST(Hexagon_StageFactoryTest, run__returns_the_expected_response)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage_factory.run());
}
