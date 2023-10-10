#pragma once


#include <string>
#include <utility>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class SymbolUnderCursorMatcher
      {
      private:

      protected:


      public:
         SymbolUnderCursorMatcher();
         ~SymbolUnderCursorMatcher();

         bool is_valid_symbol_char(char c=0);
         std::pair<int, int> find_symbol_range(std::string line_of_code="[unset-line_of_code]", int cursor_position=-1);
      };
   }
}



