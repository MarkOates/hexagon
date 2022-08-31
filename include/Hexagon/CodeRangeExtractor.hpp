#pragma once


#include <Hexagon/CodeRange.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class CodeRangeExtractor
   {
   private:
      std::vector<std::string>* lines;
      CodeRange* code_range;

   protected:


   public:
      CodeRangeExtractor(std::vector<std::string>* lines=nullptr, CodeRange* code_range=nullptr);
      ~CodeRangeExtractor();

      std::vector<std::string> extract();
      std::vector<std::string> extract_full_lines();
   };
}



