#pragma once


#include <allegro5/allegro.h>
#include <allegro_flare/vec3d.h>


namespace Hexagon
{
   class Camera
   {
   private:
      float x;
      float y;
      float z;
      vec3d position;
      vec3d stepback;
      vec3d rotation;
      float tilt;
      float zoom_min;
      float zoom_max;
      float zoom_pos;

   public:
      Camera(float x=0, float y=0, float z=0);
      ~Camera();

      void set45_isometric();
      void setup_camera_perspective(ALLEGRO_BITMAP* bmp=nullptr);
   };
}



