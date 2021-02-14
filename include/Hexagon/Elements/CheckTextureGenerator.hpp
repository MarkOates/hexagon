#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class CheckTextureGenerator
      {
      private:
         ALLEGRO_DISPLAY* display;

      public:
         CheckTextureGenerator(ALLEGRO_DISPLAY* display=nullptr);
         ~CheckTextureGenerator();

         void validate_al_init(std::string function_name="[unmamed_function]");
         void validate_display(std::string function_name="[unmamed_function]");
         ALLEGRO_BITMAP* generate_grid_check();
      };
   }
}



