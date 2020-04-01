#pragma once


#include <Hexagon/Powerbar/Powerbar.hpp>
#include <allegro5/allegro.h>
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
         float width;

      public:
         Renderer(ALLEGRO_DISPLAY* display=nullptr, Hexagon::Powerbar::Powerbar* powerbar=nullptr, float width=1000.0f);
         ~Renderer();


      void draw_individual_rectangle(float x1=0.0f, float y1=0.0f, float x2=0.0f, float y2=0.0f, std::string text="[-]");
      void render();
      };
   }
}



