

#include <Hexagon/BuildSystem/BuildStageRenderers/ShellCommand.hpp>
#include <sstream>


namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStageRenderers
{


ShellCommand::ShellCommand(Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage)
   : Hexagon::BuildSystem::BuildStageRenderers::Base(Hexagon::BuildSystem::BuildStageRenderers::ShellCommand::TYPE)
   , shell_command_build_stage(shell_command_build_stage)
{
}


ShellCommand::~ShellCommand()
{
}


void ShellCommand::set_shell_command_build_stage(Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage)
{
   this->shell_command_build_stage = shell_command_build_stage;
}


std::string ShellCommand::render_text()
{
   std::stringstream result;
   result << "  - Command: " << shell_command_build_stage->get_shell_command() << std::endl;
   return result.str();
}
} // namespace BuildStageRenderers
} // namespace BuildSystem
} // namespace Hexagon


