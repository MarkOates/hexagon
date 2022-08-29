

#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


ShellCommand::ShellCommand(std::string shell_command)
   : Hexagon::BuildSystem::BuildStages::Base("ShellCommand")
   , shell_command(shell_command)
   , shell_command_result("")
   , executed(false)
{
}


ShellCommand::~ShellCommand()
{
}


std::string ShellCommand::get_shell_command() const
{
   return shell_command;
}


std::string ShellCommand::get_shell_command_result() const
{
   return shell_command_result;
}


void ShellCommand::execute_raw()
{
   if (!((!executed)))
      {
         std::stringstream error_message;
         error_message << "ShellCommand" << "::" << "execute_raw" << ": error: " << "guard \"(!executed)\" not met";
         throw std::runtime_error(error_message.str());
      }
   Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command);
   shell_command_result = shell_command_executor.execute();
   executed = true;
   return;
}
} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


