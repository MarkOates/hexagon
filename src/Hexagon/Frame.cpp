

#include <Hexagon/Frame.hpp>



namespace Hexagon
{


Frame::Frame()
   : fonts(nullptr)
   , title_text("")
{
}


Frame::~Frame()
{
}


void Frame::render()
{
ALLEGRO_FONT *large_title_font = fonts["eurostyle.ttf 30"];
ALLEGRO_COLOR color = al_color_name("dodgerblue");
al_draw_text(0, 0, color, large_title_font, title_text.c_str());
return;

}
} // namespace Hexagon


