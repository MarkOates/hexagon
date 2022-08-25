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
         std::string get_project_root() const;
         int get_cursor_position() const;
         bool get_cursor_position_static() const;
         std::vector<Blast::Project::Component> get_nodes() const;
         std::string get_mode() const;
         std::string get_search_text() const;
         bool is_mode_navigating_list();
         bool is_mode_typing_in_search_bar();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_to_top();
         bool current_selection_is_valid();
         void set_mode_to_navigating_list();
         void set_mode_to_typing_in_search_bar();
         std::string get_current_selection_label_or_empty_string();
         void refresh_list();
         void yank_selected_text_label();
         void yank_selected_text_as_component_name();
         void yank_selected_text_as_include_directive();
         void yank_selected_text_as_quintessence_dependency_lines();
         void yank_selected_text_as_public_parent_class_lines();
         void yank_selected_text_as_injected_dependency_property();
         void yank_selected_text_as_error_message_template();
         std::string convert_to_snake_case(std::string source_str="[unset-str]");
      };
   }
}



