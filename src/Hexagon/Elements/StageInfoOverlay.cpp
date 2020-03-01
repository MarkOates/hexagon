

#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace Elements
{


StageInfoOverlay::StageInfoOverlay(ALLEGRO_FONT* title_font)
   : title_font(title_font)
   , text("")
{
}


StageInfoOverlay::~StageInfoOverlay()
{
}


ALLEGRO_FONT* StageInfoOverlay::get_title_font()
{
   return title_font;
}


std::string StageInfoOverlay::get_text()
{
   return text;
}


void StageInfoOverlay::render()
{
if (!title_font) throw std::runtime_error("[StageInfoOverlay::render() error]: title_font can not be a nullptr");
ALLEGRO_COLOR color = al_color_name("orange");
al_draw_text(title_font, color, 0, 0, ALLEGRO_ALIGN_CENTER, text.c_str());
return;

}
} // namespace Elements
} // namespace Hexagon


