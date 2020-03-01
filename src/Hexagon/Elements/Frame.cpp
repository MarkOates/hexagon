

#include <Hexagon/Elements/Frame.hpp>
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


Frame::Frame()
   : fonts(get_dummy_font_bin())
   , title_text("")
   , width(1.0f)
   , height(1.0f)
{
}


Frame::~Frame()
{
}


AllegroFlare::FontBin& Frame::get_dummy_font_bin()
{
return dummy_font_bin;

}

void Frame::render()
{
float line_thickness = 2.5;
ALLEGRO_COLOR color = al_color_name("dodgerblue");
//ALLEGRO_FONT *large_title_font = fonts["eurostyle.ttf 30"];
//al_draw_text(large_title_font, color, 0, 0, 0, title_text.c_str());
al_draw_rectangle(0, 0, width, height, color, line_thickness);
return;

}
} // namespace Elements
} // namespace Hexagon


