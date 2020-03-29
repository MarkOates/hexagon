#pragma once


#include <Hexagon/System/System.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace System
   {
      class Renderer
      {
      private:
         ::System* system;
         ALLEGRO_DISPLAY* display;

      public:
         Renderer(::System* system=nullptr, ALLEGRO_DISPLAY* display=nullptr);
         ~Renderer();


      bool render();
      };
   }
}



