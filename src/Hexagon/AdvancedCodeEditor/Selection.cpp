

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
{


Selection::Selection(std::vector<CodeRange> code_ranges)
   : code_ranges(code_ranges)
{
}


Selection::~Selection()
{
}


std::vector<CodeRange> Selection::get_code_ranges()
{
   return code_ranges;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


