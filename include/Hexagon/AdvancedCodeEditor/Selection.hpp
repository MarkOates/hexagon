#pragma once


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
      };
   }
}



