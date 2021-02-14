

#include <Hexagon/MissingFile/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
namespace MissingFile
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string expected_filename)
   : StageInterface(StageInterface::MISSING_FILE)
   , expected_filename(expected_filename)
   , text("MISSING FILE")
   , is_focused(true)
   , display(nullptr)
   , font(nullptr)
   , cell_width(10)
   , cell_height(20)
{
}


Stage::~Stage()
{
}


void Stage::set_is_focused(bool is_focused)
{
   this->is_focused = is_focused;
}


void Stage::set_display(ALLEGRO_DISPLAY* display)
{
   this->display = display;
}


void Stage::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


void Stage::set_cell_width(int cell_width)
{
   this->cell_width = cell_width;
}


void Stage::set_cell_height(int cell_height)
{
   this->cell_height = cell_height;
}


std::string Stage::get_expected_filename()
{
   return expected_filename;
}


bool Stage::get_is_focused()
{
   return is_focused;
}


ALLEGRO_DISPLAY* Stage::get_display()
{
   return display;
}


ALLEGRO_FONT* Stage::get_font()
{
   return font;
}


int Stage::get_cell_width()
{
   return cell_width;
}


int Stage::get_cell_height()
{
   return cell_height;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
   placement3d place = get_place();
   place.start_transform();

   float padding = cell_width;
   float h_padding = (float)cell_width / 2;
   float line_height = al_get_font_line_height(font);

   float width = place.size.x;
   float height = place.size.y;
   ALLEGRO_COLOR color = al_color_html("d82133");
   float thickness = 2.5;
   al_draw_rectangle(
     h_padding, h_padding,
     width-h_padding, height-h_padding,
     color, thickness);
   al_draw_text(font, color, width/2, height/3, ALLEGRO_ALIGN_CENTER, text.c_str());

   al_draw_text(font, color, width/2, height/3 + line_height*3, ALLEGRO_ALIGN_CENTER, expected_filename.c_str());

   place.restore_transform();
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}
} // namespace MissingFile
} // namespace Hexagon


