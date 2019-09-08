

#include <Hexagon/RerunOutputWatcher.hpp>
#include <allegro5/allegro_color.h>


namespace Hexagon
{


RerunOutputWatcher::RerunOutputWatcher()
   : StageInterface(StageInterface::RERUN_OUTPUT_WATCHER)
{
}


RerunOutputWatcher::~RerunOutputWatcher()
{
}


ALLEGRO_EVENT& RerunOutputWatcher::dummy_ALLEGRO_EVENT()
{
static ALLEGRO_EVENT ev;
return ev;

}

void RerunOutputWatcher::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
static ALLEGRO_FONT *font_font = al_create_builtin_font();
if (!font_font) throw std::runtime_error("could not load font font");
al_draw_text(font_font, al_color_name("yellow"), 0, 0, 0, "+ RerunOutputWatcher");
return;

}

void RerunOutputWatcher::process_local_event(std::string event_name, ActionData action_data)
{
return;

}

void RerunOutputWatcher::process_event(ALLEGRO_EVENT& event)
{
return;

}

bool RerunOutputWatcher::save_file()
{
return true;

}
} // namespace Hexagon


