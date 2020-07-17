#pragma once


#include <Hexagon/Powerbar/Powerbar.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class Renderer
      {
      private:
         ALLEGRO_DISPLAY* display;
         Hexagon::Powerbar::Powerbar* powerbar;

      public:
         Renderer(ALLEGRO_DISPLAY* display=nullptr, Hexagon::Powerbar::Powerbar* powerbar=nullptr);
         ~Renderer();


      void render();
      };
   }
}



