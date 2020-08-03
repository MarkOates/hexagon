

#include <Hexagon/Elements/QuoteRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


QuoteRenderer::QuoteRenderer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


QuoteRenderer::~QuoteRenderer()
{
}


void QuoteRenderer::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "QuoteRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "QuoteRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
return;

}

ALLEGRO_FONT* QuoteRenderer::obtain_quote_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "QuoteRenderer" << "::" << "obtain_quote_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Purista Medium.otf -32");

}
} // namespace Elements
} // namespace Hexagon


