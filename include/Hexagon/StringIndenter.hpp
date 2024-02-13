#pragma once


#include <cstddef>
#include <string>
#include <vector>


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

      static std::vector<std::string> indent_lines(std::vector<std::string> lines={}, std::size_t num_indents=2);
      static std::vector<std::string> unindent_lines(std::vector<std::string> lines={}, std::size_t num_unindents=2);
      std::string indent(std::size_t num_indents=2);
      std::string unindent(std::size_t num_unindents=2);
   };
}



