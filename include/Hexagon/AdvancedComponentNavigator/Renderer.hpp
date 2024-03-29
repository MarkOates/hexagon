#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class Renderer
      {
      private:
         Hexagon::AdvancedComponentNavigator::Stage* stage;
         AllegroFlare::FontBin* font_bin;
         bool is_focused;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR base_backfill_color;
         float backfill_opacity;
         ALLEGRO_COLOR base_text_color;
         std::vector<std::string> input_hints_tokens;
         ALLEGRO_COLOR frame_color_bluegreen;
         ALLEGRO_COLOR build_backfill_color();
         void draw_search_text_box();

      protected:


      public:
         Renderer(Hexagon::AdvancedComponentNavigator::Stage* stage=nullptr, AllegroFlare::FontBin* font_bin=nullptr, bool is_focused=true, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20, ALLEGRO_COLOR base_backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f}, float backfill_opacity=0.8f, ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, std::vector<std::string> input_hints_tokens={});
         ~Renderer();

         void set_input_hints_tokens(std::vector<std::string> input_hints_tokens);
         ALLEGRO_COLOR get_base_backfill_color() const;
         ALLEGRO_COLOR get_base_text_color() const;
         std::vector<std::string> get_input_hints_tokens() const;
         void note();
         void draw_input_hints();
         void render();
         void render_raw();
         ALLEGRO_FONT* obtain_title_text_font();
      };
   }
}



