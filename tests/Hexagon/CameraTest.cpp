
#include <gtest/gtest.h>

#include <Hexagon/Camera.hpp>

#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/FontBin.hpp>
#include <string>
#include <AllegroFlare/Vec2D.hpp>


void _draw_grid(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float thickness = 1.0f;

   for (unsigned cursor_y=0; cursor_y<=height; cursor_y+=spacing)
   {
      // horizontal lines
      al_draw_line(x, cursor_y, x + width, cursor_y, line_color, thickness);
   }

   for (unsigned cursor_x=0; cursor_x<=width; cursor_x+=spacing)
   {
      // vertical lines
      al_draw_line(cursor_x, y, cursor_x, y + height, line_color, thickness);
   }
}


void _draw_grid(float width, float height, float spacing)
{
   _draw_grid(0, 0, width, height, spacing);
}


void _draw_crosshair(float x, float y, ALLEGRO_COLOR color, float size, float thickness)
{
   float half_size = size * 0.5;
   al_draw_line(x, y-half_size, x, y+half_size, color, thickness);
   al_draw_line(x-half_size, y, x+half_size, y, color, thickness);
}


void _draw_crosshair_grid(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float size = 20.0f;
   float thickness = 1.0f;

   for (unsigned cursor_y=0; cursor_y<=height; cursor_y+=spacing)
   {
      for (unsigned cursor_x=0; cursor_x<=width; cursor_x+=spacing)
      {
         // horizontal lines
         _draw_crosshair(x + cursor_x, y + cursor_y, color, size, thickness);
      }
   }
}


void _draw_dot_grid(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};

   for (unsigned cursor_y=0; cursor_y<=height; cursor_y+=spacing)
   {
      for (unsigned cursor_x=0; cursor_x<=width; cursor_x+=spacing)
      {
         // horizontal lines
         al_draw_pixel(x + cursor_x, y + cursor_y, color);
      }
   }
}


void _draw_rect_dot_grid(float x, float y, float width, float height, float spacing, float box_size)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float hbox_size = box_size * 0.5;

   for (unsigned cursor_y=0; cursor_y<=height; cursor_y+=spacing)
   {
      for (unsigned cursor_x=0; cursor_x<=width; cursor_x+=spacing)
      {
         // horizontal lines
         al_draw_filled_rectangle(
            x + cursor_x - hbox_size,
            y + cursor_y - hbox_size,
            x + cursor_x + hbox_size,
            y + cursor_y + hbox_size,
            color
         );
         //al_draw_pixel(x + cursor_x, y + cursor_y, color);
      }
   }
}


void _draw_vertical_ruler(float x, float y, float length, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float cross_line_length = 10.0f;
   float hcross_line_length = cross_line_length * 0.5;
   float thickness = 1.0f;

   al_draw_line(x, y, x, y + length, color, thickness);
   for (unsigned cursor_y=0; cursor_y<=length; cursor_y+=spacing)
   {
      al_draw_line(-hcross_line_length, cursor_y, hcross_line_length, cursor_y, color, thickness);
   }
}


void _draw_horizontal_ruler(float x, float y, float length, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float cross_line_length = 10.0f;
   float hcross_line_length = cross_line_length * 0.5;
   float thickness = 1.0f;

   al_draw_line(x, y, x + length, y, color, thickness);
   for (unsigned cursor_x=0; cursor_x<=length; cursor_x+=spacing)
   {
      al_draw_line(cursor_x, -hcross_line_length, cursor_x, hcross_line_length, color, thickness);
   }
}


void _draw_numbered_vertical_ruler(ALLEGRO_FONT *font, float x, float y, float length, float spacing)
{
   if (!font) throw std::runtime_error("_draw_numbered_vertical_ruler font cannot be nullptr");

   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float cross_line_length = 10.0f;
   float hcross_line_length = cross_line_length * 0.5;
   float thickness = 1.0f;
   int flags = ALLEGRO_ALIGN_RIGHT;
   float h_line_height = al_get_font_line_height(font) * 0.5;

   //al_draw_line(x, y, x, y + length, color, thickness);
   int start_num = 0;
   int num = start_num;
   for (unsigned cursor_y=0; cursor_y<=length; cursor_y+=spacing)
   {
      al_draw_text(font, color, x, y + cursor_y - h_line_height, flags, std::to_string(num).c_str());
      num++;
      //al_draw_line(-hcross_line_length, cursor_y, hcross_line_length, cursor_y, color, thickness);
   }
}


void _draw_numbered_horizontal_ruler(ALLEGRO_FONT *font, float x, float y, float length, float spacing)
{
   if (!font) throw std::runtime_error("_draw_numbered_vertical_ruler font cannot be nullptr");

   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float cross_line_length = 10.0f;
   float hcross_line_length = cross_line_length * 0.5;
   float thickness = 1.0f;
   int flags = ALLEGRO_ALIGN_CENTER;
   float line_height = al_get_font_line_height(font);

   int start_num = 0;
   int num = start_num;
   for (unsigned cursor_x=0; cursor_x<=length; cursor_x+=spacing)
   {
      al_draw_text(font, color, x + cursor_x, y - line_height, flags, std::to_string(num).c_str());
      num++;
      //al_draw_line(cursor_x, -hcross_line_length, cursor_x, hcross_line_length, color, thickness);
   }
}


