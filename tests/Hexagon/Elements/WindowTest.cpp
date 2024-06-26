
#include <gtest/gtest.h>

#include <Hexagon/Elements/Window.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

//#define ASSERT_GREEN(display, x, y) \
//   ASSERT_EQ(1.0f, al_get_pixel(al_get_backbuffer(display), x, y).g)

class Hexagon_Elements_WindowTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_WindowTest_WithEmptyFixture() {}
};

class Hexagon_Elements_WindowTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   ALLEGRO_FONT* font;

public:
   Hexagon_Elements_WindowTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      font = al_create_builtin_font();
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      if (font) al_destroy_font(font);
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }

   void draw_current_test_name()
   {
      std::string current_test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
      ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
      al_draw_text(
         font,
         color,
         al_get_display_width(display)/2,
         al_get_display_height(display)/4,
         ALLEGRO_ALIGN_CENTER,
         current_test_name.c_str()
      );
   }
};

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Window window;
}

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, draw__without_allegro_initialized__throws_an_error)
{
   Hexagon::Elements::Window window;
   EXPECT_THROW_GUARD_ERROR(
      window.draw(),
      "Hexagon::Elements::Window::draw",
      "al_is_system_installed()"
   );
}

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, draw__without_primitives_addon_initialized__throws_an_error)
{
   al_init();
   Hexagon::Elements::Window window;
   EXPECT_THROW_GUARD_ERROR(
      window.draw(),
      "Hexagon::Elements::Window::draw",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}

TEST_F(Hexagon_Elements_WindowTest_WithEmptyFixture, draw__without_a_render_target__throws_an_error)
{
   al_init();
   al_init_primitives_addon();
   Hexagon::Elements::Window window;
   EXPECT_THROW_GUARD_ERROR(
      window.draw(),
      "Hexagon::Elements::Window::draw",
      "al_get_target_bitmap()"
   );
   al_uninstall_system();
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture, draw__does_not_blow_up)
{
   Hexagon::Elements::Window window;
   window.draw();
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__width__height__box_opacity__fill_color)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_box_fill_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_box_opacity(0.2);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);

   //ASSERT_GREEN(display, al_get_display_width(display)/2, al_get_display_height(display)/2);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__cell_padding)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(4.0);
   window.set_cell_padding(60.0f);

   window.set_box_fill_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_box_opacity(0.2);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__outer_line__color__thickness__opacity)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(20.0);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__corner_squares__color__width__height__opacity)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_corner_squares_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_corner_squares_opacity(0.2);
   window.set_corner_squares_width(100.0f);
   window.set_corner_squares_height(20.0f);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__corner_squares__resize_from_center)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_corner_squares_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_corner_squares_opacity(0.2);
   window.set_corner_squares_width(30.0f);
   window.set_corner_squares_height(60.0f);
   window.set_corner_squares_resize_from_center(true);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__header_bar__color__height__opacty)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_header_bar_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_header_bar_height(80.0f);
   window.set_header_bar_opacity(0.2f);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__corner_squares_are_circles)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_corner_squares_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_corner_squares_opacity(0.2);
   window.set_corner_squares_width(30.0f);
   window.set_corner_squares_height(60.0f);
   window.set_corner_squares_are_circles(true);
   //window.set_corner_squares_resize_from_center(true);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__header_baseline__color__thickness__opacity)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_header_baseline_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_header_baseline_opacity(0.2);
   window.set_header_baseline_thickness(20.0);

   window.set_header_bar_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_header_bar_height(80.0f);
   window.set_header_bar_opacity(0.2f);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__bottom_line__color__thickness__opacity)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(30.0);

   window.set_bottom_line_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_bottom_line_opacity(0.2);
   window.set_bottom_line_thickness(20.0);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_WindowTest_WithAllegroRenderingFixture,
   draw__respects__top_left_little_bar__color__width)
{
   float window_width = 1000.0f;
   float window_height = 520.0f;
   placement3d place = centered_placement(window_width, window_height);
   Hexagon::Elements::Window window(window_width, window_height);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_opacity(0.2);
   window.set_outer_line_thickness(1.0);

   window.set_header_bar_height(80.0f);

   window.set_top_left_little_bar_color(ALLEGRO_COLOR{0.0f, 1.0f, 0.0f, 1.0f});
   window.set_top_left_little_bar_width(20.0f);

   place.start_transform();
   window.draw();
   place.restore_transform();

   draw_current_test_name();

   al_flip_display();

   //sleep(1);
}

