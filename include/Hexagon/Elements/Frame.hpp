#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_color.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class Frame
      {
      private:
         static AllegroFlare::FontBin dummy_font_bin;
         AllegroFlare::FontBin& fonts;
         std::string title_text;
         float width;
         float height;
         ALLEGRO_COLOR outline_color;

      public:
         Frame(float width=1.0f, float height=1.0f);
         ~Frame();

         void set_title_text(std::string title_text);
         void set_width(float width);
         void set_height(float height);
         void set_outline_color(ALLEGRO_COLOR outline_color);

         ALLEGRO_COLOR get_outline_color();
      static ALLEGRO_COLOR build_default_frame_color();
      static AllegroFlare::FontBin& get_dummy_font_bin();
      void render();
      };
   }
}



