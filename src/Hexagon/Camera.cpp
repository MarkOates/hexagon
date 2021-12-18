

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


void Camera::set45_isometric()
{
   return;
}

void Camera::setup_camera_perspective(ALLEGRO_BITMAP* bmp)
{
   return;
}
} // namespace Hexagon


