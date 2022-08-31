#pragma once


#include <string>


namespace Hexagon
{
   class RegexStore
   {
   private:

   protected:


   public:
      RegexStore();
      ~RegexStore();

      static std::string identifiers();
      static std::string double_quoted_strings_with_escapes();
   };
}



