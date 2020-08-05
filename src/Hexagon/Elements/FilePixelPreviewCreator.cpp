

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


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


void FilePixelPreviewCreator::create()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "FilePixelPreviewCreator" << "::" << "create" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
return;

}

std::vector<std::string> FilePixelPreviewCreator::file_contents()
{
return {};

}
} // namespace Elements
} // namespace Hexagon


