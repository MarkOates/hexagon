

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
std::map<std::string, std::function<void(AdvancedCodeEditor::Stage&)>> local_events_dictionary =
   build_local_events_dictionary();
return;

}

void EventController::process_event(ALLEGRO_EVENT& event)
{
return;

}

std::map<std::string, std::function<void(AdvancedCodeEditor::Stage&)>> EventController::build_local_events_dictionary()
{
std::map<std::string, std::function<void(AdvancedCodeEditor::Stage&)>> local_events = {
   { "cursor_move_up", &AdvancedCodeEditor::Stage::cursor_move_up },
};
return local_events;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


