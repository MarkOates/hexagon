#pragma once


#include <Hexagon/Shapes/Hexagon/Stroke.hpp>
#include <vector>


namespace Hexagon
{
   namespace Shapes
   {
      namespace Hexagon
      {
         class Renderer
         {
         private:
            float x;
            float y;
            float radius;
            std::vector<Shapes::Hexagon::Stroke> strokes;

         public:
            Renderer(float x=0, float y=0, float radius=0, std::vector<Shapes::Hexagon::Stroke> strokes={ { 1, 1, al_color_name("green") } });
            ~Renderer();

            void render();
         };
      }
   }
}



