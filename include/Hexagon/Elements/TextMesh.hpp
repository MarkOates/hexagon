#pragma once


#include <Hexagon/Elements/BitmapGridMesh.hpp>
#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>
#include <tuple>


namespace Hexagon
{
   namespace Elements
   {
      class TextMesh
      {
      private:
         ALLEGRO_FONT* font;
         int num_columns;
         int num_rows;
         Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
         Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
         ALLEGRO_BITMAP* character_map_bitmap;
         std::map<char, std::tuple<float, float, float, float>> character_uv_mapping;
         bool initialized;

      public:
         TextMesh(ALLEGRO_FONT* font=nullptr);
         ~TextMesh();


      void initialize();
      void render();
      };
   }
}



