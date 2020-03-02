

#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace Elements
{


StageInfoOverlay::StageInfoOverlay(ALLEGRO_FONT* title_font, placement3d* place)
   : title_font(title_font)
   , place(place)
   , text("")
{
}


StageInfoOverlay::~StageInfoOverlay()
{
}


void StageInfoOverlay::set_place(placement3d* place)
{
   this->place = place;
}


void StageInfoOverlay::set_text(std::string text)
{
   this->text = text;
}


ALLEGRO_FONT* StageInfoOverlay::get_title_font()
{
   return title_font;
}


placement3d* StageInfoOverlay::get_place()
{
   return place;
}


std::string StageInfoOverlay::get_text()
{
   return text;
}


void StageInfoOverlay::render()
{
if (!title_font) throw std::runtime_error("[StageInfoOverlay::render() error]: title_font can not be a nullptr");
if (!place) throw std::runtime_error("[StageInfoOverlay::render() error]: place can not be a nullptr");

ALLEGRO_COLOR color = al_color_name("orange");
al_draw_text(title_font, color, place->size.x/2, place->size.y/2, ALLEGRO_ALIGN_CENTER, text.c_str());
return;

}
} // namespace Elements
} // namespace Hexagon


