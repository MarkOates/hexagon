

#include <Hexagon/RerunOutputWatcher.hpp>
#include <allegro5/allegro_color.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <vector>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{


RerunOutputWatcher::RerunOutputWatcher(std::string command, std::string watch_pattern)
   : StageInterface(StageInterface::RERUN_OUTPUT_WATCHER)
   , command(command)
   , watch_pattern(watch_pattern)
   , output("[no content]")
{
}


RerunOutputWatcher::~RerunOutputWatcher()
{
}


void RerunOutputWatcher::set_command(std::string command)
{
   this->command = command;
}


void RerunOutputWatcher::set_watch_pattern(std::string watch_pattern)
{
   this->watch_pattern = watch_pattern;
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

void RerunOutputWatcher::append_to_output(std::string content_to_append)
{
output += content_to_append;

}

void RerunOutputWatcher::refresh()
{
output = "";
using std::placeholders::_1;
Blast::ShellCommandExecutorWithCallback executor(get_command(), std::bind(&RerunOutputWatcher::append_to_output, this, _1));
executor.execute();

}

void RerunOutputWatcher::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
get_place().start_transform();

if (!font) throw std::runtime_error("could not load font font");
al_draw_text(font, al_color_name("yellow"), 0, 0, 0, "+ RerunOutputWatcher");

int y_spacing = 20;
int x_col = 170;
int line_height = al_get_font_line_height(font);

// draw the command
al_draw_text(font, al_color_name("yellow"), 0, y_spacing * 1, 0, "command: ");
al_draw_text(font, al_color_name("aliceblue"), x_col, y_spacing * 1, 0, get_command().c_str());

// draw the command
al_draw_text(font, al_color_name("yellow"), 0, y_spacing * 2, 0, "watch_pattern: ");
al_draw_text(font, al_color_name("aliceblue"), x_col, y_spacing * 2, 0, get_watch_pattern().c_str());

// split the lines
int line_count = 0;
std::vector<std::string> output_lines = Blast::StringSplitter(get_output(), '\n').split();
// draw the output       
for (auto &line : output_lines)
{
   al_draw_text(font, al_color_name("dodgerblue"), 0, y_spacing * 3 + line_count * line_height, 0, line.c_str());
   line_count++;
   //std::cout << line << "-------" << std::endl;
}
get_place().restore_transform();

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


