#pragma once


#include <Hexagon/Powerbar/Powerbar.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Powerbar
   {
      class Renderer
      {
      private:
         ALLEGRO_DISPLAY* display;
         Hexagon::Powerbar::Powerbar* powerbar;
         ALLEGRO_FONT* font;
         float width;
         bool draw_state_boxes;
         bool draw_focus_timer;

      public:
         Renderer(ALLEGRO_DISPLAY* display=nullptr, Hexagon::Powerbar::Powerbar* powerbar=nullptr, ALLEGRO_FONT* font=nullptr, float width=1000.0f);
         ~Renderer();


      void draw_focus_timer_bar();
      void draw_individual_rectangle(float x1=0.0f, float y1=0.0f, float x2=0.0f, float y2=0.0f, std::string text="[-]");
      void render();
      };
   }
}



