#pragma once


#include <Hexagon/CodeRange.hpp>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Selection
      {
      private:
         std::vector<CodeRange> selections;

      public:
         Selection(std::vector<CodeRange> selections={});
         ~Selection();


         std::vector<CodeRange> get_selections();
      };
   }
}



