

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


void Selection::clear()
{
   code_ranges.clear();
   return;
}

CodePoint Selection::find_next_from(int position_x, int position_y)
{
   CodePoint result(position_x, position_y);
   // TODO
   return result;
}

CodePoint Selection::find_previous_from(int position_x, int position_y)
{
   CodePoint result(position_x, position_y);
   // TODO
   return result;
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


