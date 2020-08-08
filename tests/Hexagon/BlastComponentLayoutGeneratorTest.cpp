
#include <gtest/gtest.h>

#include <Hexagon/BlastComponentLayoutGenerator.hpp>

TEST(Hexagon_BlastComponentLayoutGeneratorTest, can_be_created_without_blowing_up)
{
   Hexagon::BlastComponentLayoutGenerator blast_component_layout_generator;
}

TEST(Hexagon_BlastComponentLayoutGeneratorTest, run__returns_the_expected_response)
{
   Hexagon::BlastComponentLayoutGenerator blast_component_layout_generator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, blast_component_layout_generator.run());
}
