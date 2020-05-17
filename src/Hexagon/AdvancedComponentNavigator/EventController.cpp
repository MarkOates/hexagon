

#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
#include <map>
#include <string>
#include <functional>
#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


EventController::EventController(Hexagon::AdvancedComponentNavigator::Stage* stage)
   : stage(stage)
{
}


EventController::~EventController()
{
}


void EventController::process_local_event(std::string event_name, ActionData action_data)
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_local_event" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
using Hexagon::AdvancedComponentNavigator::Stage;
Stage &stage = *this->stage;

std::map<std::string, std::function<void(Stage&)>> local_events = {
   { "refresh_list", &Stage::refresh_list },
   { "move_cursor_to_top", &Stage::move_cursor_to_top },
   { "move_cursor_up", &Stage::move_cursor_up },
   { "move_cursor_down", &Stage::move_cursor_down },
   { "set_mode_to_navigating_list", &Stage::set_mode_to_navigating_list },
   { "set_mode_to_typing_in_search_bar", &Stage::set_mode_to_typing_in_search_bar },
};

std::map<std::string, std::function<void(Stage&)>>::iterator it = local_events.find(event_name);
if (it == local_events.end())
{
   std::stringstream error_message;
   error_message << "AdvancedComponentNavigator::EventController::process_local_event: error: "
                 << "No local event named \"" << event_name << "\" exists.";
   throw std::runtime_error(error_message.str());
}
else
{
   local_events[event_name](stage);
}

return;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


