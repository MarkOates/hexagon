

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT EventController::a_default_empty_event = {};


EventController::EventController(Hexagon::AdvancedCodeEditor::Stage* stage, std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> events_dictionary)
   : stage(stage)
   , events_dictionary(events_dictionary)
{
}


EventController::~EventController()
{
}


std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> &EventController::get_events_dictionary_ref()
{
   return events_dictionary;
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

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>>::iterator it =
   events_dictionary.find(event_name);
if (it == events_dictionary.end())
{
   std::stringstream error_message;
   error_message << "AdvancedCodeEditor::EventController::process_local_event: error: "
                 << "No local event named \"" << event_name << "\" exists.";
   throw std::runtime_error(error_message.str());
}
else
{
   events_dictionary[event_name](component);
}

return;

}

void EventController::process_event(ALLEGRO_EVENT& event)
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_event" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
switch(event.type)
{
case ALLEGRO_EVENT_KEY_DOWN:
   break;
case ALLEGRO_EVENT_KEY_UP:
   break;
case ALLEGRO_EVENT_KEY_CHAR:
   //std::vector<std::string> mapped_events = {};
   //if (mapped_events.empty())
   {
      char character = (char)(event.keyboard.unichar);
      stage->get_input_buffer_ref() = " ";
      stage->get_input_buffer_ref()[0] = character;
      process_local_event("insert_string");
      process_local_event("cursor_move_right");
   }
   return;
}

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


