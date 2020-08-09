

#include <Hexagon/Elements/BitmapGridMesh.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> BitmapGridMesh::dummy_grid = {};


BitmapGridMesh::BitmapGridMesh()
   : grid(get_dummy_grid_ref())
   , vertexes({})
   , num_columns(0)
   , num_rows(0)
   , cell_width(1.0f)
   , cell_height(1.0f)
   , clip_start_y(0)
   , clip_length_y(-1)
   , bitmap(nullptr)
{
}


BitmapGridMesh::~BitmapGridMesh()
{
}


void BitmapGridMesh::set_clip_start_y(int clip_start_y)
{
   this->clip_start_y = clip_start_y;
}


void BitmapGridMesh::set_clip_length_y(int clip_length_y)
{
   this->clip_length_y = clip_length_y;
}


void BitmapGridMesh::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& BitmapGridMesh::get_grid()
{
   return grid;
}


std::vector<ALLEGRO_VERTEX> BitmapGridMesh::get_vertexes()
{
   return vertexes;
}


int BitmapGridMesh::get_num_columns()
{
   return num_columns;
}


int BitmapGridMesh::get_num_rows()
{
   return num_rows;
}


float BitmapGridMesh::get_cell_width()
{
   return cell_width;
}


float BitmapGridMesh::get_cell_height()
{
   return cell_height;
}


int BitmapGridMesh::get_clip_start_y()
{
   return clip_start_y;
}


int BitmapGridMesh::get_clip_length_y()
{
   return clip_length_y;
}


ALLEGRO_BITMAP* BitmapGridMesh::get_bitmap()
{
   return bitmap;
}


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &BitmapGridMesh::get_dummy_grid_ref()
{
   return dummy_grid;
}


void BitmapGridMesh::set_cell_uv(int x, int y, std::tuple<float, float, float, float> uv_coords)
{
std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>* cell = find_cell(x, y);
if (!cell) throw std::runtime_error("set_cell_uv: cell not found");

int vertex_start = (x + y * num_columns) * 6;

float &u1 = std::get<0>(uv_coords);
float &v1 = std::get<1>(uv_coords);
float &u2 = std::get<2>(uv_coords);
float &v2 = std::get<3>(uv_coords);

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

void BitmapGridMesh::set_cell_color(int x, int y, ALLEGRO_COLOR color)
{
// set the cell in the grid
std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>* cell = find_cell(x, y);
if (!cell) throw std::runtime_error("cell not found");
std::get<2>(*cell) = color;

// set the vertexes in the mesh
int vertex_start = (x + y * num_columns) * 6;
vertexes[vertex_start+0].color = color;
vertexes[vertex_start+1].color = color;
vertexes[vertex_start+2].color = color;
vertexes[vertex_start+3].color = color;
vertexes[vertex_start+4].color = color;
vertexes[vertex_start+5].color = color;

}

bool BitmapGridMesh::resize(int num_columns, int num_rows, float cell_width, float cell_height)
{
// resize the grid
grid.clear();
std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR> default_grid_cell =
   std::make_tuple('-', ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR{0.2f, 0.2f, 0.2f, 0.2f});
for (unsigned y=0; y<num_rows; y++)
{
   grid.push_back({});
   std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>> &row = grid.back();
   for (unsigned x=0; x<num_columns; x++)
   {
      row.push_back(default_grid_cell);
   }
}

// resize the vertexes
int num_vertexes = num_columns * num_rows * 6;
vertexes.clear();
vertexes.resize(num_vertexes); // 6 vertexes per rectangle
this->num_columns = num_columns;
this->num_rows = num_rows;
this->cell_width = cell_width;
this->cell_height = cell_height;

int v = 0;
for (; v<num_vertexes; v+=6)
{
   long tile_num = v / 6;

   int x1 = (tile_num % num_columns);
   int y1 = (tile_num / num_columns);
   int x2 = x1 + 1;
   int y2 = y1 + 1;

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
}

v = 0;
for (; v<num_vertexes; v++)
{
   vertexes[v].x *= cell_width;
   vertexes[v].y *= cell_height;
   vertexes[v].z = 0;
   vertexes[v].color = al_map_rgba_f(1, 1, 1, 1);
}

}

void BitmapGridMesh::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "BitmapGridMesh" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "BitmapGridMesh" << "::" << "render" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
if (clip_length_y == 0) return;

ALLEGRO_BITMAP *tile_atlas_bitmap = get_bitmap();
int num_vertexes_in_line = num_columns * 6;

int start_vertex = clip_start_y * num_vertexes_in_line;
int one_past_the_last_vertex = (clip_length_y > 0) ? (clip_length_y * num_vertexes_in_line) : vertexes.size();

al_draw_prim(
   &vertexes[0],
   NULL,
   tile_atlas_bitmap,
   start_vertex,
   one_past_the_last_vertex,
   ALLEGRO_PRIM_TRIANGLE_LIST
);

return;

}

void BitmapGridMesh::render_only_select_cells(std::vector<std::pair<int, int>> cell_coordinates)
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "BitmapGridMesh" << "::" << "render_only_select_cells" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "BitmapGridMesh" << "::" << "render_only_select_cells" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *tile_atlas_bitmap = get_bitmap();
int indices_per_cell = 6;
std::vector<int> indices(cell_coordinates.size() * indices_per_cell);

int i=0;
for (auto &cell_coordinate : cell_coordinates)
{
   int &x = cell_coordinate.first;
   int &y = cell_coordinate.second;

   if (y < 0 || y >= grid.size()) continue;
   if (x < 0 || x >= grid[y].size()) continue;

   int start_index_for_this_cell = (x + y * num_columns) * indices_per_cell;
   indices[i+0] = start_index_for_this_cell + 0;
   indices[i+1] = start_index_for_this_cell + 1;
   indices[i+2] = start_index_for_this_cell + 2;
   indices[i+3] = start_index_for_this_cell + 3;
   indices[i+4] = start_index_for_this_cell + 4;
   indices[i+5] = start_index_for_this_cell + 5;

   i += indices_per_cell;
}

al_draw_indexed_prim(
   &vertexes[0],
   NULL,
   tile_atlas_bitmap,
   &indices[0],
   indices.size(),
   ALLEGRO_PRIM_TRIANGLE_LIST
);
return;

}

float BitmapGridMesh::calculate_width()
{
return cell_width * num_columns;
}

float BitmapGridMesh::calculate_height()
{
return cell_height * num_rows;
}

std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>* BitmapGridMesh::find_cell(int x, int y)
{
if (y < 0 || y >= grid.size()) return nullptr;
if (x < 0 || x >= grid[y].size()) return nullptr;
return &grid[y][x];

}
} // namespace Elements
} // namespace Hexagon


