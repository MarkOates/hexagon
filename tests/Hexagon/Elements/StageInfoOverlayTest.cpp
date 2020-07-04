
#include <gtest/gtest.h>

#include <Hexagon/Elements/StageInfoOverlay.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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
   std::string expected_error_message = "StageInfoOverlay::render: error: guard \"backfill_color\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_info_overlay.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_StageInfoOverlayTest, render__without_a_valid_title_font__throws_an_error)
{
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   Hexagon::Elements::StageInfoOverlay stage_info_overlay(nullptr, &backfill_color);
   std::string expected_error_message = "StageInfoOverlay::render: error: guard \"title_font\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_info_overlay.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_StageInfoOverlayTest, render__with_valid_dependencies__does_not_blow_up)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_DISPLAY *display = al_create_display(400, 300);
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   float backfill_opacity = 0.8;
   placement3d place;
   place.size.x = 400;
   place.size.y = 300;

   Hexagon::Elements::StageInfoOverlay stage_info_overlay(font, &backfill_color, backfill_opacity, &place);
   stage_info_overlay.render();

   al_flip_display();
   //sleep(1);

  al_uninstall_system();
}
