

#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
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
      error_message << "[Hexagon::BuildSystem::BuildStages::ShellCommand::execute]: error: guard \"(!executed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::BuildSystem::BuildStages::ShellCommand::execute]: error: guard \"(!executed)\" not met");
   }
   Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command);
   shell_command_result = shell_command_executor.execute();
   executed = true;
   return true;
}


} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


