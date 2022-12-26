#pragma once


#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class InputBox
         {
         private:
            Hexagon::AdvancedCodeEditor::AdvancedCodeEditor text_editor;

         protected:


         public:
            InputBox();
            ~InputBox();

            Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &get_text_editor_ref();
            void draw();
            bool move_cursor_up();
            bool move_cursor_down();
            bool move_cursor_left();
            bool move_cursor_right();
            bool insert_string(std::string text="[unset-text]");
            bool delete_character();
            Hexagon::AdvancedCodeEditor::Cursor get_cursor();
            std::string get_text();
         };
      }
   }
}



