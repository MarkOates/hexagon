#pragma once


#include <Hexagon/System/System.hpp>


namespace Hexagon
{
   namespace System
   {
      class Renderer
      {
      private:
         ::System* system;

      public:
         Renderer();
         ~Renderer();


      bool render();
      };
   }
}



