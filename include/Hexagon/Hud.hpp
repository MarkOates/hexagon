#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class Hud
   {
   private:
      bool initialized;
      ALLEGRO_DISPLAY* display;
      static AllegroFlare::FontBin dummy_font_bin;
      AllegroFlare::FontBin& fonts;
      ALLEGRO_BITMAP* screen_sub_bitmap;
      std::vector<std::string> notifications;
      std::vector<std::string> notifications2;

   public:
      Hud(ALLEGRO_DISPLAY* display=nullptr, AllegroFlare::FontBin& fonts=get_dummy_font_bin());
      ~Hud();

      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);
      void set_notifications2(std::vector<std::string> notifications2);

      std::vector<std::string> get_notifications();
      std::vector<std::string> get_notifications2();
   static AllegroFlare::FontBin& get_dummy_font_bin();
   ALLEGRO_FONT* obtain_text_font();
   void initialize();
   void draw();
   };
}



