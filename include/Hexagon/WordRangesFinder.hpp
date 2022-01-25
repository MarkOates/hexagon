#pragma once


#include <string>
#include <utility>


namespace Hexagon
{
   class WordRangesFinder
   {
   private:
      std::string line_of_text;
      int cursor_pos;

   public:
      WordRangesFinder(std::string line_of_text="empty", int cursor_pos=0);
      ~WordRangesFinder();

      std::pair<int, int> find_ranges();
      bool is_valid(std::pair<int, int> word_range={0, 0});
   };
}



