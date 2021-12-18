

#include <Hexagon/Camera.hpp>



namespace Hexagon
{


Camera::Camera(float x, float y, float z)
   : x(x)
   , y(y)
   , z(z)
   , position(x, y, z)
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


vec3d Camera::get_position()
{
   return position;
}


vec3d Camera::get_stepback()
{
   return stepback;
}


vec3d Camera::get_rotation()
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


void Camera::setup_camera_perspective(ALLEGRO_BITMAP* bmp)
{
   vec3d stepback_with_stepback_baseline = stepback + vec3d(0, 0, 600);
   //rotation = vec3d(-TAU/8.0, TAU/16.0, 0) * 0.1;

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

   //al_perspective_transform(&p, -1, aspect_ratio, 1, 1, -aspect_ratio, 1000);
   float znear = 5;
   float zoom = (zoom_max - zoom_min) * zoom_pos + zoom_min; // 4 is closeup, 10 is wide
   stepback_with_stepback_baseline = vec3d(0, znear*zoom, znear*zoom);

   float viewport_scale = 200.0;
   //al_perspective_transform(&p,      -1, aspect_ratio, znear,      1, -aspect_ratio, 1000);
   //al_perspective_transform(&p, -1 * viewport_scale, -aspect_ratio * viewport_scale, znear, 1 * viewport_scale, aspect_ratio * viewport_scale, 1000);
   al_perspective_transform(&p, -1 * viewport_scale, -aspect_ratio * viewport_scale, znear * viewport_scale, 1 * viewport_scale, aspect_ratio * viewport_scale, 1000 * viewport_scale);
   //al_orthographic_transform(&p, -1 * viewport_scale, -aspect_ratio * viewport_scale, znear * viewport_scale, 1 * viewport_scale, aspect_ratio * viewport_scale, 1000 * viewport_scale);

   //float viewport_scale = 1;
   //al_orthographic_transform(&p, -1 * viewport_scale, aspect_ratio * viewport_scale, znear, 1 * viewport_scale, -aspect_ratio * viewport_scale, 1000);

   al_scale_transform_3d(&p, 0.1, 0.1, 0.1);
   al_use_projection_transform(&p);

   //al_scale_transform_3d(&p, 0.5, 0.5, 0.5);

   al_use_transform(al_get_current_transform());
   //al_set_render_state(ALLEGRO_DEPTH_TEST, 1);

   return;
}
} // namespace Hexagon


