#pragma once


#include <Hexagon/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Shaders
   {
      class TexturedTruchet : private Hexagon::Shaders::Base
      {
      private:
         bool initialized;

      public:
         TexturedTruchet();
         ~TexturedTruchet();

         void initialize();
         void activate();
         void deactivate();
         void set_flat_color(ALLEGRO_COLOR flat_color={});
         void set_texture_width(int width=1);
         void set_texture_height(int height=1);
         void set_nyan_cat_texture(ALLEGRO_BITMAP* nyan_cat_texture=nullptr);
         void set_time(float time=1);
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}



