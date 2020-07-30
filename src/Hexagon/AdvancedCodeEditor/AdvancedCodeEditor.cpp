

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
} // namespace AdvancedCodeEditor
} // namespace Hexagon


