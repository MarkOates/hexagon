
#include <gtest/gtest.h>

#include <Hexagon/CodeRenderer.hpp>

TEST(Hexagon_CodeRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeRenderer code_renderer;
}

TEST(Hexagon_CodeRendererTest, run__returns_the_expected_response)
{
   Hexagon::CodeRenderer code_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, code_renderer.run());
}
