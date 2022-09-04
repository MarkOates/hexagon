

#include <Hexagon/BuildSystem/BuildFactory.hpp>

#include <Hexagon/BuildSystem/BuildStageFactory.hpp>
#include <sstream>


namespace Hexagon
{
namespace BuildSystem
{


BuildFactory::BuildFactory()
   : build_stage_factory({})
{
}


BuildFactory::~BuildFactory()
{
}


Hexagon::BuildSystem::Builds::Base* BuildFactory::create_placeholder_build()
{
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(),
      build_stage_factory.create_shell_command_build_stage("echo \"Having a good day?\""),
   });
   return build;
}

Hexagon::BuildSystem::Builds::Base* BuildFactory::create_shell_command_build(std::string shell_command)
{
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(shell_command),
   });
   return build;
}


} // namespace BuildSystem
} // namespace Hexagon


