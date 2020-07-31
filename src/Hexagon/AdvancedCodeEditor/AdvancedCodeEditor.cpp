

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


std::vector<std::string> &AdvancedCodeEditor::get_lines_ref()
{
   return lines;
}


Hexagon::AdvancedCodeEditor::Cursor &AdvancedCodeEditor::get_cursor_ref()
{
   return cursor;
}


bool AdvancedCodeEditor::set_content(std::string content)
{
lines = Blast::StringSplitter(content, '\n').split();
return true;

}

bool AdvancedCodeEditor::insert_string(std::string string)
{
Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
std::vector<std::string> &lines = get_lines_ref();

if (!is_cursor_in_bounds()) return false;
lines[cursor.get_y()].insert(cursor.get_x(), string);
return true;

}

bool AdvancedCodeEditor::delete_character()
{
Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
std::vector<std::string> &lines = get_lines_ref();

if (!is_cursor_in_bounds()) return false;
lines[cursor.get_y()].erase(cursor.get_x(), 1);
return true;

}

bool AdvancedCodeEditor::join_lines()
{
Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
std::vector<std::string> &lines = get_lines_ref();

if (!is_cursor_in_bounds()) return false;
if (is_cursor_on_last_line()) return false;

lines[cursor.get_y()] += lines[cursor.get_y()+1];
lines.erase(lines.begin() + cursor.get_y()+1);

return true;

}

bool AdvancedCodeEditor::split_lines()
{
if (!is_cursor_in_bounds()) return false;

lines.insert(lines.begin() + cursor.get_y() + 1, lines[cursor.get_y()].substr(cursor.get_x()));
std::string &current_line = lines[cursor.get_y()];
current_line.erase(cursor.get_x());
return true;

}

bool AdvancedCodeEditor::delete_line()
{
if (cursor.get_y() < 0 || cursor.get_y() >= lines.size()) return false;
lines.erase(lines.begin()+cursor.get_y());
return true;

}

bool AdvancedCodeEditor::insert_lines(std::vector<std::string> lines_to_insert)
{
int range_safe_y = std::min(std::max(0, cursor.get_y()), (int)lines.size());
lines.insert(lines.begin() + range_safe_y, lines_to_insert.begin(), lines_to_insert.end());
return true;

}

bool AdvancedCodeEditor::cursor_set_width(float width)
{
cursor.set_width(width);
return true;

}

bool AdvancedCodeEditor::cursor_set_height(float height)
{
cursor.set_height(height);
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

bool AdvancedCodeEditor::cursor_set_x(int x)
{
cursor.set_x(x);
return true;

}

bool AdvancedCodeEditor::cursor_set_y(int y)
{
cursor.set_y(y);
return true;

}

int AdvancedCodeEditor::cursor_get_x()
{
return cursor.get_x();

}

int AdvancedCodeEditor::cursor_get_y()
{
return cursor.get_y();

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


