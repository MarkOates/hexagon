#pragma once


#include <allegro5/allegro.h>
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
         std::vector<std::string> get_file_contents();

      protected:


      public:
         FilePixelPreviewCreator(std::string filename="", int width=120);
         ~FilePixelPreviewCreator();

         ALLEGRO_BITMAP* create();
      };
   }
}



