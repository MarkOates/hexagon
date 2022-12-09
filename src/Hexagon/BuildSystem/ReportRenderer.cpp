

#include <Hexagon/BuildSystem/ReportRenderer.hpp>

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace BuildSystem
{


ReportRenderer::ReportRenderer(Hexagon::BuildSystem::Builds::Base* build)
   : build(build)
{
}


ReportRenderer::~ReportRenderer()
{
}


void ReportRenderer::set_build(Hexagon::BuildSystem::Builds::Base* build)
{
   this->build = build;
}


Hexagon::BuildSystem::Builds::Base* ReportRenderer::get_build() const
{
   return build;
}


std::string ReportRenderer::build_text_report()
{
   if (!(build))
   {
      std::stringstream error_message;
      error_message << "[ReportRenderer::build_text_report]: error: guard \"build\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReportRenderer::build_text_report: error: guard \"build\" not met");
   }
   std::string result;

   if (build->is_type(Hexagon::BuildSystem::Builds::Base::TYPE))
   {
      Hexagon::BuildSystem::ReportRenderers::Base base_report_renderer;
      base_report_renderer.set_build(build);

      result = base_report_renderer.render_text();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Hexagon::BuildSystem::ReportRenderer::build_report error: "
                    << "Cannot build_report() on a report that is of unknown type \"" << build->get_type() << "\".";
      throw std::runtime_error(error_message.str());
   }

   return result;
}


} // namespace BuildSystem
} // namespace Hexagon


