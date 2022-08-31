#pragma once


#include <Hexagon/CodeRange.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class SearchRegexToSelectionsConverter
      {
      private:
         std::string search_regex_string;
         std::vector<std::string> lines;

      protected:


      public:
         SearchRegexToSelectionsConverter(std::string search_regex_string="", std::vector<std::string> lines={});
         ~SearchRegexToSelectionsConverter();

         std::vector<CodeRange> convert();
      };
   }
}



