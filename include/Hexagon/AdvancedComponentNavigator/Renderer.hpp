#pragma once


#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class Renderer
      {
      private:
         Hexagon::AdvancedComponentNavigator::Stage* stage;
         bool is_focused;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR frame_color;

      public:
         Renderer(Hexagon::AdvancedComponentNavigator::Stage* stage=nullptr, bool is_focused=true, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
         ~Renderer();


      ALLEGRO_COLOR build_not_quite_black_color();
      void render();
      void draw_search_text_box();
      void render_raw();
      };
   }
}



