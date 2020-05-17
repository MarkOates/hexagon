#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class AdvancedComponentNavigator
      {
      private:
         std::string project_root;
         int cursor_position;
         bool cursor_position_static;
         std::vector<Blast::Project::Component> nodes;
         std::string mode;
         std::string search_text;

      public:
         AdvancedComponentNavigator(std::string project_root="/Users/markoates/Repos/hexagon/");
         ~AdvancedComponentNavigator();

         void set_project_root(std::string project_root);
         void set_cursor_position_static(bool cursor_position_static);
         void set_nodes(std::vector<Blast::Project::Component> nodes);
         void set_mode(std::string mode);
         void set_search_text(std::string search_text);

         std::string get_project_root();
         int get_cursor_position();
         bool get_cursor_position_static();
         std::vector<Blast::Project::Component> get_nodes();
         std::string get_mode();
         std::string get_search_text();
      void move_cursor_up();
      void move_cursor_down();
      void move_cursor_to_top();
      bool current_selection_is_valid();
      void set_mode_to_navigating_list();
      void set_mode_to_typing_in_search_bar();
      std::string get_current_selection_label_or_empty_string();
      void refresh_list();
      };
   }
}



