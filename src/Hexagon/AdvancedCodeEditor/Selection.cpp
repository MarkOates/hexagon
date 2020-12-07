

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
{


Selection::Selection(std::vector<CodeRange> selections)
   : selections(selections)
{
}


Selection::~Selection()
{
}


std::vector<CodeRange> Selection::get_selections()
{
   return selections;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


