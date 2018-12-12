


#include <Hexagon/Font.hpp>



void Font::__destroy(Font *font)
{
   al_destroy_font(font->font);
   font->font = nullptr;
}



void Font::__create(Font *font)
{
   font->font = al_load_font(font->get_font_filename().c_str(), font->get_font_size(), 0);
}



Font::Font(int font_size, std::string font_filename)
   : font_size(font_size)
   , font_filename(font_filename)
   , font(nullptr)
{
   __create(this);
}



Font::~Font()
{
   al_destroy_font(font);
}



void Font::set_font_size(int font_size)
{
   al_destroy_font(font);
}



int Font::get_font_size()
{
   return font_size;
}



void Font::set_font_filename(std::string font_filename)
{
   if (this->font_filename == font_filename) return;

   this->font_filename = font_filename;
   __destroy(this);
   __create(this);
}



std::string Font::get_font_filename()
{
   return font_filename;
}



