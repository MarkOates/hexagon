#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   class ProjectNavigator : public StageInterface
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Hexagon::System::Config* config;
      Hexagon::Elements::ListMenu main_menu;
      int surface_width;
      int surface_height;
      bool initialized;
      static ALLEGRO_EVENT a_default_empty_event;

   public:
      ProjectNavigator(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::System::Config* config=nullptr);
      virtual ~ProjectNavigator();

      bool get_initialized();
      static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void initialize();
      virtual void render() override;
      bool main_menu_cursor_move_up();
      bool main_menu_cursor_move_down();
      std::string main_menu_get_current_list_item_identifier();
      void __draw_hexagon_logo_and_wait_for_keypress();
      void draw_menu();
      void render_profiler_graph(AllegroFlare::Profiler* profiler=nullptr, ALLEGRO_FONT* font=nullptr);
      std::string build_allegro_version_string();
      void append_project_path_to_config_file_and_reload_injected_config();
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
   };
}



