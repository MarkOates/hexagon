

#include <Hexagon/Elements/TextMesh.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


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
   , mesh({})
   , font_character_map_bitmap(nullptr)
   , font_character_uv_mapping({})
   , initialized(false)
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


Hexagon::Elements::BitmapGridMesh TextMesh::get_mesh()
{
   return mesh;
}


ALLEGRO_BITMAP* TextMesh::get_font_character_map_bitmap()
{
   return font_character_map_bitmap;
}


bool TextMesh::get_initialized()
{
   return initialized;
}


void TextMesh::set_font(ALLEGRO_FONT* font)
{
if (!(!initialized))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "set_font" << ": error: " << "guard \"!initialized\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "TextMesh" << "::" << "initialize" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (initialized) return;

if (font_character_map_bitmap) al_destroy_bitmap(font_character_map_bitmap);
font_character_uv_mapping.clear();
cell_width = 1;
cell_height = 1;
font_character_map_bitmap = font_character_map_grid.create();
font_character_uv_mapping = font_character_map_grid.get_character_uv_mapping();

if (!font_character_map_bitmap) throw std::runtime_error("boobaz");
if (!font_character_uv_mapping.size() == 256) throw std::runtime_error("foobar");

mesh.set_bitmap(font_character_map_bitmap);
cell_width = al_get_text_width(font, "W");
cell_height = al_get_font_line_height(font);
mesh.resize(num_columns, num_rows, cell_width, cell_height);

initialized = true;
return;

}

void TextMesh::destruct()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "destruct" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
if (font_character_map_bitmap) al_destroy_bitmap(font_character_map_bitmap);
return;

}

void TextMesh::set_cell_color(int x, int y, ALLEGRO_COLOR color)
{
mesh.set_cell_color(x, y, color);
return;

}

void TextMesh::set_cell_character(int x, int y, char character)
{
// TODO: validate 'character' index exists in character_uv_mapping
std::tuple<float, float, float, float> character_map = font_character_uv_mapping[character];
mesh.set_cell_uv(x, y, character_map);
return;

}

int TextMesh::calculate_width()
{
return mesh.calculate_width();

}

int TextMesh::calculate_height()
{
return mesh.calculate_height();

}

void TextMesh::render()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TextMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
mesh.render();
return;

}
} // namespace Elements
} // namespace Hexagon


