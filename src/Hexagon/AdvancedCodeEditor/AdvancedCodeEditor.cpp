

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
} // namespace AdvancedCodeEditor
} // namespace Hexagon


