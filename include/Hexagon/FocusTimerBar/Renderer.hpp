#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         float surface_width;
         float surface_height;
         Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar;

      protected:


      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, float surface_width=(1920/2), float surface_height=(1080/2), Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar=nullptr);
         ~Renderer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_focus_timer_bar(Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar);
         AllegroFlare::FontBin* get_font_bin() const;
         void render();
      };
   }
}



