#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>
#include <tuple>


namespace Hexagon
{
   namespace Elements
   {
      class FontCharacterMapGrid
      {
      private:
         ALLEGRO_FONT* font;
         int grid_width;
         int grid_height;
         std::map<char, std::tuple<float, float, float, float>> character_uv_mapping;
         ALLEGRO_BITMAP* created_character_map_bitmap;
         bool initialized;

      public:
         FontCharacterMapGrid(ALLEGRO_FONT* font=nullptr);
         ~FontCharacterMapGrid();

         void set_font(ALLEGRO_FONT* font);
         int get_grid_width();
         int get_grid_height();
         std::map<char, std::tuple<float, float, float, float>> get_character_uv_mapping();
         bool get_initialized();
         ALLEGRO_BITMAP* get_created_character_map_bitmap();
         bool initialize();
      };
   }
}



