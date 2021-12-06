#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace ComponentRelationsNavigator
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         static ALLEGRO_EVENT a_default_empty_event;
         std::vector<std::tuple<std::string, std::string>> dependents_menu_items;
         std::vector<std::tuple<std::string, std::string>> relatives_menu_items;
         std::vector<std::tuple<std::string, std::string>> dependencies_menu_items;
         Hexagon::Elements::ListMenu dependents_menu;
         Hexagon::Elements::ListMenu relatives_menu;
         Hexagon::Elements::ListMenu dependencies_menu;
         placement3d dependents_menu_place;
         placement3d relatives_menu_place;
         placement3d dependencies_menu_place;
         bool initialized;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<std::string, std::string>> dependents_menu_items={{"Foo", "foo"}, {"Bar", "bar"}}, std::vector<std::tuple<std::string, std::string>> relatives_menu_items={{"Baz", "baz"}, {"Buz", "buz"}}, std::vector<std::tuple<std::string, std::string>> dependencies_menu_items={{"Fiz", "fiz"}, {"Foz", "foz"}});
         ~Stage();

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         void initialize();
         void render() override;
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         void set_upcase(bool upcase=false);
         void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         void emit_submission();
      };
   }
}



