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

      protected:


      public:
         FileCategoryDecorator(std::string file_category="undefined");
         ~FileCategoryDecorator();

         std::string label();
      };
   }
}



