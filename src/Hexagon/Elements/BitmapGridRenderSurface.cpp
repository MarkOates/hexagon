

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>



namespace Hexagon
{
namespace Elements
{


BitmapGridRenderSurface::BitmapGridRenderSurface()
   : surface(nullptr)
{
}


BitmapGridRenderSurface::~BitmapGridRenderSurface()
{
}


ALLEGRO_BITMAP* BitmapGridRenderSurface::get_surface()
{
   return surface;
}


std::string BitmapGridRenderSurface::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


