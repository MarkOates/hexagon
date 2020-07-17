#pragma once


#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class Renderer
      {
      private:
         ALLEGRO_DISPLAY* display;
         Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar;

      public:
         Renderer(ALLEGRO_DISPLAY* display=nullptr, Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar=nullptr);
         ~Renderer();


      void render();
      };
   }
}



