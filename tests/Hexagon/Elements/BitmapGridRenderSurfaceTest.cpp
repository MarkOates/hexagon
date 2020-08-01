
#include <gtest/gtest.h>

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, run__returns_the_expected_response)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, bitmap_grid_render_surface.run());
}
