#pragma once


#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace Elements
   {
      class CheckTextureGenerator
      {
      private:
         ALLEGRO_DISPLAY* display;

      protected:


      public:
         CheckTextureGenerator(ALLEGRO_DISPLAY* display=nullptr);
         ~CheckTextureGenerator();

         ALLEGRO_BITMAP* generate_grid_check();
      };
   }
}



