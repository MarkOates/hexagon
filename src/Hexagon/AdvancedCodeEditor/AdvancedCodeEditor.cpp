

#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


AdvancedCodeEditor::AdvancedCodeEditor()
   : lines({})
{
}


AdvancedCodeEditor::~AdvancedCodeEditor()
{
}


bool AdvancedCodeEditor::set_initial_content(std::string content)
{
lines = Blast::StringSplitter(content, '\n').split();
return true;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


