
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/Window.hpp>

#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>

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
      display = al_create_display(1280*2, 720*2);
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Window window;
}

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, draw__without_allegro_initialized__throws_an_error)
{
   Hexagon::Elements::Window window;
   std::string expected_error_message = "Window::draw: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(window.draw(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture, draw__does_not_blow_up)
{
   Hexagon::Elements::Window window;
   window.draw();
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__width__height__box_opacity__cell_padding__fill_color)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height, 0.2, 8.0, ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});

   place.start_transform();
   window.draw();
   place.restore_transform();

   al_flip_display();

   sleep(1);
}
