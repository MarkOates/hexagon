
#include <gtest/gtest.h>

#include <Hexagon/Elements/StageInfoOverlay.hpp>

TEST(Hexagon_Elements_StageInfoOverlayTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::StageInfoOverlay stage_info_overlay;
}

TEST(Hexagon_Elements_StageInforOverlayTest, text__has_getters_and_setters)
{
   Hexagon::Elements::StageInfoOverlay stage_info_overlay;
   ASSERT_EQ("", stage_info_overlay.get_text());
}

TEST(Hexagon_Elements_StageInforOverlayTest, render__without_a_valid_title_font__throws_an_error)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_DISPLAY *display = al_create_display(400, 300);
   placement3d place;
   place.size.x = 400;
   place.size.y = 300;

   Hexagon::Elements::StageInfoOverlay stage_info_overlay(font, &place);
   stage_info_overlay.render();

   al_flip_display();
   //sleep(1);

  al_uninstall_system();
}
