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
         float page_width;
         void render_page(Hexagon::MultiplexMenu::MultiplexMenuPage* page=nullptr, bool is_active=false);

      protected:


      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu=nullptr, float page_width=400);
         ~Renderer();

         void render();
         float get_width();
      };
   }
}



