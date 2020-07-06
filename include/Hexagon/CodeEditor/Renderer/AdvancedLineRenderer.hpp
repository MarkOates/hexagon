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
            ALLEGRO_COLOR* backfill_color;
            float x;
            float y;
            std::string full_line_text;
            int max_num_columns;

         public:
            AdvancedLineRenderer(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR* font_color=nullptr, ALLEGRO_COLOR* backfill_color=nullptr, float x=0.0f, float y=0.0f, std::string full_line_text="", int max_num_columns=121);
            ~AdvancedLineRenderer();


         std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> build_test_declaration_element_tokens();
         std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> build_quintessence_yaml_name_element_tokens();
         std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> build_quoted_string_tokens();
         std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> build_comment_tokens();
         void render_tokens(std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens={}, float cell_width=1.0f);
         void render();
         };
      }
   }
}



