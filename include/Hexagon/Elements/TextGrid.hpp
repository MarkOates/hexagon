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
         float cell_width;
         float cell_height;
         float cell_spacing_x;
         float cell_spacing_y;
         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid;

      public:
         TextGrid(ALLEGRO_FONT* font=nullptr, float cell_width=1.0f, float cell_height=1.0f, float cell_spacing_x=0.0f, float cell_spacing_y=0.0f, std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid={});
         ~TextGrid();


      void set_cell_color(int x=0, int y=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
      void render();
      };
   }
}



