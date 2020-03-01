

#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <Hexagon/FontSet.hpp>


namespace Hexagon
{
namespace Elements
{


StageInfoOverlay::StageInfoOverlay()
   : font_set(nullptr)
   , text("")
{
}


StageInfoOverlay::~StageInfoOverlay()
{
}


std::string StageInfoOverlay::get_text()
{
   return text;
}


void StageInfoOverlay::render()
{
//al_draw_text(
return;

}
} // namespace Elements
} // namespace Hexagon


