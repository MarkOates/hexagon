#pragma once


#include <string>
#include <utility>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class SymbolUnderCursorMatcher
      {
      public:
         static constexpr std::pair<int, int> NO_MATCH_FOUND = { -1, -1 };

      private:

      protected:


      public:
         SymbolUnderCursorMatcher();
         ~SymbolUnderCursorMatcher();

         bool is_valid_symbol_char(char c=0);
         bool is_valid_match(std::pair<int, int> match_result=NO_MATCH_FOUND);
         std::pair<int, int> find_symbol_range(std::string line_of_code="[unset-line_of_code]", int cursor_position=-1);
      };
   }
}



