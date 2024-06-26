

#include <Hexagon/Elements/BitmapGridRenderSurface.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , cell_sub_bitmaps({})
   , initialized(false)
   , previous_render_state()
{
}


BitmapGridRenderSurface::~BitmapGridRenderSurface()
{
}


ALLEGRO_BITMAP* BitmapGridRenderSurface::get_surface() const
{
   return surface;
}


bool BitmapGridRenderSurface::get_initialized() const
{
   return initialized;
}


void BitmapGridRenderSurface::set_cell_width(int cell_width)
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::set_cell_width]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::set_cell_width]: error: guard \"(!get_initialized())\" not met");
   }
   this->cell_width = cell_width;
   return;
}

void BitmapGridRenderSurface::set_cell_height(int cell_height)
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::set_cell_height]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::set_cell_height]: error: guard \"(!get_initialized())\" not met");
   }
   this->cell_height = cell_height;
   return;
}

void BitmapGridRenderSurface::lock_for_render()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::lock_for_render]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::lock_for_render]: error: guard \"get_initialized()\" not met");
   }
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
   al_set_target_bitmap(surface);
   al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
   return;
}

void BitmapGridRenderSurface::unlock_for_render()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::unlock_for_render]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::unlock_for_render]: error: guard \"get_initialized()\" not met");
   }
   al_restore_state(&previous_render_state);
   return;
}

void BitmapGridRenderSurface::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (initialized) return;

   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

   if (surface)
   {
      for (auto &cell_sub_bitmap : cell_sub_bitmaps) al_destroy_bitmap(cell_sub_bitmap);
      al_destroy_bitmap(surface);
      cell_sub_bitmaps.clear();
      surface = nullptr;
   }

   if (!surface)
   {
      surface = al_create_bitmap(num_columns * cell_width, num_rows * cell_height);
      cell_sub_bitmaps.resize(num_columns * num_rows);
      for (unsigned y=0; y<num_rows; y++)
      {
         for (unsigned x=0; x<num_columns; x++)
         {
            ALLEGRO_BITMAP *cell_sub_bitmap =
              al_create_sub_bitmap(surface, x*cell_width, y*cell_height, cell_width, cell_height);
            cell_sub_bitmaps[x + y*num_columns] = cell_sub_bitmap;
         }
      }
   }
   al_set_target_bitmap(surface);
   al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});

   al_restore_state(&previous_render_state);

   initialized = true;
   return;
}

void BitmapGridRenderSurface::draw_to_cell(ALLEGRO_BITMAP* bitmap_to_draw, ALLEGRO_COLOR tint, int x, int y)
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::draw_to_cell]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::draw_to_cell]: error: guard \"get_initialized()\" not met");
   }
   if (!(bitmap_to_draw))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::BitmapGridRenderSurface::draw_to_cell]: error: guard \"bitmap_to_draw\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::BitmapGridRenderSurface::draw_to_cell]: error: guard \"bitmap_to_draw\" not met");
   }
   al_draw_tinted_bitmap(bitmap_to_draw, tint, x*cell_width, y*cell_height, 0);

   return;
}

ALLEGRO_BITMAP* BitmapGridRenderSurface::find_sub_bitmap(int x, int y)
{
   if (x < 0) return nullptr;
   if (y < 0) return nullptr;
   if (x >= num_columns) return nullptr;
   if (y >= num_rows) return nullptr;
   return cell_sub_bitmaps[x + y*num_columns];
}

void BitmapGridRenderSurface::destroy()
{
   for (auto &cell_sub_bitmap : cell_sub_bitmaps) { if (cell_sub_bitmap) al_destroy_bitmap(cell_sub_bitmap); }
   cell_sub_bitmaps.clear();
   if (surface) al_destroy_bitmap(surface);
   return;
}


} // namespace Elements
} // namespace Hexagon


