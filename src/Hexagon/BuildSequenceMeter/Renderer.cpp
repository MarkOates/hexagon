

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
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
al_draw_filled_rectangle(0, 0, 100, 100, ALLEGRO_COLOR{1, 1, 1, 1});
return;

}
} // namespace BuildSequenceMeter
} // namespace Hexagon


