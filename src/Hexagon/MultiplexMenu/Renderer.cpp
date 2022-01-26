

#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
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
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   render_menu_item();
   return;
}

void Renderer::render_menu_item(float x, float y, std::string label, std::string input)
{
   ALLEGRO_COLOR frame_color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 1.0};
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_FONT *font = obtain_font();
   float input_text_length = al_get_text_width(font, input.c_str());
   float roundness = 6.0;

   al_draw_filled_rounded_rectangle(x, y+3, 200, 43, roundness, roundness, frame_color);
   al_draw_text(font, text_color, x+12, y+3, ALLEGRO_ALIGN_LEFT, input.c_str());
   al_draw_text(font, text_color, x+12 + input_text_length + 20, y+3, ALLEGRO_ALIGN_LEFT, label.c_str());

   return;
}

ALLEGRO_FONT* Renderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace MultiplexMenu
} // namespace Hexagon


