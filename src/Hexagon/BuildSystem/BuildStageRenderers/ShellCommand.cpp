

#include <Hexagon/BuildSystem/BuildStageRenderers/ShellCommand.hpp>



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


} // namespace BuildStageRenderers
} // namespace BuildSystem
} // namespace Hexagon


