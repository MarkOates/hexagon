

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


EventController::EventController(Hexagon::AdvancedComponentNavigator::Stage* stage, std::map<std::string, std::function<void(Stage&)>> event_dictionary)
   : stage(stage)
   , event_dictionary(event_dictionary)
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

std::map<std::string, std::function<void(Stage&)>>::iterator it = event_dictionary.find(event_name);
if (it == event_dictionary.end())
{
   std::stringstream error_message;
   error_message << "AdvancedComponentNavigator::EventController::process_local_event: error: "
                 << "No local event named \"" << event_name << "\" exists.";
   throw std::runtime_error(error_message.str());
}
else
{
   event_dictionary[event_name](stage);
}

return;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


