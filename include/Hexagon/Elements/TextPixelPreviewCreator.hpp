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
         std::vector<std::string> text_lines;
         int width;

      protected:


      public:
         TextPixelPreviewCreator(std::vector<std::string> text_lines={}, int width=120);
         ~TextPixelPreviewCreator();

         ALLEGRO_BITMAP* create();
      };
   }
}



