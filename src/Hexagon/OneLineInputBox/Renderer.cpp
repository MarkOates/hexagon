

#include <Hexagon/OneLineInputBox/Renderer.hpp>
#include <iostream>
#include <iostream>
#include <Hexagon/CodeSelectionBoxRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>
#include <allegro_flare/placement3d.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace OneLineInputBox
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin, ALLEGRO_FONT* font, ALLEGRO_COLOR outline_color, ALLEGRO_COLOR user_input_text_color, ALLEGRO_COLOR backfill_color, float width, float height, int cell_width, int cell_height, std::vector<std::string> lines, std::vector<CodeRange> selections, int cursor_x, int cursor_y, placement3d place, int first_line_number, bool in_edit_mode, std::string top_left_text, std::string top_right_text, std::string bottom_left_text, std::string bottom_right_text)
   : font_bin(font_bin)
   , font(font)
   , outline_color(outline_color)
   , user_input_text_color(user_input_text_color)
   , backfill_color(backfill_color)
   , width(width)
   , height(height)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , lines(lines)
   , selections(selections)
   , cursor_x(cursor_x)
   , cursor_y(cursor_y)
   , place(place)
   , first_line_number(first_line_number)
   , in_edit_mode(in_edit_mode)
   , top_left_text(top_left_text)
   , top_right_text(top_right_text)
   , bottom_left_text(bottom_left_text)
   , bottom_right_text(bottom_right_text)
   , state("normal")
{
}


Renderer::~Renderer()
{
}


void Renderer::set_top_left_text(std::string top_left_text)
{
   this->top_left_text = top_left_text;
}


void Renderer::set_top_right_text(std::string top_right_text)
{
   this->top_right_text = top_right_text;
}


void Renderer::set_bottom_left_text(std::string bottom_left_text)
{
   this->bottom_left_text = bottom_left_text;
}


void Renderer::set_bottom_right_text(std::string bottom_right_text)
{
   this->bottom_right_text = bottom_right_text;
}


void Renderer::change_state_to_submitted_and_pending_destruction()
{
   state = "submitted_and_pending_destruction";
   return;
}

bool Renderer::is_state_to_submitted_and_pending_destruction()
{
   return state == "submitted_and_pending_destruction";
}

void Renderer::draw_selections(int cell_width, int cell_height, int first_line_number)
{
   for (auto &selection : selections)
   {
      std::cout << " drawing selection " << selection << std::endl;
      Hexagon::CodeSelectionBoxRenderer(&lines, &selection, first_line_number, cell_width, cell_height).render();
   }
}

ALLEGRO_COLOR Renderer::get_primary_color()
{
   if (is_state_to_submitted_and_pending_destruction())
   {
      return ALLEGRO_COLOR{1, 1, 1, 1};
   }
   else return outline_color;
}

ALLEGRO_COLOR Renderer::get_user_input_text_color()
{
   if (is_state_to_submitted_and_pending_destruction())
   {
      return ALLEGRO_COLOR{1, 1, 1, 1};
   }
   else return user_input_text_color;
}

