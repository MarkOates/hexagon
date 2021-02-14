

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


bool SimpleTextSearcher::would_be_included_in_results(std::string element)
{
   std::size_t found = element.find(search_text);
   return found != std::string::npos;
}

std::vector<std::string> SimpleTextSearcher::results()
{
   if (search_text.empty()) return elements;

   std::vector<std::string> results;

   for (auto &element : elements)
   {
      if (would_be_included_in_results(element)) results.push_back(element);
   }

   return results;
}
} // namespace Blast


