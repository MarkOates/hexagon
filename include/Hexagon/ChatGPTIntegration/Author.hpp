#pragma once


#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      class Author
      {
      private:
         uint32_t id;
         std::string identifier;
         std::string display_name;
         std::string avatar_bitmap_identifier;
         ALLEGRO_COLOR display_background_color;

      protected:


      public:
         Author(uint32_t id=0, std::string identifier="[unset-identifier]", std::string display_name="[unset-name]", std::string avatar_bitmap_identifier="[unset-avatar_bitmap_identifier]", ALLEGRO_COLOR display_background_color=ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.0});
         ~Author();

         void set_id(uint32_t id);
         void set_identifier(std::string identifier);
         void set_display_name(std::string display_name);
         void set_avatar_bitmap_identifier(std::string avatar_bitmap_identifier);
         void set_display_background_color(ALLEGRO_COLOR display_background_color);
         uint32_t get_id() const;
         std::string get_identifier() const;
         std::string get_display_name() const;
         std::string get_avatar_bitmap_identifier() const;
         ALLEGRO_COLOR get_display_background_color() const;
      };
   }
}



