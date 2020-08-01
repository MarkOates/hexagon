

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>



namespace Hexagon
{
namespace Elements
{


BitmapGridRenderSurface::BitmapGridRenderSurface(int num_columns, int num_rows, int cell_width, int cell_height)
   : num_columns(num_columns)
   , num_rows(num_rows)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , surface(nullptr)
   , initialized(false)
{
}


BitmapGridRenderSurface::~BitmapGridRenderSurface()
{
}


ALLEGRO_BITMAP* BitmapGridRenderSurface::get_surface()
{
   return surface;
}


bool BitmapGridRenderSurface::get_initialized()
{
   return initialized;
}


void BitmapGridRenderSurface::initialize()
{
if (initialized) return;
return;

}
} // namespace Elements
} // namespace Hexagon


