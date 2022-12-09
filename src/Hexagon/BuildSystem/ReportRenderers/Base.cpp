

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>

#include <Hexagon/BuildSystem/BuildStageRenderer.hpp>
#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <Hexagon/Errors.hpp>
#include <iostream>
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
      error_message << "[Base::render_text]: error: guard \"build\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::render_text: error: guard \"build\" not met");
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
      result << "  - Status: " << colorize_status(build_stage->get_status()) << std::endl;
      result << "  - Duration: " << build_stage->calc_duration_seconds() << " seconds" << std::endl;
      if (!build_stage_render.empty()) result << build_stage_render;
      result << std::endl;
   }
   result << "[===== Duration: " << build->infer_duration_seconds() << " seconds =======]" << std::endl;

   return result.str();
}

std::string Base::colorize_status(std::string status)
{
   const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   const std::string CONSOLE_COLOR_YELLOW = "\033[1;33m";
   const std::string CONSOLE_COLOR_GREEN = "\033[1;32m";
   const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   const std::string CONSOLE_COLOR_CYAN = "\033[1;36m";

   std::string color;

   if (status == Hexagon::BuildSystem::BuildStages::Base::STATUS_WAITING_TO_START) { color = CONSOLE_COLOR_CYAN; }
   else if (status == Hexagon::BuildSystem::BuildStages::Base::STATUS_RUNNING) { color = CONSOLE_COLOR_YELLOW; }
   else if (status == Hexagon::BuildSystem::BuildStages::Base::STATUS_SUCCEEDED) { color = CONSOLE_COLOR_GREEN; }
   else if (status == Hexagon::BuildSystem::BuildStages::Base::STATUS_ERROR) { color = CONSOLE_COLOR_RED; }
   else if (status == Hexagon::BuildSystem::BuildStages::Base::STATUS_FAILED) { color = CONSOLE_COLOR_RED; }
   else
   {
      throw std::runtime_error(Hexagon::Errors::build_error_message(
            "Hexagon::BuildSystem::ReportRenderers::Base::colorize_status()",
            "Unaccounted for status type"
         )
      );
   }

   return color + status + CONSOLE_COLOR_DEFAULT;
}


} // namespace ReportRenderers
} // namespace BuildSystem
} // namespace Hexagon


