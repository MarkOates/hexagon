#pragma once


#include <Hexagon/Elements/Window.hpp>


namespace Hexagon
{
   namespace ElementFX
   {
      class WindowSpawnMotionFX
      {
      private:
         Hexagon::Elements::Window window;

      public:
         WindowSpawnMotionFX(Hexagon::Elements::Window window={});
         ~WindowSpawnMotionFX();

         Hexagon::Elements::Window construct_modified_window();
      };
   }
}



