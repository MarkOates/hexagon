#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace OneLineInputBox
   {
      class Renderer
      {
      private:
         ALLEGRO_FONT* font;
         ALLEGRO_COLOR outline_and_text_color;
         int cell_width;
         int cell_height;

      public:
         Renderer();
         ~Renderer();


      void render();
      };
   }
}



