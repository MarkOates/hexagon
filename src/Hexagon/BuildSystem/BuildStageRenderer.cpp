

#include <Hexagon/BuildSystem/BuildStageRenderer.hpp>
#include <Hexagon/BuildSystem/BuildStageRenderers/Base.hpp>
#include <Hexagon/BuildSystem/BuildStageRenderers/ShellCommand.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace BuildSystem
{


BuildStageRenderer::BuildStageRenderer(Hexagon::BuildSystem::BuildStages::Base* build_stage)
   : build_stage(build_stage)
{
}


BuildStageRenderer::~BuildStageRenderer()
{
}


void BuildStageRenderer::set_build_stage(Hexagon::BuildSystem::BuildStages::Base* build_stage)
{
   this->build_stage = build_stage;
}


Hexagon::BuildSystem::BuildStages::Base* BuildStageRenderer::get_build_stage() const
{
   return build_stage;
}


std::string BuildStageRenderer::build_text_report()
{
   if (!(build_stage))
   {
      std::stringstream error_message;
      error_message << "BuildStageRenderer" << "::" << "build_text_report" << ": error: " << "guard \"build_stage\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::string result;

   if (build_stage->is_type(Hexagon::BuildSystem::BuildStages::Base::TYPE))
   {
     // do nothing for this case
   }
   else if (build_stage->is_type(Hexagon::BuildSystem::BuildStages::ShellCommand::TYPE))
   {
      Hexagon::BuildSystem::BuildStages::ShellCommand* typed_build_stage =
         dynamic_cast<Hexagon::BuildSystem::BuildStages::ShellCommand*>(build_stage);

      Hexagon::BuildSystem::BuildStageRenderers::ShellCommand renderer;
      renderer.set_shell_command_build_stage(typed_build_stage);

      result = renderer.render_text();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Hexagon::BuildSystem::BuildStageRenderer::build_text_report() error: "
                    << "Cannot build_text_report() on a report that is of unknown type \""
                    << build_stage->get_type() << "\".";
      throw std::runtime_error(error_message.str());
   }

   return result;
}
} // namespace BuildSystem
} // namespace Hexagon


