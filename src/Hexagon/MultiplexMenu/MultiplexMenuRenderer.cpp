

#include <Hexagon/MultiplexMenu/MultiplexMenuRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenuRenderer::MultiplexMenuRenderer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


MultiplexMenuRenderer::~MultiplexMenuRenderer()
{
}


void MultiplexMenuRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "MultiplexMenuRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "MultiplexMenuRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

ALLEGRO_FONT* MultiplexMenuRenderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "MultiplexMenuRenderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace MultiplexMenu
} // namespace Hexagon


