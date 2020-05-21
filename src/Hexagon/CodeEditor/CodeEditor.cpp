

#include <Hexagon/CodeEditor/CodeEditor.hpp>



namespace Hexagon
{
namespace CodeEditor
{


CodeEditor::CodeEditor()
   : cursor_x(0)
   , cursor_y(0)
{
}


CodeEditor::~CodeEditor()
{
}


void CodeEditor::set_cursor_x(int cursor_x)
{
   this->cursor_x = cursor_x;
}


void CodeEditor::set_cursor_y(int cursor_y)
{
   this->cursor_y = cursor_y;
}


int CodeEditor::get_cursor_x()
{
   return cursor_x;
}


int CodeEditor::get_cursor_y()
{
   return cursor_y;
}


std::string CodeEditor::run()
{
return "Hello World!";
}
} // namespace CodeEditor
} // namespace Hexagon


