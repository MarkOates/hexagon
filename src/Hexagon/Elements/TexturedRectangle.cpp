

#include <Hexagon/Elements/TexturedRectangle.hpp>
#include <allegro_flare/useful.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TexturedRectangle::TexturedRectangle(float x1, float y1, float x2, float y2, ALLEGRO_BITMAP* texture)
   : x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
   , texture(texture)
{
}


TexturedRectangle::~TexturedRectangle()
{
}


void TexturedRectangle::draw()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "TexturedRectangle" << "::" << "draw" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(texture))
      {
         std::stringstream error_message;
         error_message << "TexturedRectangle" << "::" << "draw" << ": error: " << "guard \"texture\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR white_color = ALLEGRO_COLOR{1, 1, 1, 1};
   draw_textured_rectangle(
      x1,
      y1,
      x2,
      y2,
      texture,
      white_color
   );
   return;
}
} // namespace Elements
} // namespace Hexagon


