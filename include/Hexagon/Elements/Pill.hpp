#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class Pill
      {
      private:
         AllegroFlare::FontBin* font_bin;
         float x;
         float y;
         float width;
         float height;
         std::string label;
         ALLEGRO_COLOR color;
         ALLEGRO_COLOR font_color;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Pill(AllegroFlare::FontBin* font_bin=nullptr, float x=0, float y=0, float width=120, float height=31, std::string label="label-not-set", ALLEGRO_COLOR color=ALLEGRO_COLOR{0.1, 0.3, 0.1, 0.3}, ALLEGRO_COLOR font_color=ALLEGRO_COLOR{0, 0, 0, 1.0});
         ~Pill();

         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         void set_label(std::string label);
         void set_color(ALLEGRO_COLOR color);
         void set_font_color(ALLEGRO_COLOR font_color);
         float get_x() const;
         float get_y() const;
         float get_width() const;
         float get_height() const;
         std::string get_label() const;
         ALLEGRO_COLOR get_color() const;
         ALLEGRO_COLOR get_font_color() const;
         void render();
      };
   }
}



