

#include <Hexagon/PacketRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


PacketRenderer::PacketRenderer(Hexagon::Packet* packet)
   : packet(packet)
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
return;

}
} // namespace Hexagon


