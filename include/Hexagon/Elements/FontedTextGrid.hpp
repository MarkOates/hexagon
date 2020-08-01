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

         bool get_initialized();
      void initialize();
      void set_cell_to_character_and_color(char character=' ', int x=0, int y=0, ALLEGRO_COLOR tint=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
      void draw();
      };
   }
}



