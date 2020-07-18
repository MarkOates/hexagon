

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


void SingleBlockBarGraph::set_number_of_active_bars(int number_of_active_bars)
{
   this->number_of_active_bars = number_of_active_bars;
}


void SingleBlockBarGraph::set_number_of_bg_bars(int number_of_bg_bars)
{
   this->number_of_bg_bars = number_of_bg_bars;
}


void SingleBlockBarGraph::set_bar_width(float bar_width)
{
   this->bar_width = bar_width;
}


void SingleBlockBarGraph::set_bar_height(float bar_height)
{
   this->bar_height = bar_height;
}


void SingleBlockBarGraph::set_bar_spacing(float bar_spacing)
{
   this->bar_spacing = bar_spacing;
}


void SingleBlockBarGraph::set_stroke_width(float stroke_width)
{
   this->stroke_width = stroke_width;
}


void SingleBlockBarGraph::set_main_bar_color(ALLEGRO_COLOR main_bar_color)
{
   this->main_bar_color = main_bar_color;
}


void SingleBlockBarGraph::set_bg_bar_color(ALLEGRO_COLOR bg_bar_color)
{
   this->bg_bar_color = bg_bar_color;
}


void SingleBlockBarGraph::set_stroke_color(ALLEGRO_COLOR stroke_color)
{
   this->stroke_color = stroke_color;
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
int bar_start_x = 0;
for (int i=number_of_active_bars; i<number_of_bg_bars; i++)
{
   float bar_x = bar_start_x + bar_spacing * i;
   al_draw_filled_rectangle(-bar_hwidth + bar_x, -bar_hheight, bar_hwidth + bar_x, bar_hheight, bg_bar_color);
}
for (int i=0; i<number_of_active_bars; i++)
{
   float bar_x = bar_start_x + bar_spacing * i;
   // draw filled box
   al_draw_filled_rectangle(-bar_hwidth + bar_x, -bar_hheight, bar_hwidth + bar_x, bar_hheight, main_bar_color);
   // draw outline stroke
   al_draw_rectangle(
      -bar_hwidth + bar_x,
      -bar_hheight,
      bar_hwidth + bar_x,
      bar_hheight,
      stroke_color,
      stroke_width
   );
}
return;

}
} // namespace Elements
} // namespace Hexagon


