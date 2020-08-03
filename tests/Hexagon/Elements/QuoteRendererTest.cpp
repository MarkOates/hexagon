
#include <gtest/gtest.h>

#include <Hexagon/Elements/QuoteRenderer.hpp>

TEST(Hexagon_Elements_QuoteRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}

TEST(Hexagon_Elements_QuoteRendererTest, run__returns_the_expected_response)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, quote_renderer.run());
}
