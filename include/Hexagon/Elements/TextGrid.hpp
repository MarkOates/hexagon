#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class TextGrid
      {
      private:
         ALLEGRO_FONT* font;
         int num_columns;
         int num_rows;
         float cell_width;
         float cell_height;
         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid;

      public:
         TextGrid(ALLEGRO_FONT* font=nullptr, int num_columns=16, int num_rows=12, float cell_width=1.0, float cell_height=1.0, std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid={});
         ~TextGrid();


      void set_cell_color(int x=0, int y=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
      void render();
      };
   }
}



