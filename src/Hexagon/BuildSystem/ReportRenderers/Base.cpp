

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>

#include <Hexagon/BuildSystem/BuildStageRenderer.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace BuildSystem
{
namespace ReportRenderers
{


Base::Base(std::string type)
   : type(type)
   , build(nullptr)
{
}


Base::~Base()
{
}


void Base::set_build(Hexagon::BuildSystem::Builds::Base* build)
{
   this->build = build;
}


std::string Base::get_type() const
{
   return type;
}


Hexagon::BuildSystem::Builds::Base* Base::get_build() const
{
   return build;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

std::string Base::render_text()
{
   if (!(build))
   {
      std::stringstream error_message;
      error_message << "Base" << "::" << "render_text" << ": error: " << "guard \"build\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::stringstream result;

   unsigned i=0;

   result << "[========= BUILD =========]" << std::endl;
   result << std::endl;
   for (auto &build_stage : build->get_build_stages())
   {
      Hexagon::BuildSystem::BuildStageRenderer build_stage_renderer;
      build_stage_renderer.set_build_stage(build_stage);
      std::string build_stage_render = build_stage_renderer.build_text_report();

      i++;
      result << "[#=------ STAGE " << i << " ------=#]" << std::endl;
      result << "  - Type: " << build_stage->get_type() << std::endl;
      result << "  - Status: " << build_stage->get_status() << std::endl;
      result << "  - Duration: " << build_stage->calc_duration_seconds() << " seconds" << std::endl;
      if (!build_stage_render.empty()) result << build_stage_render;
      result << std::endl;
   }
   result << "[=========================]" << std::endl;

   return result.str();
}


} // namespace ReportRenderers
} // namespace BuildSystem
} // namespace Hexagon


