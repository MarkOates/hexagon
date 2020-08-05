

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextPixelPreviewCreator::TextPixelPreviewCreator(int width)
   : width(width)
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
std::vector<std::string> lines = {};
int height = lines.size();

ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);

return bitmap;

}
} // namespace Elements
} // namespace Hexagon


