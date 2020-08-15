#pragma once


#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class DynamicGridMesh
      {
      private:
         std::vector<ALLEGRO_VERTEX> vertexes;

      public:
         DynamicGridMesh();
         ~DynamicGridMesh();


         std::vector<ALLEGRO_VERTEX> get_vertexes();
      std::string run();
      };
   }
}



