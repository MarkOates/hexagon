

#include <Hexagon/Elements/TextMesh.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextMesh::TextMesh(ALLEGRO_FONT* font)
   : font(font)
   , font_character_map_grid({font})
   , bitmap_grid_mesh({})
   , character_map_bitmap(nullptr)
   , character_uv_mapping({})
   , initialized(true)
{
}


TextMesh::~TextMesh()
{
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

bitmap_grid_mesh.set_cell_uv();
ALLEGRO_BITMAP *font_character_map_bitmap = font_character_map_grid.create();
character_uv_mapping = font_character_map_grid.get_character_uv_mapping();

initialized = true;
return;

}
} // namespace Elements
} // namespace Hexagon


