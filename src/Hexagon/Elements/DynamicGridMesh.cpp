

#include <Hexagon/Elements/DynamicGridMesh.hpp>



namespace Hexagon
{
namespace Elements
{


DynamicGridMesh::DynamicGridMesh(int cell_width, int cell_height, ALLEGRO_BITMAP* texture)
   : vertexes({})
   , cell_width(cell_width)
   , cell_height(cell_height)
   , texture(texture)
   , cells({})
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


void DynamicGridMesh::create_or_set_cell(int x, int y, int u1, int v1, int u2, int v2, ALLEGRO_COLOR color)
{
int vertex_start = cells[std::tuple<int, int>(x, y)];

// set the UV coordinates for the vertexes in the cell
vertexes[vertex_start+0].u = u1;
vertexes[vertex_start+0].v = v1;
vertexes[vertex_start+1].u = u1;
vertexes[vertex_start+1].v = v2;
vertexes[vertex_start+2].u = u2;
vertexes[vertex_start+2].v = v2;
vertexes[vertex_start+3].u = u2;
vertexes[vertex_start+3].v = v2;
vertexes[vertex_start+4].u = u2;
vertexes[vertex_start+4].v = v1;
vertexes[vertex_start+5].u = u1;
vertexes[vertex_start+5].v = v1;

// set the vertexes in the mesh
vertexes[vertex_start+0].color = color;
vertexes[vertex_start+1].color = color;
vertexes[vertex_start+2].color = color;
vertexes[vertex_start+3].color = color;
vertexes[vertex_start+4].color = color;
vertexes[vertex_start+5].color = color;

return;

}

void DynamicGridMesh::delete_cell(int x, int y)
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


