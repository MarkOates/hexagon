

#include <Hexagon/MultiplexMenu/CommandExecutor.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


CommandExecutor::CommandExecutor(StageInterface* stage_to_send_messages_to, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu)
   : stage_to_send_messages_to(stage_to_send_messages_to)
   , multiplex_menu(multiplex_menu)
{
}


CommandExecutor::~CommandExecutor()
{
}


void CommandExecutor::send_message_to_stage(std::string message)
{
   if (!(stage_to_send_messages_to))
      {
         std::stringstream error_message;
         error_message << "CommandExecutor" << "::" << "send_message_to_stage" << ": error: " << "guard \"stage_to_send_messages_to\" not met";
         throw std::runtime_error(error_message.str());
      }
   stage_to_send_messages_to->process_local_event(message);
   return;
}

void CommandExecutor::execute()
{
   if (!(stage_to_send_messages_to))
      {
         std::stringstream error_message;
         error_message << "CommandExecutor" << "::" << "execute" << ": error: " << "guard \"stage_to_send_messages_to\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(multiplex_menu))
      {
         std::stringstream error_message;
         error_message << "CommandExecutor" << "::" << "execute" << ": error: " << "guard \"multiplex_menu\" not met";
         throw std::runtime_error(error_message.str());
      }
   send_message_to_stage(multiplex_menu->get_final_command_to_execute());
}
} // namespace MultiplexMenu
} // namespace Hexagon


