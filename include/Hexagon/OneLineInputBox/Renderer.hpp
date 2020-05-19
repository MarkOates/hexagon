#pragma once


#include <Hexagon/CodeRange.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/placement3d.h>
#include <string>
#include <vector>


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
         std::vector<std::string> lines;
         std::vector<CodeRange> selections;
         int cursor_x;
         int cursor_y;
         placement3d place;
         int first_line_number;
         bool in_edit_mode;

      public:
         Renderer(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR outline_and_text_color={0.0f,0.0f,0.0f,0.0f}, float width=1.0f, float height=1.0f, int cell_width=1, int cell_height=1, std::vector<std::string> lines={}, std::vector<CodeRange> selections={}, int cursor_x=0, int cursor_y=0, placement3d place={}, int first_line_number=0, bool in_edit_mode=false);
         ~Renderer();


      void draw_selections(int cell_width=1, int cell_height=1, int first_line_number=0);
      void render();
      };
   }
}



