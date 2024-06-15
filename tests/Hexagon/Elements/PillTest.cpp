
#include <gtest/gtest.h>

#include <Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

class Hexagon_Elements_PillTest : public ::testing::Test
{};

class Hexagon_Elements_PillTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/Elements/Pill.hpp>


TEST_F(Hexagon_Elements_PillTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Pill pill;
}


TEST_F(Hexagon_Elements_PillTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::Pill pill;
   ASSERT_THROW_GUARD_ERROR(
      pill.render(),
      "Hexagon::Elements::Pill::render",
      "al_is_system_installed()"
   );
}


TEST_F(Hexagon_Elements_PillTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::Pill pill(&get_font_bin_ref());
   pill.render();
   al_flip_display();
   sleep(2);
   SUCCEED();
}

