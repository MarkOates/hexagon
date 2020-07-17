

#include <Hexagon/PacketRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/Elements/Window.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>


namespace Hexagon
{


PacketRenderer::PacketRenderer(Hexagon::Packet* packet, ALLEGRO_FONT* font, float width, float height)
   : packet(packet)
   , font(font)
   , width(width)
   , height(height)
{
}


PacketRenderer::~PacketRenderer()
{
}


void PacketRenderer::render()
{
if (!(packet))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"packet\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
render_window();

ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};
int line_height = al_get_font_line_height(font) * 2;
al_draw_textf(font, text_color, 20, 20, ALLEGRO_ALIGN_LEFT, "Searches: %d", packet->get_searches_count());
al_draw_textf(font, text_color, 20, 20 + line_height, ALLEGRO_ALIGN_LEFT, "Saves: %d", packet->get_saves_count());

return;

}

void PacketRenderer::render_window()
{
Hexagon::Elements::Window window(width, height);

window.set_box_fill_color(ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 1.0f});
window.set_box_opacity(0.1);
window.set_cell_padding(10);

window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
window.set_outer_line_opacity(0.2);
window.set_outer_line_thickness(2.0);

window.draw();
return;

}
} // namespace Hexagon


