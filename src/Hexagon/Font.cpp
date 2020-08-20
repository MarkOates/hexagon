

#include <Hexagon/Font.hpp>



namespace Hexagon
{


Font::Font()
   : font_bin(nullptr)
   , font_filename("Consolas.ttf")
   , font_size(-16)
{
}


Font::~Font()
{
}


void Font::set_font_filename(std::string font_filename)
{
   this->font_filename = font_filename;
}


void Font::set_font_size(int font_size)
{
   this->font_size = font_size;
}


std::string Font::get_font_filename()
{
   return font_filename;
}


int Font::get_font_size()
{
   return font_size;
}


} // namespace Hexagon


