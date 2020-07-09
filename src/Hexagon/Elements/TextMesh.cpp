

#include <Hexagon/Elements/TextMesh.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace Elements
{


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> TextMesh::dummy_grid = {};


TextMesh::TextMesh()
   : grid(get_dummy_grid_ref())
   , vertexes({})
{
}


TextMesh::~TextMesh()
{
}


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &TextMesh::get_dummy_grid_ref()
{
   return dummy_grid;
}


void TextMesh::render()
{
ALLEGRO_BITMAP *tile_atlas_bitmap = nullptr;
//al_draw_prim(&vertexes[0], NULL, tile_atlas_bitmap, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
return;

}
} // namespace Elements
} // namespace Hexagon


