

#include <Hexagon/WordRangesFinder.hpp>



namespace Hexagon
{


WordRangesFinder::WordRangesFinder(std::string line_of_text, int cursor_pos)
   : line_of_text(line_of_text)
   , cursor_pos(cursor_pos)
{
}


WordRangesFinder::~WordRangesFinder()
{
}


std::pair<int, int> WordRangesFinder::find_ranges()
{
   if (cursor_pos < 0) return std::pair<int, int>(-1, 0);
   if (cursor_pos >= line_of_text.length()) return std::pair<int, int>(-1, 0);
   return std::pair<int, int>(1, 1);
}
} // namespace Hexagon


