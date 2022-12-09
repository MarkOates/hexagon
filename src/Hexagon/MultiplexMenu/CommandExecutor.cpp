

#include <Hexagon/MultiplexMenu/CommandExecutor.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[CommandExecutor::send_message_to_stage]: error: guard \"stage_to_send_messages_to\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CommandExecutor::send_message_to_stage: error: guard \"stage_to_send_messages_to\" not met");
   }
   stage_to_send_messages_to->process_local_event(message);
   return;
}

bool CommandExecutor::execute()
{
   if (!(stage_to_send_messages_to))
   {
      std::stringstream error_message;
      error_message << "[CommandExecutor::execute]: error: guard \"stage_to_send_messages_to\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CommandExecutor::execute: error: guard \"stage_to_send_messages_to\" not met");
   }
   if (!(multiplex_menu))
   {
      std::stringstream error_message;
      error_message << "[CommandExecutor::execute]: error: guard \"multiplex_menu\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CommandExecutor::execute: error: guard \"multiplex_menu\" not met");
   }
   for (auto &command : multiplex_menu->get_final_command_set_to_execute())
   {
      send_message_to_stage(command);
   }
   return true;
}


} // namespace MultiplexMenu
} // namespace Hexagon


