

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
{
}


TextMesh::~TextMesh()
{
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


std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &TextMesh::get_dummy_grid_ref()
{
   return dummy_grid;
}


bool TextMesh::resize(int num_columns, int num_rows, float cell_width, float cell_height)
{
vertexes.clear();
vertexes.resize(num_columns*num_rows*6); // 6 vertexes per rectangle
this->num_columns = num_columns;
this->num_rows = num_rows;
this->cell_width = cell_width;
this->cell_height = cell_height;

}

void TextMesh::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *tile_atlas_bitmap = nullptr;
al_draw_prim(&vertexes[0], NULL, tile_atlas_bitmap, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
return;

}
} // namespace Elements
} // namespace Hexagon


