

#include <Hexagon/Camera.hpp>



namespace Hexagon
{


Camera::Camera()
   : position(0, 0, 0)
   , stepback(0, 0, 0)
   , rotation(0, 0, 0)
   , tilt(0)
   , zoom_min(10)
   , zoom_max(4)
   , zoom_pos(0.5)
{
}


Camera::~Camera()
{
}


vec3d Camera::get_position() const
{
   return position;
}


vec3d Camera::get_stepback() const
{
   return stepback;
}


vec3d Camera::get_rotation() const
{
   return rotation;
}


vec3d &Camera::get_position_ref()
{
   return position;
}


vec3d &Camera::get_stepback_ref()
{
   return stepback;
}


vec3d &Camera::get_rotation_ref()
{
   return rotation;
}


void Camera::setup_camera_perspective(ALLEGRO_BITMAP* bmp, float znear, float stepback_baseline_z, float viewport_scale, float final_scale_multiplier)
{
   vec3d stepback_with_stepback_baseline = stepback + vec3d(0, 0, stepback_baseline_z);

   ALLEGRO_TRANSFORM p;
   float aspect_ratio = (float)al_get_bitmap_height(bmp) / al_get_bitmap_width(bmp);
   al_set_target_bitmap(bmp);
   al_identity_transform(&p);

   { // my camera translations go here
      // turn the camera right-left
      al_rotate_transform_3d(&p, 0, 1, 0, rotation.y);

      // position
      al_translate_transform_3d(&p,
         -position.x-stepback_with_stepback_baseline.x,
         -position.y-stepback_with_stepback_baseline.y,
         -position.z-stepback_with_stepback_baseline.z);

      // tilt the camera up-down
      al_rotate_transform_3d(&p, -1, 0, 0, rotation.x);
   }

   //float znear = 5;
   float zoom = (zoom_max - zoom_min) * zoom_pos + zoom_min; // 4 is closeup, 10 is wide
   stepback_with_stepback_baseline = vec3d(0, znear*zoom, znear*zoom);

   //float viewport_scale = 200.0;
   al_perspective_transform(
      &p,
      -1 * viewport_scale,
      -aspect_ratio * viewport_scale,
      znear * viewport_scale,
      1 * viewport_scale,
      aspect_ratio * viewport_scale,
      1000 * viewport_scale
   );

   al_scale_transform_3d(&p, final_scale_multiplier, final_scale_multiplier, final_scale_multiplier);
   al_use_projection_transform(&p);

   al_use_transform(al_get_current_transform());

   return;
}
} // namespace Hexagon


