

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
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::string Stage::run()
{
return "Hello World!";
}

void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
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


