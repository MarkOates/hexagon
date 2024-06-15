

#include <Hexagon/Elements/TexturedRectangle.hpp>

#include <allegro_flare/useful.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[Hexagon::Elements::TexturedRectangle::draw]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::TexturedRectangle::draw]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(texture))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::TexturedRectangle::draw]: error: guard \"texture\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::TexturedRectangle::draw]: error: guard \"texture\" not met");
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


