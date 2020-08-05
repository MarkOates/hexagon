#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class TextPixelPreviewCreator
      {
      private:
         std::string filename;
         int width;

      public:
         TextPixelPreviewCreator(std::string filename="", int width=120);
         ~TextPixelPreviewCreator();


      ALLEGRO_BITMAP* create();
      std::vector<std::string> get_file_contents();
      };
   }
}



