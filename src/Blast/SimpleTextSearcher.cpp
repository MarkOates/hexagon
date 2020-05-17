

#include <Blast/SimpleTextSearcher.hpp>



namespace Blast
{


SimpleTextSearcher::SimpleTextSearcher(std::string search_text, std::vector<std::string> elements)
   : search_text(search_text)
   , elements(elements)
{
}


SimpleTextSearcher::~SimpleTextSearcher()
{
}


std::vector<std::string> SimpleTextSearcher::results()
{
if (search_text.empty()) return {};

std::vector<std::string> results;

for (auto &element : elements)
{
   std::size_t found = element.find(search_text);
   if (found != std::string::npos) results.push_back(element);
}

return results;

}
} // namespace Blast


