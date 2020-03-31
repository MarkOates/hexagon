#pragma once


#include <Hexgaon/Powerbar/Powerbar.hpp>


namespace Hexgaon
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



