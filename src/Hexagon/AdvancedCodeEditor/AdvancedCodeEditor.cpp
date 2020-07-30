

#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


AdvancedCodeEditor::AdvancedCodeEditor()
   : lines({})
   , cursor({})
{
}


AdvancedCodeEditor::~AdvancedCodeEditor()
{
}


std::vector<std::string> AdvancedCodeEditor::get_lines()
{
   return lines;
}


Hexagon::AdvancedCodeEditor::Cursor &AdvancedCodeEditor::get_cursor_ref()
{
   return cursor;
}


bool AdvancedCodeEditor::set_initial_content(std::string content)
{
lines = Blast::StringSplitter(content, '\n').split();
return true;

}

bool AdvancedCodeEditor::cursor_move_up()
{
cursor.move_up();
return true;

}

bool AdvancedCodeEditor::cursor_move_down()
{
cursor.move_down();
return true;

}

bool AdvancedCodeEditor::cursor_move_left()
{
cursor.move_left();
return true;

}

bool AdvancedCodeEditor::cursor_move_right()
{
cursor.move_right();
return true;

}

bool AdvancedCodeEditor::cursor_move_to(int x, int y)
{
cursor.move_to(x, y);
return true;

}

bool AdvancedCodeEditor::is_cursor_in_bounds()
{
if (cursor.get_y() >= lines.size()) return false;
if (cursor.get_y() < 0) return false;
if (cursor.get_x() >= lines[cursor.get_y()].size()) return false;
return true;

}

bool AdvancedCodeEditor::is_cursor_on_last_line()
{
if (lines.empty()) return false;
return cursor.get_y() == (lines.size() - 1);

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


