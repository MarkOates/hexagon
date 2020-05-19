

#include <Hexagon/OneLineInputBox/Renderer.hpp>
#include <iostream>
#include <iostream>
#include <Hexagon/CodeRangeRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>
#include <allegro_flare/placement3d.h>
#include <Hexagon/shared_globals.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace OneLineInputBox
{


Renderer::Renderer(ALLEGRO_FONT* font, ALLEGRO_COLOR outline_and_text_color, float width, float height, int cell_width, int cell_height, std::vector<std::string> lines, std::vector<CodeRange> selections, int cursor_x, int cursor_y, placement3d place, int first_line_number, bool in_edit_mode)
   : font(font)
   , outline_and_text_color(outline_and_text_color)
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
{
}


Renderer::~Renderer()
{
}


void Renderer::draw_selections(int cell_width, int cell_height, int first_line_number)
{
for (auto &selection : selections)
{
   std::cout << " drawing selection " << selection << std::endl;
   CodeRangeRenderer(lines, selection, first_line_number, cell_width, cell_height).render();
}

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

ALLEGRO_COLOR backfill_color = hexagon_get_backfill_color();
backfill_color = color::color(backfill_color, hexagon_get_backfill_opacity());

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
   outline_and_text_color,
   3.0);

float _cursor_y = cursor_y - first_line_number;
//switch(mode)
//{
//case EDIT:
if (in_edit_mode)
{
   al_draw_filled_rectangle(
      cursor_x*cell_width,
      _cursor_y*cell_height,
      cursor_x*cell_width + cell_width,
      _cursor_y*cell_height + cell_height,
      al_color_name("gray"));
}
//   break;
//case INSERT:
else
{
   al_draw_line(
      cursor_x*cell_width,
      _cursor_y*cell_height,
      cursor_x*cell_width,
      _cursor_y*cell_height + cell_height,
      al_color_name("gray"),
      3);
   //break;
}

draw_selections(cell_width, cell_height, first_line_number);

int line_height = al_get_font_line_height(font);
for (int i=0; i<lines.size(); i++)
{
   al_draw_text(font, outline_and_text_color, 0, i*line_height, ALLEGRO_ALIGN_LEFT, lines[i].c_str());
}

place.restore_transform();

}
} // namespace OneLineInputBox
} // namespace Hexagon


