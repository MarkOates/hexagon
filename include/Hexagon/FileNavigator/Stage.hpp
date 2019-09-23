#pragma once


#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace FileNavigator
   {
      class Stage : public StageInterface
      {
      private:

      public:
         Stage();
         ~Stage();


      std::string run();
      void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      };
   }
}



