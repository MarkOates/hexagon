
#include <gtest/gtest.h>

#include <Hexagon/TitleScreen.hpp>

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_TitleScreenTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_TitleScreenTestWithAllegroRenderingFixture, can_be_created_without_blowing_up)
{
   Hexagon::TitleScreen title_screen(&get_font_bin_ref());
   title_screen.draw_hexagon_logo_and_wait_for_keypress();
}

