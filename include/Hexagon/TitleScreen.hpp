#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   class TitleScreen
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Hexagon::System::Config* config;
      Hexagon::Elements::ListMenu main_menu;
      int surface_width;
      int surface_height;
      bool initialized;

   protected:


   public:
      TitleScreen(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::System::Config* config=nullptr);
      ~TitleScreen();

      bool get_initialized() const;
      void initialize();
      bool main_menu_cursor_move_up();
      bool main_menu_cursor_move_down();
      std::string main_menu_get_current_list_item_identifier();
      void draw_hexagon_logo_and_wait_for_keypress();
      void draw_menu();
      void render_profiler_graph(AllegroFlare::Profiler* profiler=nullptr, ALLEGRO_FONT* font=nullptr);
      std::string build_allegro_version_string();
      void append_project_path_to_config_file_and_reload_injected_config();
   };
}



