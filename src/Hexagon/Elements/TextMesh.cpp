

#include <Hexagon/Elements/TextMesh.hpp>



namespace Hexagon
{
namespace Elements
{


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> TextMesh::dummy_grid = {};


TextMesh::TextMesh(std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& grid)
   : grid(grid)
{
}


TextMesh::~TextMesh()
{
}


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &TextMesh::get_dummy_grid_ref()
{
   return dummy_grid;
}


std::string TextMesh::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


