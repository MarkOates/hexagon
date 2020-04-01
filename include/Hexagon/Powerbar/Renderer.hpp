#pragma once


#include <Hexagon/Powerbar/Powerbar.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace Powerbar
   {
      class Renderer
      {
      private:
         ALLEGRO_DISPLAY* display;
         Hexagon::Powerbar::Powerbar* powerbar;
         float width;

      public:
         Renderer(ALLEGRO_DISPLAY* display=nullptr, Hexagon::Powerbar::Powerbar* powerbar=nullptr, float width=1000.0f);
         ~Renderer();


      void render();
      };
   }
}



