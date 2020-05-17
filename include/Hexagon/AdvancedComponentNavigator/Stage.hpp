#pragma once


#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Blast/Project/Component.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <map>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class Stage : public StageInterface
      {
      private:
         std::string project_root;
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator component;
         int X_cursor_position;
         bool X_cursor_position_static;
         static ALLEGRO_EVENT a_default_empty_event;
         std::vector<Blast::Project::Component> X_nodes;
         std::string X_search_text;
         std::string X_mode;

      public:
         Stage(std::string project_root="/Users/markoates/Repos/hexagon");
         ~Stage();

         void set_project_root(std::string project_root);
         void set_X_cursor_position_static(bool X_cursor_position_static);
         void set_X_nodes(std::vector<Blast::Project::Component> X_nodes);
         void set_X_search_text(std::string X_search_text);
         void set_X_mode(std::string X_mode);

         std::string get_project_root();
         int get_X_cursor_position();
         bool get_X_cursor_position_static();
         std::vector<Blast::Project::Component> get_X_nodes();
         std::string get_X_search_text();
         std::string get_X_mode();
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &get_component_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      KeyboardCommandMapper build_keyboard_command_mapping();
      std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> build_local_events_dictionary();
      void move_cursor_up();
      void move_cursor_down();
      void move_cursor_to_top();
      bool current_selection_is_valid();
      void set_mode_to_navigating_list();
      void set_mode_to_typing_in_search_bar();
      std::string get_current_selection_label_or_empty_string();
      void refresh_list();
      void render(bool is_focused=true, ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_char_event(int keycode=0, int unichar=0, bool is_repeat=false);
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      bool save_file();
      };
   }
}



