

#include <Hexagon/Font.hpp>

#include <sstream>
#include <stdexcept>


namespace Hexagon
{


Font::Font(AllegroFlare::FontBin* font_bin, std::string font_filename, int font_size)
   : font_bin(font_bin)
   , font_filename(font_filename)
   , font_size(font_size)
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


std::string Font::get_font_filename() const
{
   return font_filename;
}


int Font::get_font_size() const
{
   return font_size;
}


void Font::increase_font_size()
{
   font_size--;
}

void Font::decrease_font_size()
{
   font_size++;
   if (font_size < 0) font_size = 0;
}

ALLEGRO_FONT* Font::al_font()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Font" << "::" << "al_font" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Font" << "::" << "al_font" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Font" << "::" << "al_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get(font_filename + " " + std::to_string(font_size));
}


} // namespace Hexagon


