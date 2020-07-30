#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <string>
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

      public:
         AdvancedCodeEditor();
         ~AdvancedCodeEditor();


         Hexagon::AdvancedCodeEditor::Cursor &get_cursor_ref();
      bool set_initial_content(std::string content="");
      bool cursor_move_up();
      bool cursor_move_down();
      bool cursor_move_left();
      bool cursor_move_right();
      bool is_cursor_in_bounds();
      bool is_cursor_on_last_line();
      };
   }
}



