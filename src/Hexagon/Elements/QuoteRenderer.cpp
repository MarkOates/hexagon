

#include <Hexagon/Elements/QuoteRenderer.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


QuoteRenderer::QuoteRenderer(AllegroFlare::FontBin* font_bin, std::string quote)
   : font_bin(font_bin)
   , font({font_bin})
   , quote(quote)
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
font.set_font_size(-60);
al_draw_text(font.al_font(), ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, 0, "Hello QuoteRenderer");
return;

}
} // namespace Elements
} // namespace Hexagon


