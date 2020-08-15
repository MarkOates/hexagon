#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class DynamicGridMesh
      {
      private:
         std::vector<ALLEGRO_VERTEX> vertexes;
         ALLEGRO_BITMAP* texture;

      public:
         DynamicGridMesh(ALLEGRO_BITMAP* texture=nullptr);
         ~DynamicGridMesh();

         void set_texture(ALLEGRO_BITMAP* texture);

         std::vector<ALLEGRO_VERTEX> get_vertexes();
         ALLEGRO_BITMAP* get_texture();
      void set_or_create_cell();
      void delete_cell();
      void render();
      };
   }
}



