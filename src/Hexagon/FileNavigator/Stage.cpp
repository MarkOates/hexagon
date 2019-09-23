

#include <Hexagon/FileNavigator/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <iostream>
#include <iostream>


namespace Hexagon
{
namespace FileNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface({})
   , circle_color(al_color_name("green"))
{
}


Stage::~Stage()
{
}


void Stage::set_circle_color(ALLEGRO_COLOR circle_color)
{
   this->circle_color = circle_color;
}


ALLEGRO_COLOR Stage::get_circle_color()
{
   return circle_color;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::string Stage::run()
{
return "Hello World!";
}

void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
al_draw_filled_circle(100, 100, 60, get_circle_color());
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
std::cout << "LocalEvent::" << event_name << std::endl;

try
{
   bool executed = false;

   if (event_name == "change_to_yellow")
   {
     executed = true;
     set_circle_color(al_color_name("yellow"));
   }
   //else if (event_name == ROTATE_STAGE_LEFT) { executed = true; rotate_stage_left(); }

   if (!executed) std::cerr << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
}
catch (const std::exception &exception)
{
   std::cerr << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
}

}

bool Stage::save_file()
{
return true;

}

void Stage::process_event(ALLEGRO_EVENT& action_data)
{
return;

}
} // namespace FileNavigator
} // namespace Hexagon


