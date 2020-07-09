#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class TextMesh
      {
      private:
         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& grid;
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> dummy_grid;
         std::vector<ALLEGRO_VERTEX> vertexes;
         int num_columns;
         int num_rows;
         float cell_width;
         float cell_height;

      public:
         TextMesh();
         ~TextMesh();


         std::vector<ALLEGRO_VERTEX> get_vertexes();
         int get_num_columns();
         int get_num_rows();
         float get_cell_width();
         float get_cell_height();
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &get_dummy_grid_ref();
      bool resize(int num_columns=0, int num_rows=0, float cell_width=0.0f, float cell_height=0.0f);
      void render();
      };
   }
}



