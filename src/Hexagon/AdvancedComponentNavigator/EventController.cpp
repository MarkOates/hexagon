

#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>

#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


EventController::EventController(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator* component, std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>> event_dictionary)
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
      error_message << "[EventController::process_local_event]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventController::process_local_event: error: guard \"component\" not met");
   }
   using Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator;
   AdvancedComponentNavigator &component = *this->component;

   std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>>
      ::iterator it =
         event_dictionary.find(event_name);
   if (it == event_dictionary.end())
   {
      std::stringstream error_message;
      error_message << "AdvancedComponentNavigator::EventController::process_local_event: error: "
                    << "No local event named \"" << event_name << "\" exists.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      std::stringstream info_message;
      info_message << "AdvancedComponentNavigator::EventController::process_local_event: info: "
                   << "handling event named \"" << event_name << "\": ";
      std::cout << info_message.str() << std::endl;

      event_dictionary[event_name](component);

      std::stringstream info_message2;
      info_message2 << "AdvancedComponentNavigator::EventController::process_local_event: info: "
                   << "handled event named \"" << event_name << "\".";
      std::cout << info_message2.str() << std::endl;
   }

   return;
}


} // namespace AdvancedComponentNavigator
} // namespace Hexagon


