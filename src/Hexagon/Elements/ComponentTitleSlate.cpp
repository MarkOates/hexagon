

#include <Hexagon/Elements/ComponentTitleSlate.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


ComponentTitleSlate::ComponentTitleSlate(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


ComponentTitleSlate::~ComponentTitleSlate()
{
}


void ComponentTitleSlate::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ComponentTitleSlate" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ComponentTitleSlate" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

ALLEGRO_FONT* ComponentTitleSlate::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ComponentTitleSlate" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace Elements
} // namespace Hexagon


