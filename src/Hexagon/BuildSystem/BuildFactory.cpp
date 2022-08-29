

#include <Hexagon/BuildSystem/BuildFactory.hpp>
#include <Hexagon/BuildSystem/BuildStageFactory.hpp>


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
      build_stage_factory.create_shell_command_build_stage(),
   });
   return build;
}
} // namespace BuildSystem
} // namespace Hexagon


