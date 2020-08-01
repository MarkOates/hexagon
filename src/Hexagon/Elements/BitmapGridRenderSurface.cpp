

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


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
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "BitmapGridRenderSurface" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
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

void BitmapGridRenderSurface::draw_to_surface(ALLEGRO_BITMAP* bitmap, int x, int y)
{
if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "BitmapGridRenderSurface" << "::" << "draw_to_surface" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

// TODO
//al_set_target_bitmap(surface);

al_restore_state(&previous_render_state);
return;

}

void BitmapGridRenderSurface::destroy()
{
if (surface) al_destroy_bitmap(surface);
return;

}
} // namespace Elements
} // namespace Hexagon


