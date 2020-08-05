#pragma once


#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class FilePixelPreviewCreator
      {
      private:
         std::string filename;

      public:
         FilePixelPreviewCreator(std::string filename="");
         ~FilePixelPreviewCreator();


      std::string run();
      };
   }
}



