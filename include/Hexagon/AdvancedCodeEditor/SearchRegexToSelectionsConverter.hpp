#pragma once


#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
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

      public:
         SearchRegexToSelectionsConverter(std::string search_regex_string="", std::vector<std::string> lines={});
         ~SearchRegexToSelectionsConverter();

         std::vector<Hexagon::AdvancedCodeEditor::Selection> convert();
      };
   }
}



