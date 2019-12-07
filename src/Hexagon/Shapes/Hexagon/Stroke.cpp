

#include <Hexagon/Shapes/Hexagon/Stroke.hpp>



namespace Hexagon
{
namespace Shapes
{
namespace Hexagon
{


Stroke::Stroke(float start, float end, ALLEGRO_COLOR color, float thickness)
   : start(start)
   , end(end)
   , color(color)
   , thickness(thickness)
{
}


Stroke::~Stroke()
{
}


float Stroke::get_start()
{
   return start;
}


float Stroke::get_end()
{
   return end;
}


ALLEGRO_COLOR Stroke::get_color()
{
   return color;
}


float Stroke::get_thickness()
{
   return thickness;
}


ALLEGRO_COLOR Stroke::default_color()
{
ALLEGRO_COLOR c;
c.r = 188/255.0f;
c.g = 45/255.0f;
c.b = 72/255.0f;
c.a = 1.0;
return c;

}
} // namespace Hexagon
} // namespace Shapes
} // namespace Hexagon