void _draw_vertical_pin_lines(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float thickness = 1.0f;
   //float x = 0;
   //float y = 0;
   //float width = 400;
   //float height = 300;
   //float spacing = 10;

   for (unsigned i=0; i<=width; i+=spacing)
   {
      al_draw_line(x+i, y, x+i, y+height, color, thickness);
   }
}


void _draw_horizontal_pin_lines(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float thickness = 1.0f;
   //float x = 0;
   //float y = 0;
   //float width = 400;
   //float height = 300;
   //float spacing = 10;

   for (unsigned i=0; i<=height; i+=spacing)
   {
      al_draw_line(x, y+i, x+width, y+i, color, thickness);
   }
}


void _draw_diagonal_pin_lines_in_box(float x, float y, float size, float spacing)
{
   // This approach is failing.  Need time to step away from the problem.

   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float thickness = 1.0f;
   float width = size;
   float height = size;

   al_draw_rectangle(x, y, width, height, color, thickness * 2.0);

   float aspect = height / width;
   float inv_aspect = 1.0 / (aspect);

   al_draw_line(spacing*0, spacing*0, width * aspect -spacing*0, height * aspect -spacing*0, color, thickness);

   //int step = 0;
   //for (unsigned i=0; i<step; i+=step)
   //{
      //al_draw_line(spacing*0, 0, width, height-spacing*0, color, thickness);
      al_draw_line(spacing*1, 0, width, height-spacing*1, color, thickness);
      al_draw_line(spacing*2, 0, width, height-spacing*2, color, thickness);
   //}

   {
      //al_draw_line(0, spacing*0, width-spacing*0, height, color, thickness);
      al_draw_line(0, spacing*1, width-spacing*1, height, color, thickness);
      al_draw_line(0, spacing*2, width-spacing*2, height, color, thickness);
   }
}


void _draw_diagonal_pin_lines(float x, float y, float width, float height, float spacing)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   float thickness = 1.0f;
   //float x = 0;
   //float y = 0;
   //float width = 400;
   //float height = 300;
   //float spacing = 10;
   float slope = 1.0f;
   float length = 100.0f;

   // horizontal set (lines drawn along the left)
   int num_horizontal_passes = height / spacing;
   for (unsigned i=0; i<=num_horizontal_passes; i++)
   {
      float offset = i * spacing;
      AllegroFlare::vec2d vec = AllegroFlare::vec2d(1, slope).normalized();
      al_draw_line(x, y+offset, x+width, y+offset+width*slope, color, thickness);
      //al_draw_line(x, y+offset, x+width*vec.x, y+offset+width*vec.y, color, thickness);
   }

   // vertial set (lines drawn along the top)
   int num_vertical_passes = width / spacing;
   for (unsigned i=1; i<=num_vertical_passes; i++)
   {
      float offset = i * spacing;
      AllegroFlare::vec2d vec = AllegroFlare::vec2d(1, slope).normalized();
      al_draw_line(x+offset, y, x+offset+height*slope, y+height, color, thickness);
      //al_draw_line(x+offset, y, x+offset+height*vec.x, y+height*vec.y, color, thickness);
   }
}


class Hexagon_CameraTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_CameraTest_WithEmptyFixture() {}
};


class Hexagon_CameraTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_CameraTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      //ASSERT_EQ(true, al_init_primitives_addon());
      ASSERT_EQ(true, al_init_font_addon());
      ASSERT_EQ(true, al_init_ttf_addon());
      //display = al_create_display(1280*2, 720*2);
      //display = al_create_display(1920 / 2 * 4, 1080 / 2 * 4);
      display = al_create_display(1920 * 2, 1080 * 2);
      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts/");

      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      //al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                                 // see https://www.allegro.cc/forums/thread/618183
      al_destroy_display(display);
      al_uninstall_system();
   }

   ALLEGRO_FONT *obtain_font()
   {
      return font_bin.auto_get("Purista Medium.otf -20");
   }

   //placement3d build_centered_placement(float width, float height)
   //{
   //   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
   //   place.size = vec3d(width, height, 0);
   //   return place;
   //}
};


TEST_F(Hexagon_CameraTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Camera camera;
}


TEST_F(Hexagon_CameraTest_WithAllegroRenderingFixture, setup_camera_perspective__can_be_created_without_blowing_up)
{
   ALLEGRO_BITMAP *bitmap = al_get_backbuffer(display);
   Hexagon::Camera camera;
   camera.setup_camera_perspective(bitmap);

   //_draw_grid(500, 500, 50);
   //_draw_grid(500, 500, 500);
   //_draw_grid(500, 500, 250);
   //_draw_crosshair(0, 0, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 30.0, 2.0);

   //_draw_crosshair_grid(-500, -500, 1000, 1000, 100);

   _draw_vertical_ruler(0, 0, 500, 10);
   _draw_numbered_vertical_ruler(obtain_font(), -20, 0, 500, 100);
   _draw_horizontal_ruler(0, 0, 500, 10);
   _draw_numbered_horizontal_ruler(obtain_font(), 0, -20, 500, 100);

   //_draw_horizontal_pin_lines(0, 0, 400, 300, 10);
   //_draw_vertical_pin_lines(0, 0, 400, 300, 10);
   //_draw_diagonal_pin_lines(0, 0, 400, 300, 10);
   _draw_diagonal_pin_lines_in_box(0, 0, 400, 10);

   al_flip_display();

   sleep(2);
}


