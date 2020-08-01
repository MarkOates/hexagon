

#include <Hexagon/Elements/FontedTextGrid.hpp>



namespace Hexagon
{
namespace Elements
{


FontedTextGrid::FontedTextGrid(ALLEGRO_FONT* font, int num_columns, int num_rows)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , sub_bitmap_character_map({})
   , bitmap_grid_render_surface(num_columns, num_rows)
   , initialized(false)
{
}


FontedTextGrid::~FontedTextGrid()
{
}


void FontedTextGrid::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


std::string FontedTextGrid::run()
{
return "Hello World!";
}

void FontedTextGrid::initialize()
{
//-> font
int num_columns = 123;
int num_rows = 74;


// Setup dependencies

//Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map(font);
sub_bitmap_character_map.initialize();


// Setup self

Hexagon::Elements::BitmapGridRenderSurface bitmap_grid_render_surface(
   num_columns,
   num_rows,
   sub_bitmap_character_map.get_grid_width(),
   sub_bitmap_character_map.get_grid_height()
);
bitmap_grid_render_surface.initialize();

initialized = true;
return;


// Use

for (unsigned y=0; y<num_rows; y++)
{
   for (unsigned x=0; x<num_columns; x++)
   {
      ALLEGRO_BITMAP *bitmap_to_draw = sub_bitmap_character_map.find_sub_bitmap('A');
      bitmap_grid_render_surface.draw_to_cell(bitmap_to_draw, ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f}, x, y);
   }
}


// For drawing

ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();
al_draw_bitmap(surface, 0, 0, 0);

}
} // namespace Elements
} // namespace Hexagon


