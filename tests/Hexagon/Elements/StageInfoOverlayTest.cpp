
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
   Hexagon::Elements::StageInfoOverlay stage_info_overlay;
   //ASSERT_EQ("", stage_info_overlay.render());
}
