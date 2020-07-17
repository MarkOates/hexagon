

#include <Hexagon/PacketRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/Elements/Window.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


PacketRenderer::PacketRenderer(Hexagon::Packet* packet, float width, float height)
   : packet(packet)
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
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "PacketRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
al_draw_filled_rectangle(0, 0, width, height, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2});
Hexagon::Elements::Window window(width, height);

window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
window.set_outer_line_opacity(0.2);
window.set_outer_line_thickness(4.0);

window.draw();
return;

}
} // namespace Hexagon


