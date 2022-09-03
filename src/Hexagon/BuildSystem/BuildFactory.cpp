

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

Hexagon::BuildSystem::Builds::Base* BuildFactory::create_make_quintessence_build(std::string project_directory)
{
   std::stringstream build_stage_shell_command;
   build_stage_shell_command << "(cd " << project_directory << " && make quintessence)";

   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(build_stage_shell_command.str()),
   });
   return build;
}


} // namespace BuildSystem
} // namespace Hexagon


