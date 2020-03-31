
#include <gtest/gtest.h>

#include <Hexgaon/Powerbar/Renderer.hpp>

TEST(Hexgaon_Powerbar_RendererTest, can_be_created_without_blowing_up)
{
   Hexgaon::Powerbar::Renderer renderer;
}

TEST(Hexgaon_Powerbar_RendererTest, run__returns_the_expected_response)
{
   Hexgaon::Powerbar::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}
