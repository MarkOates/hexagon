#pragma once


#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>
#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>
#include <allegro5/allegro_font.h>
#include <string>


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

      std::string run();
      void initialize();
      void set_cell_to_character_and_color();
      };
   }
}



