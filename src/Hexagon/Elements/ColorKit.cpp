

#include <Hexagon/Elements/ColorKit.hpp>



namespace Hexagon
{
namespace Elements
{


ColorKit::ColorKit()
{
}


ColorKit::~ColorKit()
{
}


ALLEGRO_COLOR ColorKit::black()
{
   return ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f};
}
} // namespace Elements
} // namespace Hexagon


