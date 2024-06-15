
#include <gtest/gtest.h>

#include <Hexagon/Elements/QuoteRenderer.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Blast/TaoTeChingQuoteGenerator.hpp>

class Hexagon_Elements_QuoteRendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   EXPECT_THROW_GUARD_ERROR(
      quote_renderer.render(),
      "Hexagon::Elements::QuoteRenderer::render",
      "al_is_system_installed()"
   );
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer(&get_font_bin_ref(), "To all, be well.");
   placement3d place = build_centered_placement(800, 600);

   place.start_transform();
   quote_renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__renders_nicely_with_longer_text)
{
   Blast::TaoTeChingQuoteGenerator quote_generator;
   Hexagon::Elements::QuoteRenderer quote_renderer(&get_font_bin_ref(), quote_generator.pick_quote());
   placement3d place = build_centered_placement(800, 600);

   place.start_transform();
   quote_renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(5);
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__renders_the_speaker_line)
{
   Blast::TaoTeChingQuoteGenerator quote_generator;
   Hexagon::Elements::QuoteRenderer quote_renderer(&get_font_bin_ref(), quote_generator.pick_quote(), "Tao Te Ching");
   placement3d place = build_centered_placement(800, 600);

   place.start_transform();
   quote_renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(5);
}

