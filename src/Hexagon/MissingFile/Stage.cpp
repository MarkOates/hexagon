

#include <Hexagon/MissingFile/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
namespace MissingFile
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::FILE_MISSING)
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
float width = al_get_display_width(display);
float height = al_get_display_height(display);
ALLEGRO_COLOR color = al_color_html("d82133");
float thickness = 2.5;
al_draw_rectangle(0, 0, width, height, color, thickness);
al_draw_text(font, color, width/2, height/3*2, ALLEGRO_ALIGN_CENTER, text.c_str());

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


