

#include <Hexagon/Elements/ComponentTitleSlate.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


ComponentTitleSlate::ComponentTitleSlate(AllegroFlare::FontBin* font_bin, std::string quote, float width, float height)
   : font_bin(font_bin)
   , quote(quote)
   , width(width)
   , height(height)
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
   ALLEGRO_FONT *font = obtain_font();
   float width = al_get_text_width(font, quote.c_str());
   float height = al_get_font_line_height(font);
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1};
   al_draw_text(font, text_color, 0, -height * 0.5, ALLEGRO_ALIGN_CENTER, quote.c_str());
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
   return font_bin->auto_get("Purista Medium.otf -84");
}
} // namespace Elements
} // namespace Hexagon


