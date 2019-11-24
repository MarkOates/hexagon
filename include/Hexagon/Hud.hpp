#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class Hud
   {
   private:
      ALLEGRO_FONT* text_font;
      ALLEGRO_BITMAP* screen_sub_bitmap;
      std::vector<std::string> notifications;

   public:
      Hud();
      ~Hud();

      void set_text_font(ALLEGRO_FONT* text_font);
      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);

      std::vector<std::string> get_notifications();
   void initialize();
   void draw();
   };
}



