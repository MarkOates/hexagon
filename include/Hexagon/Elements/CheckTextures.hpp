#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class CheckTextures
      {
      private:
         ALLEGRO_DISPLAY* display;

      public:
         CheckTextures(ALLEGRO_DISPLAY* display=nullptr);
         ~CheckTextures();


      void validate_al_init(std::string function_name="[unmamed_function]");
      void validate_display(std::string function_name="[unmamed_function]");
      ALLEGRO_BITMAP* generate_grid_check();
      };
   }
}



