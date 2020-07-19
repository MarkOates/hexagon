#pragma once


#include <Hexagon/Packet.hpp>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace Elements
   {
      class DataTable
      {
      private:
         Hexagon::Packet* packet;
         ALLEGRO_FONT* font;
         float width;
         float height;

      public:
         DataTable(Hexagon::Packet* packet=nullptr, ALLEGRO_FONT* font=nullptr, float width=1.0, float height=1.0);
         ~DataTable();


      void render();
      void render_text();
      };
   }
}



