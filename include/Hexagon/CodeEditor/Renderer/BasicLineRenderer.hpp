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

         protected:


         public:
            BasicLineRenderer(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR* font_color=nullptr, float x=0.0f, float y=0.0f, std::string truncated_line="");
            ~BasicLineRenderer();

            void render();
         };
      }
   }
}



