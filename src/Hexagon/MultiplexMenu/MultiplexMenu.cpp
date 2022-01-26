

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(StageInterface* stage, std::vector<std::tuple<std::string, std::string, std::string, std::string>> items)
   : stage(stage)
   , items(items)
{
}


MultiplexMenu::~MultiplexMenu()
{
}


void MultiplexMenu::send_message_to_stage(std::string message)
{
   if (!(stage))
      {
         std::stringstream error_message;
         error_message << "MultiplexMenu" << "::" << "send_message_to_stage" << ": error: " << "guard \"stage\" not met";
         throw std::runtime_error(error_message.str());
      }
   stage->process_local_event(message);
   return;
}
} // namespace MultiplexMenu
} // namespace Hexagon


