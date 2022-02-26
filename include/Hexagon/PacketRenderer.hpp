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
      ALLEGRO_COLOR text_color;

   public:
      PacketRenderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::Packet* packet=nullptr, ALLEGRO_FONT* font=nullptr, float width=1.0, float height=1.0, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
      ~PacketRenderer();

      void set_text_color(ALLEGRO_COLOR text_color);
      ALLEGRO_COLOR get_text_color();
      void render();
      ALLEGRO_COLOR box_fill_color();
      float box_fill_opacity();
      ALLEGRO_COLOR box_outline_color();
      float box_outline_opacity();
      ALLEGRO_COLOR color_good();
      ALLEGRO_COLOR color_failure();
      ALLEGRO_COLOR color_approaching_failure();
      ALLEGRO_COLOR color_warning();
      ALLEGRO_COLOR color_neutral();
      void render_window();
      void render_text();
      ALLEGRO_COLOR generate_top_left_little_bar_color();
      ALLEGRO_FONT* obtain_table_text_font();
   };
}



