

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
window.draw();
return;

}
} // namespace Hexagon


