#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace FileNavigator
   {
      class Stage : public StageInterface
      {
      private:
         bool cursor_position_static;
         static ALLEGRO_EVENT a_default_empty_event;
         ALLEGRO_COLOR selector_color;
         std::vector<std::string> nodes;
         int cursor_position;
         std::string node_root;

      public:
         Stage(std::string node_root="/Users/markoates/Repos");
         ~Stage();

         void set_cursor_position_static(bool cursor_position_static);
         void set_selector_color(ALLEGRO_COLOR selector_color);
         void set_nodes(std::vector<std::string> nodes);
         void set_node_root(std::string node_root);

         ALLEGRO_COLOR get_selector_color();
         std::vector<std::string> get_nodes();
         int get_cursor_position();
         std::string get_node_root();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void move_cursor_down();
      bool current_selection_is_valid();
      std::string get_current_selection_or_spaced_empty_string();
      std::string get_current_selection();
      bool current_selection_is_folder();
      void move_cursor_up();
      void move_cursor_to_top();
      void set_node_root_to_system_root_directory();
      void set_node_root_to_repos_directory();
      void set_node_root_to_user_directory();
      void set_node_root_to_parent_directory();
      void set_node_root_to_current_selection_if_folder();
      void refresh_list();
      void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      bool save_file();
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



