

#include <Hexagon/BuildSystem/ReportRenderer.hpp>
#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace BuildSystem
{


ReportRenderer::ReportRenderer(Hexagon::BuildSystem::Builds::Base* report)
   : report(report)
{
}


ReportRenderer::~ReportRenderer()
{
}


void ReportRenderer::set_report(Hexagon::BuildSystem::Builds::Base* report)
{
   this->report = report;
}


Hexagon::BuildSystem::Builds::Base* ReportRenderer::get_report() const
{
   return report;
}


std::string ReportRenderer::build_report()
{
   if (!(report))
      {
         std::stringstream error_message;
         error_message << "ReportRenderer" << "::" << "build_report" << ": error: " << "guard \"report\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string result;

   if (report->is_type(Hexagon::BuildSystem::Builds::Base::TYPE))
   {
      Hexagon::BuildSystem::ReportRenderers::Base base_report_renderer;
      result = base_report_renderer.render();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Hexagon::BuildSystem::ReportRenderer::build_report error: "
                    << "Cannot build_report() on a report that is of unknown type \"" << report->get_type() << "\".";
      throw std::runtime_error(error_message.str());
   }

   return result;
}
} // namespace BuildSystem
} // namespace Hexagon


