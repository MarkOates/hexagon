#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>


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
         void render_page(Hexagon::MultiplexMenu::MultiplexMenuPage* page=nullptr);
      };
   }
}



