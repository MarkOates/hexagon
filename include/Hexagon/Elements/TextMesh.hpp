#pragma once


#include <Hexagon/Elements/BitmapGridMesh.hpp>
#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <map>
#include <tuple>
#include <utility>
#include <vector>


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
         Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
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
         Hexagon::Elements::BitmapGridMesh get_bitmap_grid_mesh();
         ALLEGRO_BITMAP* get_font_character_map_bitmap();
         bool get_initialized();
         void set_font(ALLEGRO_FONT* font=nullptr);
         void initialize();
         void destruct();
         void set_cell_color(int x=0, int y=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
         void set_cell_character(int x=0, int y=0, char character='\0');
         int calculate_width();
         int calculate_height();
         void render();
         void render_only_select_cells(std::vector<std::pair<int, int>> cell_coordinates={});
      };
   }
}



