#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <tuple>
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


         std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> build_comment_tokens();
         void render_tokens(std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens={}, float cell_width=1.0f);
         void render();
         };
      }
   }
}



