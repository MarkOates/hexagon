
#include <gtest/gtest.h>

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, initialize__without_allegro_initialized__raises_an_exception)
{
   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
   EXPECT_THROW_GUARD_ERROR(
      bitmap_grid_render_surface.initialize(),
      "Hexagon::Elements::BitmapGridRenderSurface::initialize",
      "al_is_system_installed()"
   );
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

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, draw_to_cell__will_render_the_bitmap_clipped_to_the_cell)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(16*40, 8*40);
   ALLEGRO_FONT *font = al_create_builtin_font();
   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map(font);
   sub_bitmap_character_map.initialize();

   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface(7, 9, 13, 29);
   bitmap_grid_render_surface.initialize();

   ALLEGRO_BITMAP *bitmap_to_draw = sub_bitmap_character_map.find_sub_bitmap('A');
   bitmap_grid_render_surface.draw_to_cell(bitmap_to_draw, ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f}, 0, 0);

   ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();

   al_draw_bitmap(surface, 0, 0, 0);
   al_flip_display();
   //sleep(3);

   al_destroy_display(display);
   al_uninstall_system();

   SUCCEED();
}

TEST(Hexagon_Elements_BitmapGridRenderSurfaceTest, fun)
{
   // setup
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(16*40, 8*40);
   ALLEGRO_FONT *font = al_create_builtin_font();


   // parameters

   //-> font
   int num_columns = 123;
   int num_rows = 74;


   // Setup dependencies

   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map(font);
   sub_bitmap_character_map.initialize();


   // Setup self

   Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface(
      num_columns,
      num_rows,
      sub_bitmap_character_map.get_grid_width(),
      sub_bitmap_character_map.get_grid_height()
   );
   bitmap_grid_render_surface.initialize();


   // Use

   bitmap_grid_render_surface.lock_for_render();
   for (unsigned y=0; y<num_rows; y++)
   {
      for (unsigned x=0; x<num_columns; x++)
      {
         ALLEGRO_BITMAP *bitmap_to_draw = sub_bitmap_character_map.find_sub_bitmap('A');
         bitmap_grid_render_surface.draw_to_cell(bitmap_to_draw, ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f}, x, y);
      }
   }
   bitmap_grid_render_surface.unlock_for_render();


   // For drawing

   ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();
   al_draw_bitmap(surface, 0, 0, 0);


   // Shutdown

   al_flip_display();
   //sleep(1);

   al_destroy_display(display);
   al_uninstall_system();

   SUCCEED();
}

