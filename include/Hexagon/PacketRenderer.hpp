#pragma once


#include <Hexagon/Packet.hpp>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   class PacketRenderer
   {
   private:
      Hexagon::Packet* packet;
      ALLEGRO_FONT* font;
      float width;
      float height;

   public:
      PacketRenderer(Hexagon::Packet* packet=nullptr, ALLEGRO_FONT* font=nullptr, float width=1.0, float height=1.0);
      ~PacketRenderer();


   void render();
   void render_window();
   };
}



