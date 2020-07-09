

#include <Hexagon/Elements/TextMesh.hpp>



namespace Hexagon
{
namespace Elements
{


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> TextMesh::dummy_grid = {};


TextMesh::TextMesh()
   : grid(get_dummy_grid_ref())
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
//std::vector<ALLEGRO_VERTEX> vertexes;
//al_draw_prim(&vertexes[0], NULL, tile_atlas->bitmap, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
return;

}
} // namespace Elements
} // namespace Hexagon


