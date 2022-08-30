

#include <Hexagon/Elements/QuoteRenderer.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


QuoteRenderer::QuoteRenderer(AllegroFlare::FontBin* font_bin, std::string quote, std::string speaker)
   : font_bin(font_bin)
   , font({font_bin, "consolas.ttf", -24})
   , quote(quote)
   , speaker(speaker)
{
}


QuoteRenderer::~QuoteRenderer()
{
}


bool QuoteRenderer::incrementer(int line_num, char* line__WAS_CONST_CHAR, int size, void* extra)
{
   (*static_cast<int*>(extra))++;
   return true;
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
   float x = 0;
   float y = 0;
   ALLEGRO_FONT *al_font = font.al_font();
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 1, 1, 1};
   std::string text = quote;
   float max_width = 600;
   float line_height = al_get_font_line_height(al_font);

   al_draw_multiline_text(
      al_font,
      color,
      x,
      y,
      max_width,
      line_height,
      0,
      text.c_str()
   );

   int line_count = 0;

   // TODO: this feature is currently not implemented because it requires a type (const char) that is not
   // available in quintessence extrapolation at this time.

   // TODO: this feature is currently not implemented because it requires a type (const char) that is not
   // available in quintessence extrapolation at this time.

   // THIS call was disabled:
   //al_do_multiline_text(
      //al_font,
      //max_width,
      //text.c_str(),
      //&Hexagon::Elements::QuoteRenderer::incrementer,
      //static_cast<void*>(&line_count)
   //);

   al_draw_text(al_font, color, 0, line_height * (line_count + 1), 0, (std::string("- ") + speaker).c_str());

   return;
}
} // namespace Elements
} // namespace Hexagon


