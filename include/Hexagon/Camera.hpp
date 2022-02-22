#pragma once


#include <allegro5/allegro.h>
#include <allegro_flare/vec3d.h>


namespace Hexagon
{
   class Camera
   {
   private:
      vec3d position;
      vec3d stepback;
      vec3d rotation;
      float tilt;
      float zoom_min;
      float zoom_max;
      float zoom_pos;

   public:
      Camera();
      ~Camera();

      vec3d get_position();
      vec3d get_stepback();
      vec3d get_rotation();
      vec3d &get_position_ref();
      vec3d &get_stepback_ref();
      vec3d &get_rotation_ref();
      void setup_camera_perspective(ALLEGRO_BITMAP* bmp=nullptr, float znear=5.0f, float stepback_baseline_z=600.0f, float viewport_scale=200.0f, float final_scale_multiplier=0.1f);
   };
}



