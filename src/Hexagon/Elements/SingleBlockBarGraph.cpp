

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>



namespace Hexagon
{
namespace Elements
{


SingleBlockBarGraph::SingleBlockBarGraph(int number_of_active_bars, int number_of_bg_bars, float bar_width, float bar_height, float bar_spacing, float stroke_width, ALLEGRO_COLOR main_bar_color, ALLEGRO_COLOR bg_bar_color, ALLEGRO_COLOR stroke_color)
   : number_of_active_bars(number_of_active_bars)
   , number_of_bg_bars(number_of_bg_bars)
   , bar_width(bar_width)
   , bar_height(bar_height)
   , bar_spacing(bar_spacing)
   , stroke_width(stroke_width)
   , main_bar_color(main_bar_color)
   , bg_bar_color(bg_bar_color)
   , stroke_color(stroke_color)
{
}


SingleBlockBarGraph::~SingleBlockBarGraph()
{
}


void SingleBlockBarGraph::draw()
{
return;

}
} // namespace Elements
} // namespace Hexagon


