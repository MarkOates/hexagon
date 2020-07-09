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
         int width;
         int height;

      public:
         TextMesh();
         ~TextMesh();


         int get_width();
         int get_height();
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &get_dummy_grid_ref();
      bool resize();
      void render();
      };
   }
}



