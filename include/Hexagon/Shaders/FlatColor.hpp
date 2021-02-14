#pragma once


#include <Hexagon/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Shaders
   {
      class FlatColor : private Hexagon::Shaders::Base
      {
      private:
         bool initialized;

      public:
         FlatColor();
         ~FlatColor();

         void initialize();
         void activate();
         void set_flat_color(ALLEGRO_COLOR flat_color={});
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}



