#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class SimpleTextSearcher
   {
   private:
      std::string search_text;
      std::vector<std::string> elements;

   public:
      SimpleTextSearcher(std::string search_text="", std::vector<std::string> elements={});
      ~SimpleTextSearcher();

      bool would_be_included_in_results(std::string element="");
      std::vector<std::string> results();
   };
}



