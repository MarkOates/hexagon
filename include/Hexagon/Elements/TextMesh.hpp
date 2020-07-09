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
         ALLEGRO_BITMAP* bitmap;

      public:
         TextMesh();
         ~TextMesh();

         void set_bitmap(ALLEGRO_BITMAP* bitmap);

         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& get_grid();
         std::vector<ALLEGRO_VERTEX> get_vertexes();
         int get_num_columns();
         int get_num_rows();
         float get_cell_width();
         float get_cell_height();
         ALLEGRO_BITMAP* get_bitmap();
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &get_dummy_grid_ref();
      std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>* get_cell(int x=0, int y=0);
      bool resize(int num_columns=0, int num_rows=0, float cell_width=0.0f, float cell_height=0.0f);
      void render();
      float calculate_width();
      float calculate_height();
      };
   }
}



