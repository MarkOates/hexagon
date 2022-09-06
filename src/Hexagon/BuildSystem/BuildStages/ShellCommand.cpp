

#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


ShellCommand::ShellCommand(std::string shell_command)
   : Hexagon::BuildSystem::BuildStages::Base(Hexagon::BuildSystem::BuildStages::ShellCommand::TYPE)
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


bool ShellCommand::execute()
{
   if (!((!executed)))
   {
      std::stringstream error_message;
      error_message << "ShellCommand" << "::" << "execute" << ": error: " << "guard \"(!executed)\" not met";
      throw std::runtime_error(error_message.str());
   }
   Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command);
   shell_command_result = shell_command_executor.execute();
   executed = true;
   return true;
}


} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


