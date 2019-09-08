

#include <Hexagon/RerunOutputWatcher.hpp>
#include <allegro5/allegro_color.h>


namespace Hexagon
{


RerunOutputWatcher::RerunOutputWatcher()
   : StageInterface(StageInterface::RERUN_OUTPUT_WATCHER)
   , command("make")
   , watch_pattern("**.*.q.yml")
   , output("[no content]")
{
}


RerunOutputWatcher::~RerunOutputWatcher()
{
}


std::string RerunOutputWatcher::get_command()
{
   return command;
}


std::string RerunOutputWatcher::get_watch_pattern()
{
   return watch_pattern;
}


std::string RerunOutputWatcher::get_output()
{
   return output;
}


ALLEGRO_EVENT& RerunOutputWatcher::dummy_ALLEGRO_EVENT()
{
static ALLEGRO_EVENT ev;
return ev;

}

bool RerunOutputWatcher::append_to_output(std::string content_to_append)
{
output += content_to_append;
return true;

}

void RerunOutputWatcher::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
static ALLEGRO_FONT *font_font = al_create_builtin_font();
if (!font_font) throw std::runtime_error("could not load font font");
al_draw_text(font_font, al_color_name("yellow"), 0, 0, 0, "+ RerunOutputWatcher");

int y_spacing = 20;
int x_col = 130;

// draw the command
al_draw_text(font_font, al_color_name("yellow"), 0, y_spacing * 1, 0, "command: ");
al_draw_text(font_font, al_color_name("aliceblue"), x_col, y_spacing * 1, 0, get_command().c_str());

// draw the command
al_draw_text(font_font, al_color_name("yellow"), 0, y_spacing * 2, 0, "watch_pattern: ");
al_draw_text(font_font, al_color_name("aliceblue"), x_col, y_spacing * 2, 0, get_watch_pattern().c_str());

// draw the output
al_draw_text(font_font, al_color_name("white"), x_col, y_spacing * 2, 0, get_output().c_str());

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


