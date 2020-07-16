

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT EventController::a_default_empty_event = {};


EventController::EventController()
   : stage(nullptr)
{
}


EventController::~EventController()
{
}


ALLEGRO_EVENT &EventController::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void EventController::process_local_event(std::string event_name, ActionData action_data)
{
return;

}

void EventController::process_event(ALLEGRO_EVENT& event)
{
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


