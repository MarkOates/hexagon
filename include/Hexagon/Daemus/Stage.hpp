#pragma once


#include <Hexagon/Daemus/Daemus.hpp>


namespace Hexagon
{
   namespace Daemus
   {
      class Stage
      {
      private:
         Hexagon::Daemus::Daemus daemus;

      public:
         Stage();
         ~Stage();

         void render();
      };
   }
}



