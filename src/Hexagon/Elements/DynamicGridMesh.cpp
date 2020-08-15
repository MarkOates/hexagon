

#include <Hexagon/Elements/DynamicGridMesh.hpp>



namespace Hexagon
{
namespace Elements
{


DynamicGridMesh::DynamicGridMesh()
   : vertexes({})
{
}


DynamicGridMesh::~DynamicGridMesh()
{
}


std::vector<ALLEGRO_VERTEX> DynamicGridMesh::get_vertexes()
{
   return vertexes;
}


std::string DynamicGridMesh::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


