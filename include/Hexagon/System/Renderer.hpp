#pragma once


#include <Hexagon/System/System.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>


namespace Hexagon
{
   namespace System
   {
      class Renderer
      {
      private:
         ::System* system;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_COLOR* backfill_color;

      public:
         Renderer(::System* system=nullptr, ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_COLOR* backfill_color=nullptr);
         ~Renderer();

         ALLEGRO_COLOR* get_backfill_color();
         bool render();
      };
   }
}



