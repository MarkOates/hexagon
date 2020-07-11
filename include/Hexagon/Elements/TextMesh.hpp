#pragma once


#include <Hexagon/Elements/BitmapGridMesh.hpp>
#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
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
         float cell_width;
         float cell_height;
         Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
         Hexagon::Elements::BitmapGridMesh mesh;
         ALLEGRO_BITMAP* font_character_map_bitmap;
         std::map<char, std::tuple<float, float, float, float>> font_character_uv_mapping;
         bool initialized;

      public:
         TextMesh(ALLEGRO_FONT* font=nullptr, int num_columns=0, int num_rows=0);
         ~TextMesh();


         int get_num_columns();
         int get_num_rows();
         float get_cell_width();
         float get_cell_height();
         Hexagon::Elements::BitmapGridMesh get_mesh();
         ALLEGRO_BITMAP* get_font_character_map_bitmap();
      void initialize();
      void set_cell_background_color(int x=0, int y=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
      void set_cell_character(int x=0, int y=0, char character='\0');
      int calculate_width();
      int calculate_height();
      void render();
      };
   }
}



