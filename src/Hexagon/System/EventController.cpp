

#include <Hexagon/System/EventController.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{


EventController::EventController(::System* system)
   : system(system)
{
}


EventController::~EventController()
{
}


void EventController::process_event()
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_event" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
return;

}
} // namespace System
} // namespace Hexagon


