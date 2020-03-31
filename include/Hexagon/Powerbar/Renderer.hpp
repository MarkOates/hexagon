#pragma once


#include <Hexagon/Powerbar/Powerbar.hpp>


namespace Hexagon
{
   namespace Powerbar
   {
      class Renderer
      {
      private:
         Hexagon::Powerbar::Powerbar* powerbar;
         float width;

      public:
         Renderer(Hexagon::Powerbar::Powerbar* powerbar=nullptr, float width=1000.0f);
         ~Renderer();


      void render();
      };
   }
}



