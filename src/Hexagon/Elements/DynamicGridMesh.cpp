

#include <Hexagon/Elements/DynamicGridMesh.hpp>



namespace Hexagon
{
namespace Elements
{


DynamicGridMesh::DynamicGridMesh(ALLEGRO_BITMAP* texture)
   : vertexes({})
   , texture(texture)
{
}


DynamicGridMesh::~DynamicGridMesh()
{
}


void DynamicGridMesh::set_texture(ALLEGRO_BITMAP* texture)
{
   this->texture = texture;
}


std::vector<ALLEGRO_VERTEX> DynamicGridMesh::get_vertexes()
{
   return vertexes;
}


ALLEGRO_BITMAP* DynamicGridMesh::get_texture()
{
   return texture;
}


void DynamicGridMesh::set_or_create_cell()
{
return;
}

void DynamicGridMesh::delete_cell()
{
return;
}

void DynamicGridMesh::render()
{
al_draw_prim(
   &vertexes[0],
   nullptr,
   texture,
   0,
   vertexes.size(),
   ALLEGRO_PRIM_TRIANGLE_LIST
);
return;

}
} // namespace Elements
} // namespace Hexagon


