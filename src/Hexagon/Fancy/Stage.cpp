

#include <Hexagon/Fancy/Stage.hpp>



namespace Hexagon
{
namespace Fancy
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::FANCY)
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

void Stage::render()
{
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
} // namespace Fancy
} // namespace Hexagon


