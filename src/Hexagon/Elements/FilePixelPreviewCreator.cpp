

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/useful_php.h>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Elements
{


FilePixelPreviewCreator::FilePixelPreviewCreator(std::string filename, int width)
   : filename(filename)
   , width(width)
{
}


FilePixelPreviewCreator::~FilePixelPreviewCreator()
{
}


ALLEGRO_BITMAP* FilePixelPreviewCreator::create()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "FilePixelPreviewCreator" << "::" << "create" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!Blast::FileExistenceChecker(filename).exists())
   {
      std::stringstream error_message;
      error_message << "FilePixelPreviewCreator::create: error: the file \"" << filename << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   std::vector<std::string> lines = get_file_contents();

   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator(lines);

   return text_pixel_preview_creator.create();
}

std::vector<std::string> FilePixelPreviewCreator::get_file_contents()
{
   std::string contents = php::file_get_contents(filename);
   return Blast::StringSplitter(contents, '\n').split();
}


} // namespace Elements
} // namespace Hexagon


