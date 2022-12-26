

#include <Hexagon/ChatGPTIntegration/Chat/InputBox.hpp>

#include <Blast/StringJoiner.hpp>


namespace Hexagon
{
namespace ChatGPTIntegration
{
namespace Chat
{


InputBox::InputBox()
   : text_editor()
{
}


InputBox::~InputBox()
{
}


Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &InputBox::get_text_editor_ref()
{
   return text_editor;
}


bool InputBox::clear()
{
   text_editor.set_content("");
   text_editor.cursor_move_to(0, 0);
}

bool InputBox::move_cursor_up()
{
   return text_editor.cursor_move_up();
}

bool InputBox::move_cursor_down()
{
   return text_editor.cursor_move_down();
}

bool InputBox::move_cursor_left()
{
   return text_editor.cursor_move_left();
}

bool InputBox::move_cursor_right()
{
   return text_editor.cursor_move_right();
}

bool InputBox::insert_string(std::string text)
{
   return text_editor.insert_string(text);
}

bool InputBox::delete_character()
{
   return text_editor.delete_character();
}

Hexagon::AdvancedCodeEditor::Cursor InputBox::get_cursor()
{
   return text_editor.get_cursor_ref();
}

std::string InputBox::get_text()
{
   Blast::StringJoiner joiner(text_editor.get_lines(), "\n");
   return joiner.join();
}


} // namespace Chat
} // namespace ChatGPTIntegration
} // namespace Hexagon


