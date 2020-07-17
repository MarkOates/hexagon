#pragma once


#include <Hexagon/Packet.hpp>


namespace Hexagon
{
   class PacketRenderer
   {
   private:
      Hexagon::Packet* packet;

   public:
      PacketRenderer(Hexagon::Packet* packet=nullptr);
      ~PacketRenderer();


   void render();
   };
}



