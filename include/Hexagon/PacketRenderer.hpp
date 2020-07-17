#pragma once


#include <Hexagon/Packet.hpp>


namespace Hexagon
{
   class PacketRenderer
   {
   private:
      Hexagon::Packet* packet;
      float width;
      float height;

   public:
      PacketRenderer(Hexagon::Packet* packet=nullptr, float width=1.0, float height=1.0);
      ~PacketRenderer();


   void render();
   };
}



