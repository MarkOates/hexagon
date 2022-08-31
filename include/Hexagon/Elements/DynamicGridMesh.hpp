#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <map>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class DynamicGridMesh
      {
      private:
         std::vector<ALLEGRO_VERTEX> vertexes;
         int cell_width;
         int cell_height;
         ALLEGRO_BITMAP* texture;
         std::map<std::tuple<int, int>, int> cells;

      protected:


      public:
         DynamicGridMesh(int cell_width=1, int cell_height=1, ALLEGRO_BITMAP* texture=nullptr);
         ~DynamicGridMesh();

         void set_texture(ALLEGRO_BITMAP* texture);
         std::vector<ALLEGRO_VERTEX> get_vertexes() const;
         ALLEGRO_BITMAP* get_texture() const;
         void create_or_set_cell(int x=0, int y=0, int u1=0, int v1=0, int u2=0, int v2=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
         void delete_cell(int x=0, int y=0);
         void render();
      };
   }
}



