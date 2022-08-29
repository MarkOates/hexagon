

#include <Hexagon/BuildSystem/BuildStageFactory.hpp>



namespace Hexagon
{
namespace BuildSystem
{


BuildStageFactory::BuildStageFactory()
{
}


BuildStageFactory::~BuildStageFactory()
{
}


Hexagon::BuildSystem::BuildStages::ShellCommand* BuildStageFactory::create_shell_command_build_stage(std::string shell_command)
{
   //std::string shell_command = "echo \"Hi friend\"";
   Hexagon::BuildSystem::BuildStages::ShellCommand* build_stage =
      new Hexagon::BuildSystem::BuildStages::ShellCommand(shell_command);
   return build_stage;
}
} // namespace BuildSystem
} // namespace Hexagon


