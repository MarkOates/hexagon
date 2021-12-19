#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/Packet.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   class PacketRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Hexagon::Packet* packet;
      ALLEGRO_FONT* font;
      float width;
      float height;

   public:
      PacketRenderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::Packet* packet=nullptr, ALLEGRO_FONT* font=nullptr, float width=1.0, float height=1.0);
      ~PacketRenderer();

      void render();
      void render_window();
      void render_text();
      ALLEGRO_COLOR generate_top_left_little_bar_color();
   };
}



