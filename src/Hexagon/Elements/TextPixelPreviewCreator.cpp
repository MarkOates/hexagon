

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


TextPixelPreviewCreator::TextPixelPreviewCreator(std::vector<std::string> text_lines, int width)
   : text_lines(text_lines)
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
int height = text_lines.size();

ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);

return bitmap;

}
} // namespace Elements
} // namespace Hexagon


