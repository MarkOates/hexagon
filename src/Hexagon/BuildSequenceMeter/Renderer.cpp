

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace BuildSequenceMeter
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , status("not_started")
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
   // steps:
   //   parsing_yaml
   //   making_component_object_files
   //   component_build_is_successful
      //   check_missing_symbol_errors_in_program_files_build

   //   make_focused_component_test
   //   run_focused_component_test
      //   check_missing_symbol_errors_in_program_files_build

   //   build_program_files
   //   build_is_successful

   // missing step - defaults change in header file(s)

   render_rectangle();

   //build_not_started
   //build_running
   //build_completed_failed
   //build_completed_successfully

   return;
}

void Renderer::render_rectangle(std::string status)
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render_rectangle" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render_rectangle" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render_rectangle" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render_rectangle" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   // statuses:
   //   incomplete: nothing has run yet
   //   running: current step is being executed and will show results once processed
   //   failed: current step failed
   //   succeeded: current step succeeded

   al_draw_filled_rectangle(0, 0, 100, 100, ALLEGRO_COLOR{1, 1, 1, 1});
   return;
}
} // namespace BuildSequenceMeter
} // namespace Hexagon


