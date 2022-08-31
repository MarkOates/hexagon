#pragma once


#include <Hexagon/StageInterface.hpp>
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
         Hexagon::System::System* system;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_COLOR* backfill_color;
         ALLEGRO_COLOR base_text_color;
         void draw_focused_frame(StageInterface* stage=nullptr);

      protected:


      public:
         Renderer(Hexagon::System::System* system=nullptr, ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_COLOR* backfill_color=nullptr, ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~Renderer();

         ALLEGRO_COLOR* get_backfill_color() const;
         ALLEGRO_COLOR get_base_text_color() const;
         bool render();
      };
   }
}



