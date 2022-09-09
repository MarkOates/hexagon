

#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>

#include <Blast/RegexMatcher.hpp>
#include <Hexagon/CodeRange.hpp>
#include <iostream>
#include <vector>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


SearchRegexToSelectionsConverter::SearchRegexToSelectionsConverter(std::string search_regex_string, std::vector<std::string> lines)
   : search_regex_string(search_regex_string)
   , lines(lines)
{
}


SearchRegexToSelectionsConverter::~SearchRegexToSelectionsConverter()
{
}


std::vector<CodeRange> SearchRegexToSelectionsConverter::convert()
{
   std::vector<CodeRange> result;

   Blast::RegexMatcher regex_matcher;
   regex_matcher.set_regex_expression(search_regex_string); 

   for (int line_num=0; line_num<lines.size(); line_num++)
   {
      regex_matcher.set_source_string(lines[line_num]);
      //std::string& line = lines[line_num];

      //Blast::RegexMatcher regex_matcher(line, search_regex_string); 
      std::vector<std::pair<int, int>> matches = regex_matcher.get_match_info();
      for (std::pair<int, int> &match : matches)
      {
         int position = match.first;
         int length = match.second;
         result.push_back(CodeRange{position, line_num, position+length, line_num});
      }
   }         

   return result;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


