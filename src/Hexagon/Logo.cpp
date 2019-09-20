

#include <Hexagon/Logo.hpp>
#include <cmath>
#include <allegro_flare/path2d.h>


namespace Hexagon
{


Logo::Logo(float x, float y, float radius, ALLEGRO_FONT* font, ALLEGRO_COLOR color, float thickness)
   : x(x)
   , y(y)
   , radius(radius)
   , font(font)
   , color(color)
   , thickness(thickness)
{
}


Logo::~Logo()
{
}


ALLEGRO_COLOR Logo::default_color()
{
ALLEGRO_COLOR c;
c.r = 188/255.0f;
c.g = 45/255.0f;
c.b = 72/255.0f;
c.a = 1.0;
return c;

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

al_draw_text(font, color, x, y + radius*1.3, ALLEGRO_ALIGN_CENTER, "H E X A G O N");

}
} // namespace Hexagon


