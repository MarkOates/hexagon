#pragma once


#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class Renderer
      {
      private:
         float surface_width;
         float surface_height;
         Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar;

      protected:


      public:
         Renderer(float surface_width=(1920/2), float surface_height=(1080/2), Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar=nullptr);
         ~Renderer();

         void render();
      };
   }
}



