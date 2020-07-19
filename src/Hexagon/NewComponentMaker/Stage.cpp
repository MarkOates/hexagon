

#include <Hexagon/NewComponentMaker/Stage.hpp>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{
namespace NewComponentMaker
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string current_project_directory, std::string component_name)
   : StageInterface(StageInterface::NEW_COMPONENT_MAKER)
   , current_project_directory(current_project_directory)
   , component_name(component_name)
{
}


Stage::~Stage()
{
}


std::string Stage::get_current_project_directory()
{
   return current_project_directory;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
placement3d place = get_place();
al_draw_rectangle(0, 0, place.size.x, place.size.y, ALLEGRO_COLOR{0.2f, 0.2f, 0.2f, 0.2f}, 4.0f);
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
return;

}
} // namespace NewComponentMaker
} // namespace Hexagon


