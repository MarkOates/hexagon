

#include <Hexagon/FontSet.hpp>
#include <sstream>


namespace Hexagon
{


AllegroFlare::FontBin FontSet::dummy_font_bin = {};


FontSet::FontSet()
   : font_dictionary({})
   , fonts(get_dummy_font_bin())
{
}


FontSet::~FontSet()
{
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


