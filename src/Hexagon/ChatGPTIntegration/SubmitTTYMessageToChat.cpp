

#include <Hexagon/ChatGPTIntegration/SubmitTTYMessageToChat.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <sstream>


namespace Hexagon
{
namespace ChatGPTIntegration
{


SubmitTTYMessageToChat::SubmitTTYMessageToChat(std::string tty_location, std::string message)
   : tty_location(tty_location)
   , message(message)
   , shell_command_output("[unset-shell_command_output]")
   , output_command_to_cout(true)
{
}


SubmitTTYMessageToChat::~SubmitTTYMessageToChat()
{
}


void SubmitTTYMessageToChat::set_tty_location(std::string tty_location)
{
   this->tty_location = tty_location;
}


void SubmitTTYMessageToChat::set_message(std::string message)
{
   this->message = message;
}


void SubmitTTYMessageToChat::set_shell_command_output(std::string shell_command_output)
{
   this->shell_command_output = shell_command_output;
}


void SubmitTTYMessageToChat::set_output_command_to_cout(bool output_command_to_cout)
{
   this->output_command_to_cout = output_command_to_cout;
}


std::string SubmitTTYMessageToChat::get_tty_location() const
{
   return tty_location;
}


std::string SubmitTTYMessageToChat::get_message() const
{
   return message;
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
   // TODO: Add guards to ensure this program is present, is compiled, and has the proper permissions:
   std::string command_program = "/Users/markoates/Repos/ChatGPT/bin/programs/writevt";
   std::stringstream command;
   std::string message_unescaped = message;
   // command << command_program << " " << tty_location << " '" << message_unescaped << "\0x0D\0x0D'";
   command << command_program << " " << tty_location << " \"" << message_unescaped << "\\n\\n\"";

   // NOTE! this assumes the command is safe. It is currently not escaped
   if (output_command_to_cout)
   {
      std::cout << std::endl << "========= outputting command begin: =======" << std::endl;
      std::cout << command.str();
      std::cout << std::endl << "========= :outputting command end =======" << std::endl;
   }

   Blast::ShellCommandExecutorWithCallback shell_command_executor_with_callback(command.str());
   shell_command_output = shell_command_executor_with_callback.execute();


   // In order to submit the command, we will need to submit the ENTER key.  There are some complexities with the
   // character, so a script has been created that can "press" the ENTER key.
   // The program expects the enter key to be pressed twice, so, the script is run twice here:

   std::string script_to_send_enter_key = "/Users/markoates/Repos/ChatGPT/scripts/subit_enter_to_tty.sh";
   Blast::ShellCommandExecutorWithCallback submit_enter_key_command(script_to_send_enter_key);
   // Unused variable:
   std::string enter_key_command_output_1 = submit_enter_key_command.execute();
   std::string enter_key_command_output_2 = submit_enter_key_command.execute();

   return shell_command_output;
}


} // namespace ChatGPTIntegration
} // namespace Hexagon


