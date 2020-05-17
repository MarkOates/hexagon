

#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
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
Hexagon::AdvancedComponentNavigator::Stage &stage = *this->stage;
bool executed = false;

if (event_name == "refresh_list")
{
  executed = true;
  stage.refresh_list();
}
else if (event_name == "move_cursor_to_top")
{
  executed = true;
  stage.move_cursor_to_top();
}
else if (event_name == "move_cursor_up")
{
  executed = true;
  stage.move_cursor_up();
}
else if (event_name == "move_cursor_down")
{
  executed = true;
  stage.move_cursor_down();
}
else if (event_name == "set_mode_to_navigating_list")
{
  executed = true;
  stage.set_mode_to_navigating_list();
}
else if (event_name == "set_mode_to_typing_in_search_bar")
{
  executed = true;
  stage.set_mode_to_typing_in_search_bar();
}

if (!executed)
{
   std::stringstream error_message;
   error_message << "AdvancedComponentNavigator::EventController::process_local_event: error: "
                 << "No local event named \"" << event_name << "\" exists.";
   throw std::runtime_error(error_message.str());
}
return;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


