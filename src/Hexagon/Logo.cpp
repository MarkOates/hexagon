

#include <Hexagon/Logo.hpp>

#include <allegro_flare/path2d.h>
#include <cmath>


namespace Hexagon
{


Logo::Logo(float x, float y, float radius, ALLEGRO_COLOR color, float thickness)
   : x(x)
   , y(y)
   , radius(radius)
   , color(color)
   , thickness(thickness)
{
}


void Logo::render()
{
   float h_radius = radius/2;
   float sqrt_h_radius = sqrt(3)/2 * radius;

   path2d path;

   path.add_point(radius, 0);
   path.add_point(h_radius, sqrt_h_radius);
   path.add_point(-h_radius, sqrt_h_radius);
   path.add_point(-radius, 0);
   path.add_point(-h_radius, -sqrt_h_radius);
   path.add_point(h_radius, -sqrt_h_radius);
   path.add_point(radius, 0);

   path.draw_outline(x, y, color, thickness);
}


};


