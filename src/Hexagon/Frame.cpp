

#include <Hexagon/Frame.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{


AllegroFlare::FontBin Frame::dummy_font_bin = {};


Frame::Frame()
   : fonts(get_dummy_font_bin())
   , title_text("")
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
ALLEGRO_FONT *large_title_font = fonts["eurostyle.ttf 30"];
ALLEGRO_COLOR color = al_color_name("dodgerblue");
al_draw_text(large_title_font, color, 0, 0, 0, title_text.c_str());
return;

}
} // namespace Hexagon


