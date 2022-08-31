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

      protected:


      public:
         FontCharacterMapGrid(ALLEGRO_FONT* font=nullptr);
         ~FontCharacterMapGrid();

         void set_font(ALLEGRO_FONT* font);
         int get_grid_width() const;
         int get_grid_height() const;
         std::map<char, std::tuple<float, float, float, float>> get_character_uv_mapping() const;
         bool get_initialized() const;
         ALLEGRO_BITMAP* get_created_character_map_bitmap();
         bool initialize();
      };
   }
}



