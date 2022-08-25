#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class PageRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         Hexagon::MultiplexMenu::MultiplexMenuPage* page;
         bool is_active;
         int width;
         int height;
         float padding;

      public:
         PageRenderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::MultiplexMenu::MultiplexMenuPage* page=nullptr, bool is_active=false, int width=320, int height=400);
         ~PageRenderer();

         float get_padding() const;
         void render();
         void render_menu_item(float x=0, float y=0, std::string input="[no-input-defined]", std::string label="Unlabeled", bool opens_menu=false, std::string state="no_state");
         static std::string convert_key_input_to_string(int al_keycode=0, bool ctrl=false, bool alt=false, bool command=false, bool shift=false);
         void render_frame();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_keyboard_key_font();
      };
   }
}



