

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
   int &v = vertex_start;

   // set the XY coordinates for the vertexes in the cell
   //long tile_num = v / 6;

   int x1 = x * cell_width; //(tile_num % num_columns);
   int y1 = y * cell_height; //(tile_num / num_columns);
   int x2 = x1 + cell_width;
   int y2 = y1 + cell_height;

   // set the x/y coordinates for the vertexes
   vertexes[v+0].x = x1;
   vertexes[v+0].y = y1;
   vertexes[v+1].x = x1;
   vertexes[v+1].y = y2;
   vertexes[v+2].x = x2;
   vertexes[v+2].y = y2;
   vertexes[v+3].x = x2;
   vertexes[v+3].y = y2;
   vertexes[v+4].x = x2;
   vertexes[v+4].y = y1;
   vertexes[v+5].x = x1;
   vertexes[v+5].y = y1;

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


