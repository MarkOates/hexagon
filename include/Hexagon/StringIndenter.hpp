#pragma once


#include <cstddef>
#include <string>


namespace Hexagon
{
   class StringIndenter
   {
   private:
      std::string content;

   protected:


   public:
      StringIndenter(std::string content="[unset-content]");
      ~StringIndenter();

      std::string indent(std::size_t num_indents=2);
      std::string unindent(std::size_t num_unindents=2);
   };
}



