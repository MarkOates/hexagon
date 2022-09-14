

#include <Hexagon/Camera.hpp>

#include <cmath>
#include <sstream>
#include <stdexcept>


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

void Camera::setup_dimentional_projection(ALLEGRO_BITMAP* bitmap)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Camera" << "::" << "setup_dimentional_projection" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "Camera" << "::" << "setup_dimentional_projection" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
   // The goal here is to setup a projection transform that behaves as if normal 2D pixels were drawn for z=0
   // (i.e. as with the normal orthographic transform set up by Allegro), but allows some perspective effects for
   // rotating widgets around the X and Y axes.

   //float w = al_get_display_width(al_get_current_display()), h = al_get_display_height(al_get_current_display());
   float w = 1920, h = 1080;
   float fov_angle = 90.0;
   float fov = tan(fov_angle * ALLEGRO_PI / 180.0 / 2.0);

   // That is the z near plane where we need to draw everything before the perspective transform so that it ends up
   // as 1:1 at pixel-coordingates.
   float z_near = w / 2 * fov;

   // If we really drew at depth of z_near, everything closer to the camera would be z-clipped.
   // This would be a problem for rotations around the x and y axis.
   // Therefore, to avoid z-clipping, we need to move everything further away from the camera before the perspective
   // transform is applied.
   // This is achieved by an additional view matrix which is composed with the perspective transform so that the view
   // transformation happens first.
   const float Z_DIST_FACTOR = 1.1; // larger number makes a deeper distance effect

   ALLEGRO_TRANSFORM perspective;
   al_identity_transform(&perspective);
   // FIXME: Does factor 2 for "far" make sense?
   al_perspective_transform(&perspective, -w / 2, -h / 2, z_near, w / 2, h / 2, z_near * Z_DIST_FACTOR * 2);

   ALLEGRO_TRANSFORM view;
   al_identity_transform(&view);
   // We make up for the perspective correction due to z-translation by scaling everything.
   al_scale_transform(&view, Z_DIST_FACTOR, Z_DIST_FACTOR);
   // Move away from the camera (and center).
   al_translate_transform_3d(&view, -w / 2 * Z_DIST_FACTOR, -h / 2 * Z_DIST_FACTOR, -z_near * Z_DIST_FACTOR);

   al_compose_transform(&view, &perspective);

   ALLEGRO_STATE previous_bitmap_target_state;
   al_store_state(&previous_bitmap_target_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);
   al_use_projection_transform(&view);
   al_restore_state(&previous_bitmap_target_state);
   return;
}


} // namespace Hexagon


