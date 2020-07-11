
#include <gtest/gtest.h>

#include <Hexagon/Elements/Window.hpp>

#include <allegro5/allegro.h>

class Hexagon_Elements_WindowTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_WindowTest_WithEmptyFixture() {}
};

class Hexagon_Elements_WindowTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_Elements_WindowTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      display = al_create_display(1280, 720);
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }
};

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Window window;
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture, draw__does_not_blow_up)
{
   Hexagon::Elements::Window window;
   window.draw();
   SUCCEED();
}
