

#include <Hexagon/Testing/Comparison/Hexagon/AdvancedCodeEditor/Selection.hpp>


namespace Hexagon::AdvancedCodeEditor
{


bool operator==(const Selection& object, const Selection& other_object)
{
   std::vector<CodeRange> object_code_ranges = object.get_code_ranges();
   std::vector<CodeRange> other_object_code_ranges = other_object.get_code_ranges();

   if (object_code_ranges.size() != other_object_code_ranges.size()) return false;

   for (int i=0; i<object_code_ranges.size(); i++)
   {
      auto &code_range = object_code_ranges[i];
      auto &other_code_range = other_object_code_ranges[i];

      CodePoint start = code_range.infer_cursor_start();
      CodePoint other_start = other_code_range.infer_cursor_start();

      if (start.get_x() != other_start.get_x()) return false;
      if (start.get_y() != other_start.get_y()) return false;

      CodePoint end = code_range.infer_cursor_start();
      CodePoint other_end = other_code_range.infer_cursor_start();

      if (start.get_x() != other_start.get_x()) return false;
      if (start.get_y() != other_start.get_y()) return false;
   }

   return true;
}


bool operator!=(const Selection& object, const Selection& other_object)
{
   return !(object == other_object);
}


void PrintTo(const Selection& object, ::std::ostream* os)
{
   *os << "Selection(";
   std::vector<CodeRange> code_ranges = object.get_code_ranges();

   for (int i=0; i<code_ranges.size(); i++)
   {
      auto &code_range = code_ranges[i];
      CodePoint start = code_range.infer_cursor_start();
      CodePoint end = code_range.infer_cursor_end();

      *os << "[" << i << "]{";
         *os << start.get_x() << ", ";
         *os << start.get_y() << ", ";
         *os << end.get_x() << ", ";
         *os << end.get_y() << ", ";
      *os << "}, ";
   }
   *os << ")";
}


} // namespace Hexagon::AdvancedCodeEditor


