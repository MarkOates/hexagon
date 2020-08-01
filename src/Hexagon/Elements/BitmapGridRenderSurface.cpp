

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

ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

if (surface) al_destroy_bitmap(surface);
if (!surface) surface = al_create_bitmap(num_columns * cell_width, num_rows * cell_height);
al_set_target_bitmap(surface);
al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});

al_restore_state(&previous_render_state);

initialized = true;
return;

}

void BitmapGridRenderSurface::destroy()
{
if (surface) al_destroy_bitmap(surface);
return;

}
} // namespace Elements
} // namespace Hexagon


