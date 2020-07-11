#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class AdvancedCodeEditor
      {
      private:
         std::vector<std::string> lines;

      public:
         AdvancedCodeEditor();
         ~AdvancedCodeEditor();


      bool set_initial_content(std::string content="");
      };
   }
}



