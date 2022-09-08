

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>

#include <sstream>
#include <stdexcept>


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


std::vector<CodeRange> Selection::get_code_ranges() const
{
   return code_ranges;
}


void Selection::clear()
{
   code_ranges.clear();
   return;
}

bool Selection::push_down_from(int starting_on_line, int num_lines_to_push_down)
{
   if (!((num_lines_to_push_down >= 0)))
   {
      std::stringstream error_message;
      error_message << "Selection" << "::" << "push_down_from" << ": error: " << "guard \"(num_lines_to_push_down >= 0)\" not met";
      throw std::runtime_error(error_message.str());
   }
   for (int i=code_ranges.size()-1; i>=0; i--)
   {
      auto &code_range = code_ranges[i];

      CodePoint start = code_range.infer_cursor_start();
      CodePoint end = code_range.infer_cursor_end();

      if (start.get_y() >= starting_on_line)
      {
         code_range.move(0, num_lines_to_push_down);
      }
   }
   return true;
}

CodePoint Selection::find_next_from(int position_x, int position_y)
{
   CodePoint anchor_code_point(position_x, position_y);

   // get ANY code point that is bigger than anchor_code_point to be the first "most_viable_code_point"
   CodePoint most_viable_code_point(position_x, position_y);
   for (auto &code_range : code_ranges)
   {
      CodePoint code_point = code_range.infer_cursor_start();
      if (most_viable_code_point < code_point)
      {
         most_viable_code_point = code_point;
         break;
      }
   }

   for (auto &code_range : code_ranges)
   {
      CodePoint code_point = code_range.infer_cursor_start();
      if (anchor_code_point < code_point && code_point < most_viable_code_point)
      {
         most_viable_code_point = code_point;
      }
   }

   return most_viable_code_point;
}

CodePoint Selection::find_previous_from(int position_x, int position_y)
{
   CodePoint anchor_code_point(position_x, position_y);

   // get ANY code point that is smaller than anchor_code_point to be the first "most_viable_code_point"
   CodePoint most_viable_code_point(position_x, position_y);
   for (auto &code_range : code_ranges)
   {
      CodePoint code_point = code_range.infer_cursor_start();
      if (code_point < most_viable_code_point)
      {
         most_viable_code_point = code_point;
         break;
      }
   }

   for (auto &code_range : code_ranges)
   {
      CodePoint code_point = code_range.infer_cursor_start();
      if (code_point < anchor_code_point && most_viable_code_point < code_point)
      {
         most_viable_code_point = code_point;
      }
   }

   return most_viable_code_point;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


