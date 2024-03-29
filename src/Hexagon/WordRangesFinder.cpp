

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
   std::pair<int, int> result = find_word_char_ranges();
   if (is_valid(result)) return result;

   result = find_non_word_char_ranges();
   if (is_valid(result)) return result;

   return find_whitespace_char_ranges();
}

std::pair<int, int> WordRangesFinder::find_word_char_ranges()
{
   if (cursor_pos < 0) return std::pair<int, int>(-1, -1);
   if (cursor_pos >= line_of_text.length()) return std::pair<int, int>(-1, -1);

   const std::string word_matching_chars = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

   if (word_matching_chars.find(line_of_text[cursor_pos]) == std::string::npos)
   {
      return std::pair<int, int>(-1, -1);
   }

   std::size_t start_pos = line_of_text.find_last_not_of(word_matching_chars, cursor_pos) + 1;
   std::size_t end_pos = line_of_text.find_first_not_of(word_matching_chars, cursor_pos);

   if (end_pos == std::string::npos) end_pos = (int)line_of_text.length();

   return std::pair<int, int>(start_pos, end_pos - start_pos);
}

std::pair<int, int> WordRangesFinder::find_non_word_char_ranges()
{
   if (cursor_pos < 0) return std::pair<int, int>(-1, -1);
   if (cursor_pos >= line_of_text.length()) return std::pair<int, int>(-1, -1);

   const std::string word_matching_chars = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
   const std::string whitespace_matching_chars = " \f\n\r\t\v"; // chars matching the isupper() function from c++
   const std::string non_word_matching_chars = word_matching_chars + whitespace_matching_chars;

   if (non_word_matching_chars.find(line_of_text[cursor_pos]) != std::string::npos)
   {
      return std::pair<int, int>(-1, -1);
   }

   std::size_t start_pos = line_of_text.find_last_of(non_word_matching_chars, cursor_pos) + 1;
   std::size_t end_pos = line_of_text.find_first_of(non_word_matching_chars, cursor_pos);

   if (end_pos == std::string::npos) end_pos = (int)line_of_text.length();

   return std::pair<int, int>(start_pos, end_pos - start_pos);
}

std::pair<int, int> WordRangesFinder::find_whitespace_char_ranges()
{
   if (cursor_pos < 0) return std::pair<int, int>(-1, -1);
   if (cursor_pos >= line_of_text.length()) return std::pair<int, int>(-1, -1);

   const std::string whitespace_matching_chars = " \f\n\r\t\v"; // chars matching the isupper() function from c++

   if (whitespace_matching_chars.find(line_of_text[cursor_pos]) == std::string::npos)
   {
      return std::pair<int, int>(-1, -1);
   }

   std::size_t start_pos = line_of_text.find_last_not_of(whitespace_matching_chars, cursor_pos) + 1;
   std::size_t end_pos = line_of_text.find_first_not_of(whitespace_matching_chars, cursor_pos);

   if (end_pos == std::string::npos) end_pos = (int)line_of_text.length();

   return std::pair<int, int>(start_pos, end_pos - start_pos);
}

bool WordRangesFinder::is_valid(std::pair<int, int> word_range)
{
   return word_range != std::pair<int, int>(-1, -1);
}


} // namespace Hexagon


