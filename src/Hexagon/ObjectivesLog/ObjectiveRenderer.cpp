

#include <Hexagon/ObjectivesLog/ObjectiveRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace ObjectivesLog
{


ObjectiveRenderer::ObjectiveRenderer(AllegroFlare::FontBin* font_bin, Hexagon::ObjectivesLog::Objective* objective)
   : font_bin(font_bin)
   , objective(objective)
{
}


ObjectiveRenderer::~ObjectiveRenderer()
{
}


void ObjectiveRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(objective))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "render" << ": error: " << "guard \"objective\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

ALLEGRO_FONT* ObjectiveRenderer::obtain_quote_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ObjectiveRenderer" << "::" << "obtain_quote_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace ObjectivesLog
} // namespace Hexagon


