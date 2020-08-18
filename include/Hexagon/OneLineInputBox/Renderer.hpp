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
         ALLEGRO_COLOR backfill_color;
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
         std::string top_left_text;
         std::string top_right_text;
         std::string bottom_left_text;
         std::string bottom_right_text;

      public:
         Renderer(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR outline_and_text_color={0.0f,0.0f,0.0f,0.0f}, ALLEGRO_COLOR backfill_color={0.0f,0.0f,0.0f,0.0f}, float width=1.0f, float height=1.0f, int cell_width=1, int cell_height=1, std::vector<std::string> lines={}, std::vector<CodeRange> selections={}, int cursor_x=0, int cursor_y=0, placement3d place={}, int first_line_number=0, bool in_edit_mode=false, std::string top_left_text="", std::string top_right_text="", std::string bottom_left_text="", std::string bottom_right_text="");
         ~Renderer();

         void set_top_left_text(std::string top_left_text);
         void set_top_right_text(std::string top_right_text);
         void set_bottom_left_text(std::string bottom_left_text);
         void set_bottom_right_text(std::string bottom_right_text);

      void draw_selections(int cell_width=1, int cell_height=1, int first_line_number=0);
      void render();
      int get_lines_character_count();
      };
   }
}



