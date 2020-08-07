#pragma once


#include <Hexagon/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Shaders
   {
      class Fun : private Hexagon::Shaders::Base
      {
      private:
         bool initialized;

      public:
         Fun();
         ~Fun();


      void initialize();
      void activate();
      void set_flat_color(ALLEGRO_COLOR flat_color={});
      void set_texture_width(int width=1);
      static std::string obtain_vertex_source();
      static std::string obtain_fragment_source();
      };
   }
}



