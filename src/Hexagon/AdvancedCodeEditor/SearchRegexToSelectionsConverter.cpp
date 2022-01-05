

#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>
#include <vector>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/RegexMatcher.hpp>


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

   for (auto &line : lines)
   {
      RegexMatcher regex_matcher(search_regex_string, line); 
      std::vector<std::pair<int, int>> match_results = regex_matcher.get_match_info();
   }         

   return result;
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


