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
         float width;
         float height;
         int cell_width;
         int cell_height;

      public:
         Renderer();
         ~Renderer();


      void render_raw(int cursor_x=0, int cursor_y=0);
      };
   }
}



