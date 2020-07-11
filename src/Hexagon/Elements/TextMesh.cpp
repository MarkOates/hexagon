

#include <Hexagon/Elements/TextMesh.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextMesh::TextMesh(ALLEGRO_FONT* font)
   : font(font)
   , num_columns(0)
   , num_rows(0)
   , font_character_map_grid({font})
   , bitmap_grid_mesh({})
   , character_map_bitmap(nullptr)
   , character_uv_mapping({})
   , initialized(false)
{
}


TextMesh::~TextMesh()
{
}


void TextMesh::set_cell_background_color(int x, int y, ALLEGRO_COLOR color)
{
return;

}

void TextMesh::initialize()
{
if (!(font))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "initialize" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (initialized) return;

//bitmap_grid_mesh.set_cell_uv();
ALLEGRO_BITMAP *font_character_map_bitmap = font_character_map_grid.create();
character_uv_mapping = font_character_map_grid.get_character_uv_mapping();

bitmap_grid_mesh.resize(num_columns, num_rows);
bitmap_grid_mesh.set_bitmap(font_character_map_bitmap);

initialized = true;
return;

}

void TextMesh::render()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bitmap_grid_mesh.render();
return;

}
} // namespace Elements
} // namespace Hexagon


