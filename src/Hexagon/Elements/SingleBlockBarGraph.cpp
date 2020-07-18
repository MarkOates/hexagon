

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


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
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "SingleBlockBarGraph" << "::" << "draw" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "SingleBlockBarGraph" << "::" << "draw" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "SingleBlockBarGraph" << "::" << "draw" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
      throw std::runtime_error(error_message.str());
   }
float bar_hwidth = bar_width * 0.5f;
float bar_hheight = bar_height * 0.5f;
for (int i=0; i<number_of_bg_bars; i++)
{
   al_draw_filled_rectangle(-bar_hwidth, -bar_hheight, bar_hwidth, bar_hheight, bg_bar_color);
}
return;

}
} // namespace Elements
} // namespace Hexagon


