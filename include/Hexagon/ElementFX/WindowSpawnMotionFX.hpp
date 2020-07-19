#pragma once


#include <Hexagon/Elements/Window.hpp>
#include <string>


namespace Hexagon
{
   namespace ElementFX
   {
      class WindowSpawnMotionFX
      {
      private:
         Hexagon::Elements::Window* window;

      public:
         WindowSpawnMotionFX(Hexagon::Elements::Window* window=nullptr);
         ~WindowSpawnMotionFX();


      std::string run();
      };
   }
}



