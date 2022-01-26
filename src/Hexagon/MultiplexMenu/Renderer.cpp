

#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
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
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   render_menu_item();
   return;
}

void Renderer::render_menu_item(float x, float y, std::string input, std::string label)
{
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.8};
   float frame_opacity = 0.4f;
   ALLEGRO_COLOR frame_color = AllegroFlare::color::color(al_color_name("dodgerblue"), frame_opacity);
   float text_opacity = 0.6f;
   ALLEGRO_COLOR text_color = AllegroFlare::color::color(al_color_name("white"), text_opacity);
   ALLEGRO_FONT *font = obtain_font();
   float padding_x = 20;
   float padding_y = 12;
   float input_text_length = al_get_text_width(font, input.c_str());
   float label_text_length = al_get_text_width(font, label.c_str());
   float roundness = 6.0;
   float height = al_get_font_line_height(font) + padding_y * 2;
   float width = label_text_length + input_text_length + padding_x * 4;
   float frame_thickness = 2.0;

   al_draw_filled_rounded_rectangle(x, y, width, height, roundness, roundness, backfill_color);
   al_draw_text(font, text_color, x+padding_x, y+padding_y, ALLEGRO_ALIGN_LEFT, input.c_str());
   al_draw_text(font, text_color, x+padding_x + input_text_length + 20, y+padding_y, ALLEGRO_ALIGN_LEFT, label.c_str());
   al_draw_rounded_rectangle(
      x+frame_thickness*2,
      y+frame_thickness*2,
      width-frame_thickness*2,
      height-frame_thickness*2,
      roundness,
      roundness,
      frame_color,
      frame_thickness
   );

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
   return font_bin->auto_get("Purista Medium.otf -38");
}
} // namespace MultiplexMenu
} // namespace Hexagon


