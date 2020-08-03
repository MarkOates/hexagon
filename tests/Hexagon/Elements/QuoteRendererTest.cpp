
#include <gtest/gtest.h>

#include <Hexagon/Elements/QuoteRenderer.hpp>

TEST(Hexagon_Elements_QuoteRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}

TEST(Hexagon_Elements_QuoteRendererTest, render__will_not_blow_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   quote_renderer.render();
   SUCCEED();
}
