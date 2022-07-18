#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu=nullptr);
         ~Renderer();

         void render();
         void render_page();
         void render_menu_page(Hexagon::MultiplexMenu::MultiplexMenuPage menu_page={});
         void render_menu_item(float x=0, float y=0, std::string input="^H", std::string label="Unlabeled", bool opens_menu=false, std::string state="no_state");
         static std::string convert_key_input_to_string(int al_keycode=0, bool ctrl=false, bool alt=false, bool command=false, bool shift=false);
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_keyboard_key_font();
      };
   }
}



