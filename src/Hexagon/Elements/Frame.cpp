

#include <Hexagon/Elements/Frame.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{
namespace Elements
{


AllegroFlare::FontBin Frame::dummy_font_bin = {};


Frame::Frame(float width, float height)
   : fonts(get_dummy_font_bin())
   , title_text("")
   , width(width)
   , height(height)
   , outline_color(build_default_frame_color())
   , line_thickness(2.5f)
{
}


Frame::~Frame()
{
}


void Frame::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void Frame::set_width(float width)
{
   this->width = width;
}


void Frame::set_height(float height)
{
   this->height = height;
}


void Frame::set_outline_color(ALLEGRO_COLOR outline_color)
{
   this->outline_color = outline_color;
}


void Frame::set_line_thickness(float line_thickness)
{
   this->line_thickness = line_thickness;
}


ALLEGRO_COLOR Frame::get_outline_color() const
{
   return outline_color;
}


float Frame::get_line_thickness() const
{
   return line_thickness;
}


ALLEGRO_COLOR Frame::build_default_frame_color()
{
   ALLEGRO_COLOR frame_color = AllegroFlare::color::color(
      AllegroFlare::color::mix(
          al_color_html("99ddc4"), al_color_name("white"),0.5
        ), 0.85
      );
   float frame_opacity = 0.6;
   frame_color.r *= frame_opacity;
   frame_color.g *= frame_opacity;
   frame_color.b *= frame_opacity;
   frame_color.a *= frame_opacity;
   return frame_color;
}

AllegroFlare::FontBin& Frame::get_dummy_font_bin()
{
   return dummy_font_bin;
}

void Frame::render()
{
   //float line_thickness = 2.5;
   //ALLEGRO_COLOR color = al_color_name("gray");
   //ALLEGRO_FONT *large_title_font = fonts["eurostyle.ttf 30"];
   //al_draw_text(large_title_font, color, 0, 0, 0, title_text.c_str());
   al_draw_rectangle(0, 0, width, height, get_outline_color(), get_line_thickness());
   return;
}
} // namespace Elements
} // namespace Hexagon


