#pragma once


#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class Renderer
      {
      private:
         Hexagon::AdvancedComponentNavigator::Stage* stage;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;

      public:
         Renderer();
         ~Renderer();


      void render();
      };
   }
}



