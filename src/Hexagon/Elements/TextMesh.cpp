

#include <Hexagon/Elements/TextMesh.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Elements
{


TextMesh::TextMesh(ALLEGRO_FONT* font, int num_columns, int num_rows)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , cell_width(1.0f)
   , cell_height(1.0f)
   , font_character_map_grid({font})
   , bitmap_grid_mesh({})
   , font_character_map_bitmap(nullptr)
   , font_character_uv_mapping({})
   , initialized(false)
{
}


TextMesh::~TextMesh()
{
}


int TextMesh::get_num_columns() const
{
   return num_columns;
}


int TextMesh::get_num_rows() const
{
   return num_rows;
}


float TextMesh::get_cell_width() const
{
   return cell_width;
}


float TextMesh::get_cell_height() const
{
   return cell_height;
}


Hexagon::Elements::BitmapGridMesh TextMesh::get_bitmap_grid_mesh() const
{
   return bitmap_grid_mesh;
}


ALLEGRO_BITMAP* TextMesh::get_font_character_map_bitmap() const
{
   return font_character_map_bitmap;
}


bool TextMesh::get_initialized() const
{
   return initialized;
}


void TextMesh::set_font(ALLEGRO_FONT* font)
{
   if (!(!initialized))
   {
      std::stringstream error_message;
      error_message << "[TextMesh::set_font]: error: guard \"!initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMesh::set_font: error: guard \"!initialized\" not met");
   }
   this->font = font;
   font_character_map_grid.set_font(font);
   return;
}

void TextMesh::initialize()
{
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[TextMesh::initialize]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMesh::initialize: error: guard \"font\" not met");
   }
   if (initialized) return;

   if (font_character_map_bitmap) al_destroy_bitmap(font_character_map_bitmap);
   font_character_uv_mapping.clear();
   cell_width = 1;
   cell_height = 1;
   font_character_map_grid.initialize();
   font_character_map_bitmap = font_character_map_grid.get_created_character_map_bitmap();
   font_character_uv_mapping = font_character_map_grid.get_character_uv_mapping();

   if (!font_character_map_bitmap) throw std::runtime_error("boobaz");
   if (!font_character_uv_mapping.size() == 256) throw std::runtime_error("foobar");

   bitmap_grid_mesh.set_bitmap(font_character_map_bitmap);
   cell_width = al_get_text_width(font, "W");
   cell_height = al_get_font_line_height(font);
   bitmap_grid_mesh.resize(num_columns, num_rows, cell_width, cell_height);

   initialized = true;
   return;
}

void TextMesh::destruct()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TextMesh::destruct]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMesh::destruct: error: guard \"initialized\" not met");
   }
   if (font_character_map_bitmap)
   {
      al_destroy_bitmap(font_character_map_bitmap);
      font_character_map_bitmap = nullptr;
   }
   initialized = false;
   return;
}

void TextMesh::set_cell_color(int x, int y, ALLEGRO_COLOR color)
{
   bitmap_grid_mesh.set_cell_color(x, y, color);
   return;
}

void TextMesh::set_cell_character(int x, int y, char character)
{
   // TODO: validate 'character' index exists in character_uv_mapping
   std::tuple<float, float, float, float> character_map = font_character_uv_mapping[character];
   bitmap_grid_mesh.set_cell_uv(x, y, character_map);
   return;
}

int TextMesh::calculate_width()
{
   return bitmap_grid_mesh.calculate_width();
}

int TextMesh::calculate_height()
{
   return bitmap_grid_mesh.calculate_height();
}

void TextMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TextMesh::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMesh::render: error: guard \"initialized\" not met");
   }
   bitmap_grid_mesh.render();
   return;
}

void TextMesh::render_only_select_cells(std::vector<std::pair<int, int>> cell_coordinates)
{
   bitmap_grid_mesh.render_only_select_cells(cell_coordinates);
   return;
}


} // namespace Elements
} // namespace Hexagon


