

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>
#include <allegro5/allegro.h>
#include <Blast/FileExistenceChecker.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro_flare/useful_php.h>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace Elements
{


TextPixelPreviewCreator::TextPixelPreviewCreator(std::string filename, int width)
   : filename(filename)
   , width(width)
{
}


TextPixelPreviewCreator::~TextPixelPreviewCreator()
{
}


ALLEGRO_BITMAP* TextPixelPreviewCreator::create()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TextPixelPreviewCreator" << "::" << "create" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!Blast::FileExistenceChecker(filename).exists())
{
   std::stringstream error_message;
   error_message << "FilePixelPreviewCreator::create: error: the file "" << filename << "" does not exist.";
   throw std::runtime_error(error_message.str());
}

std::vector<std::string> lines = get_file_contents();
int height = lines.size();

ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);

return bitmap;

}

std::vector<std::string> TextPixelPreviewCreator::get_file_contents()
{
std::string contents = php::file_get_contents(filename);
return Blast::StringSplitter(contents, '\n').split();

}
} // namespace Elements
} // namespace Hexagon


