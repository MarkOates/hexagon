

#include <Hexagon/ProjectComponentNavigator/EventController.hpp>

#include <Hexagon/ProjectComponentNavigator/EventController.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>


namespace Hexagon
{
namespace ProjectComponentNavigator
{


EventController::EventController(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator* component, std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>> event_dictionary)
   : component(component)
   , event_dictionary(event_dictionary)
{
}


EventController::~EventController()
{
}


void EventController::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ProjectComponentNavigator::EventController::process_local_event]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ProjectComponentNavigator::EventController::process_local_event]: error: guard \"component\" not met");
   }
   using Hexagon::ProjectComponentNavigator::ProjectComponentNavigator;
   ProjectComponentNavigator &component = *this->component;

   std::map<std::string, std::function<void(ProjectComponentNavigator&)>>::iterator it =
      event_dictionary.find(event_name);
   if (it == event_dictionary.end())
   {
      std::stringstream error_message;
      error_message << "ProjectComponentNavigator::EventController::process_local_event: error: "
                    << "No local event named \"" << event_name << "\" exists.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      event_dictionary[event_name](component);
   }

   return;
}


} // namespace ProjectComponentNavigator
} // namespace Hexagon


