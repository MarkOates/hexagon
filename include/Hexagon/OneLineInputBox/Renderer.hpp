#pragma once


#include <AllegroFlare/FontBin.hpp>
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
         AllegroFlare::FontBin* font_bin;
         ALLEGRO_FONT* font;
         ALLEGRO_COLOR outline_color;
         ALLEGRO_COLOR user_input_text_color;
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
         std::string state;

      protected:


      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR outline_color={0.0f,0.0f,0.0f,0.0f}, ALLEGRO_COLOR user_input_text_color={0.0f,0.0f,0.0f,0.0f}, ALLEGRO_COLOR backfill_color={0.0f,0.0f,0.0f,0.0f}, float width=1.0f, float height=1.0f, int cell_width=1, int cell_height=1, std::vector<std::string> lines={}, std::vector<CodeRange> selections={}, int cursor_x=0, int cursor_y=0, placement3d place={}, int first_line_number=0, bool in_edit_mode=false, std::string top_left_text="", std::string top_right_text="", std::string bottom_left_text="", std::string bottom_right_text="");
         ~Renderer();

         void set_top_left_text(std::string top_left_text);
         void set_top_right_text(std::string top_right_text);
         void set_bottom_left_text(std::string bottom_left_text);
         void set_bottom_right_text(std::string bottom_right_text);
         void change_state_to_submitted_and_pending_destruction();
         bool is_state_to_submitted_and_pending_destruction();
         void draw_selections(int cell_width=1, int cell_height=1, int first_line_number=0);
         ALLEGRO_COLOR get_primary_color();
         ALLEGRO_COLOR get_user_input_text_color();
         void render();
         int get_lines_character_count();
      };
   }
}