void Renderer::render()
{
   if (!(font))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"font\" not met";
         throw std::runtime_error(error_message.str());
      }
   //placement3d place = get_place();
   place.start_transform();

   //ALLEGRO_COLOR backfill_color = hexagon_get_backfill_color();
   //backfill_color = color::color(backfill_color, hexagon_get_backfill_opacity());

   ALLEGRO_COLOR color = get_primary_color();
   ALLEGRO_COLOR user_input_text_color = get_user_input_text_color();

   float outer_roundness = 12;
   float inner_roundness = 6;
   float padding = 6;
   al_draw_filled_rounded_rectangle(
      0-padding*2,
      0-padding*2,
      place.size.x+padding*2,
      place.size.y+padding*2,
      outer_roundness,
      outer_roundness,
      backfill_color);
   al_draw_rounded_rectangle(
      0-padding,
      0-padding,
      place.size.x+padding,
      place.size.y+padding,
      inner_roundness,
      inner_roundness,
      color,
      3.0);

   // draw_top_left_text
   if (!top_left_text.empty())
   {
      float line_height = al_get_font_line_height(font);
      float x = 0;
      float y = -padding - line_height/2;
      float x2 = x + al_get_text_width(font, top_left_text.c_str());
      float y2 = y + line_height;

      al_draw_filled_rectangle(x, y, x2, y2, backfill_color);
      al_draw_text(font, color, x, y, ALLEGRO_ALIGN_LEFT, top_left_text.c_str());
   }

   // draw_top_right_text
   if (!top_right_text.empty())
   {
      float line_height = al_get_font_line_height(font);
      float x = place.size.x;
      float y = -padding - line_height/2;

      float x1 = x - al_get_text_width(font, top_right_text.c_str());
      float y1 = y;
      float x2 = x;
      float y2 = y + line_height;

      al_draw_filled_rectangle(x1, y1, x2, y2, backfill_color);
      al_draw_text(font, color, x, y, ALLEGRO_ALIGN_RIGHT, top_right_text.c_str());
   }

   // draw_bottom_right_text
   if (!bottom_right_text.empty())
   {
      float line_height = al_get_font_line_height(font);
      float x = place.size.x;
      float y = place.size.y + padding - line_height/2;

      float x1 = x - al_get_text_width(font, bottom_right_text.c_str());
      float y1 = y;
      float x2 = x;
      float y2 = y + line_height;

      al_draw_filled_rectangle(x1, y1, x2, y2, backfill_color);
      al_draw_text(font, color, x, y, ALLEGRO_ALIGN_RIGHT, bottom_right_text.c_str());
   }

   if (!bottom_left_text.empty())
   {
      float line_height = al_get_font_line_height(font);
      //float x = place.size.x;
      float y = place.size.y + padding - line_height/2;

      float x1 = 0; //x - al_get_text_width(font, bottom_left_text.c_str());
      float y1 = y;
      float x2 = 0 + al_get_text_width(font, bottom_left_text.c_str());
      float y2 = y + line_height;

      al_draw_filled_rectangle(x1, y1, x2, y2, backfill_color);
      al_draw_text(font, color, x1, y1, 0, bottom_left_text.c_str());
   }

   float _cursor_y = cursor_y - first_line_number;
   float text_length_to_cursor_x = 0; //cursor_x * cell_width;
   float character_width_at_cursor_x = cell_width;
   if (cursor_y < 0 || cursor_y >= lines.size()) {}
   else
   {
      int length_of_line = lines[cursor_y].size();
      text_length_to_cursor_x = al_get_text_width(
         font,
         lines[cursor_y].substr(0, std::min(length_of_line, cursor_x)).c_str()
      );

      if (cursor_x < length_of_line)
      {
         std::string current_char_str_at_cursor_x = " ";
         current_char_str_at_cursor_x[0] = lines[cursor_y][cursor_x];
         character_width_at_cursor_x = al_get_text_width(font, current_char_str_at_cursor_x.c_str());
      }
      if (cursor_x > length_of_line)
      {
         float extra_x_length = 0;
         // TODO: There appears to be a bug in here that is making the extension longer
         int length_of_extension = cursor_x - length_of_line;
         extra_x_length = al_get_text_width(font, "x") * length_of_extension;
         text_length_to_cursor_x += extra_x_length;
      }
   }
   //switch(mode)
   //{
   //case EDIT:
   if (in_edit_mode)
   {
      float width_of_character_at_cursor_x = character_width_at_cursor_x;
      al_draw_filled_rectangle(
         text_length_to_cursor_x,
         _cursor_y*cell_height,
         text_length_to_cursor_x + width_of_character_at_cursor_x,
         _cursor_y*cell_height + cell_height,
         al_color_name("gray"));
   }
   //   break;
   //case INSERT:
   else
   {
      al_draw_line(
         text_length_to_cursor_x,
         _cursor_y*cell_height,
         text_length_to_cursor_x,
         _cursor_y*cell_height + cell_height,
         al_color_name("gray"),
         3);
      //break;
   }

   draw_selections(cell_width, cell_height, first_line_number);

   int line_height = al_get_font_line_height(font);
   for (int i=0; i<lines.size(); i++)
   {
      al_draw_text(font, user_input_text_color, 0, i*line_height, ALLEGRO_ALIGN_LEFT, lines[i].c_str());
   }

   place.restore_transform();
}

int Renderer::get_lines_character_count()
{
   int char_count = 0;
   for (int i=0; i<lines.size(); i++)
   {
      char_count += lines[i].size();
   }
   return char_count + (lines.size() - 1);
}
} // namespace OneLineInputBox
} // namespace Hexagon


