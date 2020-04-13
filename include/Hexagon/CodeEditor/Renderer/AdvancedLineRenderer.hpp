#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace CodeEditor
   {
      namespace Renderer
      {
         class AdvancedLineRenderer
         {
         private:
            ALLEGRO_FONT* font;
            ALLEGRO_COLOR* font_color;
            float x;
            float y;
            std::string line;

         public:
            AdvancedLineRenderer(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR* font_color=nullptr, float x=0.0f, float y=0.0f, std::string line="");
            ~AdvancedLineRenderer();


         std::vector<std::pair<std::string, ALLEGRO_COLOR>> build_tokens();
         void render_tokens(std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens={});
         void render();
         };
      }
   }
}



