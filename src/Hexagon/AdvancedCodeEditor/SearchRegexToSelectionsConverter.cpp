

#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>



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


std::vector<Hexagon::AdvancedCodeEditor::Selection> SearchRegexToSelectionsConverter::convert()
{
   std::vector<Hexagon::AdvancedCodeEditor::Selection> result;
   return result;
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


