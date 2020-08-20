#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class TaoTeChingQuoteGenerator
   {
   private:
      std::vector<std::string> quotes;

   public:
      TaoTeChingQuoteGenerator(std::vector<std::string> quotes=TaoTeChingQuoteGenerator::default_quotes_list());
      ~TaoTeChingQuoteGenerator();


   std::string pick_quote();
   static std::vector<std::string> default_quotes_list();
   };
}



