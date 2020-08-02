#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/DirtyGrid.hpp>
#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class AdvancedCodeEditor
      {
      private:
         std::vector<std::string> lines;
         Hexagon::AdvancedCodeEditor::Cursor cursor;
         Hexagon::DirtyGrid dirty_grid;
         std::vector<std::pair<int, int>> characters_changed_in_last_action;

      public:
         AdvancedCodeEditor();
         ~AdvancedCodeEditor();


         std::vector<std::string> get_lines();
         std::vector<std::pair<int, int>> get_characters_changed_in_last_action();
         std::vector<std::string> &get_lines_ref();
         Hexagon::AdvancedCodeEditor::Cursor &get_cursor_ref();
      bool set_content(std::string content="");
      bool insert_string(std::string string="");
      bool delete_character();
      bool join_lines();
      bool split_lines();
      bool delete_line();
      bool insert_lines(std::vector<std::string> lines_to_insert={});
      bool cursor_set_width(float width=0.0f);
      bool cursor_set_height(float height=0.0f);
      bool cursor_move_up();
      bool cursor_move_down();
      bool cursor_move_left();
      bool cursor_move_right();
      bool cursor_move_to_start_of_line();
      bool cursor_move_to(int x=0, int y=0);
      bool cursor_set_x(int x=0);
      bool cursor_set_y(int y=0);
      int cursor_get_x();
      int cursor_get_y();
      bool is_cursor_in_bounds();
      bool is_cursor_on_last_line();
      };
   }
}



