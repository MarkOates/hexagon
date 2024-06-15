

#include <Hexagon/Elements/ComponentTitleSlate.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[Hexagon::Elements::ComponentTitleSlate::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::ComponentTitleSlate::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::ComponentTitleSlate::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::ComponentTitleSlate::render]: error: guard \"al_is_font_addon_initialized()\" not met");
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
      error_message << "[Hexagon::Elements::ComponentTitleSlate::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::ComponentTitleSlate::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Purista Medium.otf -84");
}


} // namespace Elements
} // namespace Hexagon


