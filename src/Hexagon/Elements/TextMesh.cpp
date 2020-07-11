

#include <Hexagon/Elements/TextMesh.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextMesh::TextMesh(ALLEGRO_FONT* font, int num_columns, int num_rows)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , font_character_map_grid({font})
   , mesh({})
   , character_map_bitmap(nullptr)
   , character_uv_mapping({})
   , initialized(false)
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

//mesh.set_cell_uv();
ALLEGRO_BITMAP *font_character_map_bitmap = font_character_map_grid.create();
character_uv_mapping = font_character_map_grid.get_character_uv_mapping();

mesh.resize(num_columns, num_rows);
mesh.set_bitmap(font_character_map_bitmap);

initialized = true;
return;

}

void TextMesh::set_cell_background_color(int x, int y, ALLEGRO_COLOR color)
{
mesh.set_cell_color(x, y, color);
return;

}

void TextMesh::set_cell_character(int x, int y, char character)
{
// TODO: validate 'character' index exists in character_uv_mapping
std::tuple<float, float, float, float> character_map = character_uv_mapping[character];
mesh.set_cell_uv(x, y, character_map);
// update the
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
mesh.render();
return;

}
} // namespace Elements
} // namespace Hexagon


