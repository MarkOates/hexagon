

#include <Hexagon/ChatGPTIntegration/SubmitTTYMessageToChat.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <sstream>


namespace Hexagon
{
namespace ChatGPTIntegration
{


SubmitTTYMessageToChat::SubmitTTYMessageToChat()
   : tty_location("[unset-tty_location]")
   , message("[unset-message]")
   , shell_command_output("[unset-shell_command_output]")
   , output_command_to_cout(true)
{
}


SubmitTTYMessageToChat::~SubmitTTYMessageToChat()
{
}


void SubmitTTYMessageToChat::set_shell_command_output(std::string shell_command_output)
{
   this->shell_command_output = shell_command_output;
}


void SubmitTTYMessageToChat::set_output_command_to_cout(bool output_command_to_cout)
{
   this->output_command_to_cout = output_command_to_cout;
}


std::string SubmitTTYMessageToChat::get_shell_command_output() const
{
   return shell_command_output;
}


bool SubmitTTYMessageToChat::get_output_command_to_cout() const
{
   return output_command_to_cout;
}


std::string SubmitTTYMessageToChat::submit()
{
   std::string command_program = "/Users/markoates/Repos/ChatGPT/bin/programs/writevt";
   std::stringstream command;
   std::string message_unescaped = message;
   command << command_program << " " << tty_location << " \"" << message_unescaped << "\\r\\r\"";

   // NOTE! this assumes the command is safe. It is currently not escaped
   if (output_command_to_cout)
   {
      std::cout << std::endl << "========= outputting command begin: =======" << std::endl;
      std::cout << command.str();
      std::cout << std::endl << "========= :outputting command end =======" << std::endl;
   }

   Blast::ShellCommandExecutorWithCallback shell_command_executor_with_callback(command.str());

   //shell_command_output = shell_command_executor_with_callback(
   return shell_command_output;
}


} // namespace ChatGPTIntegration
} // namespace Hexagon


