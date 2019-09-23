

#include <Hexagon/FileNavigator/Stage.hpp>



namespace Hexagon
{
namespace FileNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface({})
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

void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
return;

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


