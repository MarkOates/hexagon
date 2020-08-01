
#include <gtest/gtest.h>

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, initialize__without_allegro_initialized__raises_an_exception)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
   std::string expected_error_message =
      "BitmapGridRenderSurface::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(bitmap_grid_render_surface.initialize(), std::runtime_error, expected_error_message);
   SUCCEED();
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, initialize__does_not_blow_up)
{
   al_init();

   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
   bitmap_grid_render_surface.initialize();

   al_uninstall_system();

   SUCCEED();
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, initialize__will_create_a_surface_with_the_expected_dimensions)
{
   al_init();

   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface(7, 9, 13, 29);

   ASSERT_EQ(nullptr, bitmap_grid_render_surface.get_surface());

   bitmap_grid_render_surface.initialize();

   ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();
   ASSERT_NE(nullptr, surface);
   ASSERT_EQ(91, al_get_bitmap_width(surface));
   ASSERT_EQ(261, al_get_bitmap_height(surface));

   al_uninstall_system();

   SUCCEED();
}

