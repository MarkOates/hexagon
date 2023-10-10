

#include <Hexagon/AdvancedCodeEditor/SymbolUnderCursorMatcher.hpp>




namespace Hexagon
{
namespace AdvancedCodeEditor
{


SymbolUnderCursorMatcher::SymbolUnderCursorMatcher()
{
}


SymbolUnderCursorMatcher::~SymbolUnderCursorMatcher()
{
}


bool SymbolUnderCursorMatcher::is_valid_symbol_char(char c)
{
   return (isalnum(c) || c == '_' || c == ':');
}

bool SymbolUnderCursorMatcher::is_valid_match(std::pair<int, int> match_result)
{
   return (match_result != NO_MATCH_FOUND);
}

std::pair<int, int> SymbolUnderCursorMatcher::find_symbol_range(std::string line_of_code, int cursor_position)
{
   if (cursor_position < 0) NO_MATCH_FOUND;
   if (cursor_position >= line_of_code.size()) return NO_MATCH_FOUND;

   int start_position = cursor_position;
   int end_position = cursor_position;

   // Check if the character under the cursor is a valid symbol character
   if (is_valid_symbol_char(line_of_code[cursor_position]))
   {
      // Find the start position of the symbol
      while (start_position > 0 && is_valid_symbol_char(line_of_code[start_position - 1]))
      {
         start_position--;
      }

      // Find the end position of the symbol
      while (end_position < line_of_code.length() - 1 && is_valid_symbol_char(line_of_code[end_position + 1]))
      {
         end_position++;
      }
   }

   return std::make_pair(start_position, end_position);
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


