#pragma once


#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class FileCategoryDecorator
      {
      private:
         std::string file_category;

      public:
         FileCategoryDecorator(std::string file_category="undefined");
         ~FileCategoryDecorator();

         std::string label();
      };
   }
}



