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


   std::vector<std::string> results();
   };
}



