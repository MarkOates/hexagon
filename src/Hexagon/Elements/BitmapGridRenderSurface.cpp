

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


