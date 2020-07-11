

#include <Hexagon/Elements/TextMesh.hpp>



namespace Hexagon
{
namespace Elements
{


TextMesh::TextMesh(ALLEGRO_FONT* font)
   : font(font)
   , font_character_map_grid({})
   , bitmap_grid_mesh({})
{
}


TextMesh::~TextMesh()
{
}


std::string TextMesh::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


