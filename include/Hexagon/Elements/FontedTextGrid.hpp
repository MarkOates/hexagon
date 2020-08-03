#pragma once


#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>
#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace Elements
   {
      class FontedTextGrid
      {
      private:
         ALLEGRO_FONT* font;
         int num_columns;
         int num_rows;
         Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map;
         Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface;
         bool initialized;

      public:
         FontedTextGrid(ALLEGRO_FONT* font=nullptr, int num_columns=123, int num_rows=74);
         ~FontedTextGrid();

         void set_font(ALLEGRO_FONT* font);

         int get_num_columns();
         int get_num_rows();
         bool get_initialized();
      void initialize();
      void destroy();
      void set_cell_to_character_and_color(char character=' ', int x=0, int y=0, ALLEGRO_COLOR tint=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
      void lock_for_update();
      void unlock_for_update();
      void draw();
      ALLEGRO_BITMAP* __cheat_really_badly_and_get_the_bitmap_grid_render_surface();
      };
   }
}



