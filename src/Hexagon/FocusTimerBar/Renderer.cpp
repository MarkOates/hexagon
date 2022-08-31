

#include <Hexagon/FocusTimerBar/Renderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace FocusTimerBar
{


Renderer::Renderer(float surface_width, float surface_height, Hexagon::FocusTimerBar::FocusTimerBar* focus_timer_bar)
   : surface_width(surface_width)
   , surface_height(surface_height)
   , focus_timer_bar(focus_timer_bar)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
   if (!(focus_timer_bar))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"focus_timer_bar\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   float width = surface_width * 0.6;
   float height = 30;
   float x = surface_width / 2 - width / 2;
   float y = surface_height - height * 1;
   float time_length = 0.64f;
   float length = time_length * width;
   ALLEGRO_COLOR color = al_color_name("gray");
   ALLEGRO_COLOR border_color = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);

   std::time_t time_now = time(0);
   struct tm now_tm = *localtime(&time_now);
   //double seconds = difftime(time_now,mktime(&newyear));
   double seconds = difftime(time_now, mktime(0));
   double normal_length = std::fmod(seconds, focus_timer_bar->get_focus_timer_duration_sec())
                        / focus_timer_bar->get_focus_timer_duration_sec();
   length = normal_length * width;

   float h_padding = 5.0f;
   float v_padding = 5.0f;
   float roundness = 0.0f;
   al_draw_rectangle(x - h_padding, y - v_padding, x + width + h_padding, y + v_padding, border_color, 1.0);
   al_draw_line(x, y, x+length, y, color, 1.0f);
   //al_draw_line(10, 10, 600, 300, al_color_name("white"), 10.0f);
   return;
}
} // namespace FocusTimerBar
} // namespace Hexagon


