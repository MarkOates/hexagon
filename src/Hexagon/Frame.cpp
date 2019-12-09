

#include <Hexagon/Frame.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{


AllegroFlare::FontBin Frame::dummy_font_bin = {};


Frame::Frame()
   : fonts(get_dummy_font_bin())
   , title_text("")
   , screen_width(1920)
   , screen_height(1080)
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
ALLEGRO_FONT *large_title_font = fonts["eurostyle.ttf 30"];
ALLEGRO_COLOR color = al_color_name("dodgerblue");
al_draw_text(large_title_font, color, 0, 0, 0, title_text.c_str());
al_draw_rectangle(0, 0, screen_width, screen_height, color, line_thickness);
return;

}
} // namespace Hexagon


