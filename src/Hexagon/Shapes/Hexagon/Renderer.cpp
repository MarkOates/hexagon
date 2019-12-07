

#include <Hexagon/Shapes/Hexagon/Renderer.hpp>
#include <cmath>
#include <allegro_flare/vec2d.h>
#include <allegro_flare/path2d.h>


namespace Hexagon
{
namespace Shapes
{
namespace Hexagon
{


Renderer::Renderer(float x, float y, float radius, std::vector<Shapes::Hexagon::Stroke> strokes)
   : x(x)
   , y(y)
   , radius(radius)
   , strokes(strokes)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
float h_radius = radius/2;
float sqrt_h_radius = sqrt(3)/2 * radius;
float height = sqrt_h_radius;
float h_height = sqrt_h_radius/2;
float tq_radius = radius/4*3;

std::vector<vec2d> polar_coordinate_points = {
  { 0,         -height },   // 12 (or 0)
  { h_radius,  -height },   // 1
  { tq_radius,    -h_height }, // 2
  { radius,    0 },           // 3
  { tq_radius, h_height },  // 4
  { h_radius,   height },    // 5
  { 0,   height },    // 6
  { -h_radius,   height },    // 7
  { -tq_radius, h_height },  // 8
  { -radius,   0 },         // 9
  { -tq_radius,  -h_height }, // 10
  { -h_radius,  -height },   // 11
};

for (auto &stroke : strokes)
{
  path2d path;
  float start = stroke.get_start();
  float end = stroke.get_end();
  ALLEGRO_COLOR color = stroke.get_color();
  float thickness = stroke.get_thickness();

  while (end < start) end += 12;
  
  for (int i=start; i<=end; i++)
  {
    vec2d polar_coordinate = polar_coordinate_points[i % 12];
    vec2d point(polar_coordinate);
    path.add_point(point.x, point.y);
  }

  //path.add_point(radius, 0);                 // 3 o'clock
  //path.add_point(h_radius, sqrt_h_radius);   // 5 o'clock
  //path.add_point(-h_radius, sqrt_h_radius);  // 7 o'clock
  //path.add_point(-radius, 0);                // 9 o'clock
  //path.add_point(-h_radius, -sqrt_h_radius); // 11 o'clock
  //path.add_point(h_radius, -sqrt_h_radius);  // 1 o'clock
  //path.add_point(radius, 0);                 // 3 o'clock

  path.draw_outline(x, y, color, thickness);
}
return;

}
} // namespace Hexagon
} // namespace Shapes
} // namespace Hexagon


