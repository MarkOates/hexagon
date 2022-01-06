#pragma once


#include <Hexagon/CodePoint.hpp>
#include <Hexagon/CodeRange.hpp>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Selection
      {
      private:
         std::vector<CodeRange> code_ranges;

      public:
         Selection(std::vector<CodeRange> code_ranges={});
         ~Selection();

         std::vector<CodeRange> get_code_ranges();
         void clear();
         CodePoint find_next_from(int position_x=0, int position_y=0);
         CodePoint find_previous_from(int position_x=0, int position_y=0);
      };
   }
}



