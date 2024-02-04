#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class ProjectFoldersView : public StageInterface
   {
   private:
      AllegroFlare::FontBin* font_bin;
      Hexagon::System::Config* config;
      std::vector<std::tuple<std::string, std::string>> menu_items;
      Hexagon::Elements::ListMenu main_menu;
      int surface_width;
      int surface_height;
      static ALLEGRO_EVENT a_default_empty_event;
      bool initialized;
      void draw_frame();

   protected:


   public:
      ProjectFoldersView(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::System::Config* config=nullptr, std::vector<std::tuple<std::string, std::string>> menu_items={});
      virtual ~ProjectFoldersView();

      std::vector<std::tuple<std::string, std::string>> get_menu_items() const;
      static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void set_menu_items(std::vector<std::tuple<std::string, std::string>> menu_items={});
      bool initialize();
      virtual void render() override;
      bool main_menu_cursor_move_up();
      bool main_menu_cursor_move_down();
      std::string main_menu_get_current_list_item_identifier();
      void draw_menu();
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      static std::vector<std::tuple<std::string, std::string>> build_placeholder_menu_items();
   };
}



