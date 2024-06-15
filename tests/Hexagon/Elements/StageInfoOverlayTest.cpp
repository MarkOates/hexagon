
#include <gtest/gtest.h>

#include <Hexagon/Elements/StageInfoOverlay.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro_color.h> // for al_color_name

TEST(Hexagon_Elements_StageInfoOverlayTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::StageInfoOverlay stage_info_overlay;
}

TEST(Hexagon_Elements_StageInfoOverlayTest, text__has_getters_and_setters)
{
   Hexagon::Elements::StageInfoOverlay stage_info_overlay;
   ASSERT_EQ("", stage_info_overlay.get_text());
}

TEST(Hexagon_Elements_StageInfoOverlayTest, render__without_a_valid_backfill_color__throws_an_error)
{
   Hexagon::Elements::StageInfoOverlay stage_info_overlay(nullptr, nullptr);
   ASSERT_THROW_GUARD_ERROR(
      stage_info_overlay.render(),
      "Hexagon::Elements::StageInfoOverlay::render",
      "backfill_color"
   );
}

TEST(Hexagon_Elements_StageInfoOverlayTest, render__without_a_valid_font_bin__throws_an_error)
{
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   placement3d place;
   Hexagon::Elements::StageInfoOverlay stage_info_overlay(nullptr, &backfill_color);
   stage_info_overlay.set_place(&place);

   ASSERT_THROW_GUARD_ERROR(
      stage_info_overlay.render(),
      "Hexagon::Elements::StageInfoOverlay::obtain_title_font", // !! NOTE: guard error reports from a different method
      "font_bin"
   );
}

TEST(Hexagon_Elements_StageInfoOverlayTest, render__with_valid_dependencies__does_not_blow_up)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   ALLEGRO_DISPLAY *display = al_create_display(400, 300);
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   float backfill_opacity = 0.8;
   placement3d place;
   place.size.x = 400;
   place.size.y = 300;

   Hexagon::Elements::StageInfoOverlay stage_info_overlay(&font_bin, &backfill_color, backfill_opacity, &place);
   stage_info_overlay.render();

   al_flip_display();
   sleep(1);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}
