

#include <Hexagon/FontSet.hpp>

#include <sstream>


namespace Hexagon
{


AllegroFlare::FontBin FontSet::dummy_font_bin = {};


FontSet::FontSet(AllegroFlare::FontBin& fonts, std::map<std::string, std::string> font_dictionary)
   : fonts(fonts)
   , font_dictionary(font_dictionary)
{
}


FontSet::~FontSet()
{
}


void FontSet::set_font_dictionary(std::map<std::string, std::string> font_dictionary)
{
   this->font_dictionary = font_dictionary;
}


AllegroFlare::FontBin& FontSet::get_dummy_font_bin()
{
   return dummy_font_bin;
}

ALLEGRO_FONT* FontSet::obtain_font(std::string identifier)
{
   if (font_dictionary.find(identifier) == font_dictionary.end())
   {
      std::stringstream error_message;
      error_message << "[FontSet::obtain_font error]: can not obtain font \""
        << identifier
        << "\" it does not exist in the dictionary."
        << std::endl;
      throw std::runtime_error(error_message.str());
   }

   return fonts[font_dictionary[identifier]];
}


} // namespace Hexagon


