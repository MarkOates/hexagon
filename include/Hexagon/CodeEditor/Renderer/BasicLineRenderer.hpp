#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      namespace Renderer
      {
         class BasicLineRenderer
         {
         private:
            ALLEGRO_FONT* font;
            ALLEGRO_COLOR* font_color;
            float x;
            float y;
            std::string truncated_line;

         public:
            BasicLineRenderer();
            ~BasicLineRenderer();


         std::string run();
         void render();
         };
      }
   }
}



