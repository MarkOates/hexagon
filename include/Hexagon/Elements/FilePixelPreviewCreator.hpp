#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class FilePixelPreviewCreator
      {
      private:
         std::string filename;
         int width;

      public:
         FilePixelPreviewCreator(std::string filename="", int width=120);
         ~FilePixelPreviewCreator();


      void create();
      std::vector<std::string> file_contents();
      };
   }
}



