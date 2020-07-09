

#include <Hexagon/Elements/TextMesh.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> TextMesh::dummy_grid = {};


TextMesh::TextMesh()
   : grid(get_dummy_grid_ref())
   , vertexes({})
   , num_columns(0)
   , num_rows(0)
   , cell_width(1.0f)
   , cell_height(1.0f)
   , bitmap(nullptr)
{
}


TextMesh::~TextMesh()
{
}


void TextMesh::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


std::vector<ALLEGRO_VERTEX> TextMesh::get_vertexes()
{
   return vertexes;
}


int TextMesh::get_num_columns()
{
   return num_columns;
}


int TextMesh::get_num_rows()
{
   return num_rows;
}


float TextMesh::get_cell_width()
{
   return cell_width;
}


float TextMesh::get_cell_height()
{
   return cell_height;
}


ALLEGRO_BITMAP* TextMesh::get_bitmap()
{
   return bitmap;
}


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &TextMesh::get_dummy_grid_ref()
{
   return dummy_grid;
}


bool TextMesh::resize(int num_columns, int num_rows, float cell_width, float cell_height)
{
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

void TextMesh::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "render" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *tile_atlas_bitmap = get_bitmap();
al_draw_prim(&vertexes[0], NULL, tile_atlas_bitmap, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
return;

}

float TextMesh::calculate_width()
{
return cell_width * num_columns;
}

float TextMesh::calculate_height()
{
return cell_height * num_rows;
}
} // namespace Elements
} // namespace Hexagon


