
#include <gtest/gtest.h>

#include <Hexagon/Elements/QuoteRenderer.hpp>

class Hexagon_Elements_QuoteRendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   quote_renderer.render();
   SUCCEED();
}
