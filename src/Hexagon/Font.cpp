

#include <Hexagon/Font.hpp>



namespace Hexagon
{


Font::Font()
   : font_bin(nullptr)
   , font_filename("Consolas.ttf")
{
}


Font::~Font()
{
}


void Font::set_font_filename(std::string font_filename)
{
   this->font_filename = font_filename;
}


std::string Font::get_font_filename()
{
   return font_filename;
}


} // namespace Hexagon


