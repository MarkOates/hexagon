

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

   const std::string word_matching_chars = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

   int start_pos = line_of_text.find_last_not_of(word_matching_chars, cursor_pos) + 1;
   int end_pos = line_of_text.find_first_not_of(word_matching_chars, cursor_pos);

   return std::pair<int, int>(start_pos, end_pos - start_pos);
}
} // namespace Hexagon


