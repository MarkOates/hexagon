#pragma once


#include <Hexagon/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Shaders
   {
      class TruchetMaze : private Hexagon::Shaders::Base
      {
      private:
         bool initialized;
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         TruchetMaze();
         ~TruchetMaze();

         void initialize();
         void activate();
         void deactivate();
         void set_flat_color(ALLEGRO_COLOR flat_color={});
         void set_texture_width(int width=1);
         void set_texture_height(int height=1);
         void set_time(float time=1);
      };
   }
}



