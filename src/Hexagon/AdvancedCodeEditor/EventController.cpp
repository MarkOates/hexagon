

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT EventController::a_default_empty_event = {};


EventController::EventController(Hexagon::AdvancedCodeEditor::Stage* stage)
   : stage(stage)
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
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_local_event" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::AdvancedCodeEditor::Stage &component = *stage;

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> local_events_dictionary =
   build_local_events_dictionary();

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>>::iterator it =
   local_events_dictionary.find(event_name);
if (it == local_events_dictionary.end())
{
   std::stringstream error_message;
   error_message << "AdvancedCodeEditor::EventController::process_local_event: error: "
                 << "No local event named \"" << event_name << "\" exists.";
   throw std::runtime_error(error_message.str());
}
else
{
   local_events_dictionary[event_name](component);
}

return;

}

void EventController::process_event(ALLEGRO_EVENT& event)
{
return;

}

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> EventController::build_local_events_dictionary()
{
std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> local_events = {
   { "cursor_move_up", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_up },
};
return local_events;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


