

#include <Hexagon/Elements/StageInfoOverlay.hpp>



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
return;

}
} // namespace Elements
} // namespace Hexagon


