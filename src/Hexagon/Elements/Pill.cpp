

#include <Hexagon/Elements/Pill.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


Pill::Pill(AllegroFlare::FontBin* font_bin, float x, float y, float width, float height, std::string label, ALLEGRO_COLOR color, ALLEGRO_COLOR font_color)
   : font_bin(font_bin)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , label(label)
   , color(color)
   , font_color(font_color)
{
}


Pill::~Pill()
{
}


void Pill::set_x(float x)
{
   this->x = x;
}


void Pill::set_y(float y)
{
   this->y = y;
}


void Pill::set_width(float width)
{
   this->width = width;
}


void Pill::set_height(float height)
{
   this->height = height;
}


void Pill::set_label(std::string label)
{
   this->label = label;
}


void Pill::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


void Pill::set_font_color(ALLEGRO_COLOR font_color)
{
   this->font_color = font_color;
}


float Pill::get_x() const
{
   return x;
}


float Pill::get_y() const
{
   return y;
}


float Pill::get_width() const
{
   return width;
}


float Pill::get_height() const
{
   return height;
}


std::string Pill::get_label() const
{
   return label;
}


ALLEGRO_COLOR Pill::get_color() const
{
   return color;
}


ALLEGRO_COLOR Pill::get_font_color() const
{
   return font_color;
}


void Pill::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Pill" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Pill" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   ALLEGRO_FONT *font = obtain_font();
   float font_height = al_get_font_line_height(font);
   al_draw_filled_rectangle(x, y, x+width, y+height, color);
   al_draw_text(font, font_color, x+width*0.5, y+height*0.5-font_height*0.5, ALLEGRO_ALIGN_CENTER, label.c_str());
   return;
}

ALLEGRO_FONT* Pill::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Pill" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get("Purista Medium.otf -16");
}
} // namespace Elements
} // namespace Hexagon


