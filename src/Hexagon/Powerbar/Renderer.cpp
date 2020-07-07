

#include <Hexagon/Powerbar/Renderer.hpp>
#include <ctime>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <sstream>
#include <allegro_flare/placement3d.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{
namespace Powerbar
{


Renderer::Renderer(ALLEGRO_DISPLAY* display, Hexagon::Powerbar::Powerbar* powerbar, ALLEGRO_FONT* font, ALLEGRO_COLOR backfill_color, float width)
   : display(display)
   , powerbar(powerbar)
   , font(font)
   , backfill_color(backfill_color)
   , width(width)
   , draw_state_boxes(true)
   , draw_focus_timer(true)
{
}


Renderer::~Renderer()
{
}


void Renderer::draw_focus_timer_bar()
{
if (!(display))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "draw_focus_timer_bar" << ": error: " << "guard \"display\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(powerbar))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "draw_focus_timer_bar" << ": error: " << "guard \"powerbar\" not met";
      throw std::runtime_error(error_message.str());
   }
float width = al_get_display_width(display) * 0.6;
float height = 30;
float x = al_get_display_width(display) / 2 - width / 2;
float y = al_get_display_height(display) - height * 1;
float time_length = 0.64f;
float length = time_length * width;
ALLEGRO_COLOR color = al_color_name("gray");
ALLEGRO_COLOR border_color = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);

std::time_t time_now = time(0);
struct tm now_tm = *localtime(&time_now);
//double seconds = difftime(time_now,mktime(&newyear));
double seconds = difftime(time_now, mktime(0));
double normal_length = std::fmod(seconds, powerbar->get_focus_timer_duration_sec())
                     / powerbar->get_focus_timer_duration_sec();
length = normal_length * width;

float h_padding = 5.0f;
float v_padding = 5.0f;
float roundness = 0.0f;
al_draw_rectangle(x - h_padding, y - v_padding, x + width + h_padding, y + v_padding, border_color, 2.0);
al_draw_line(x, y, x+length, y, color, 1.0f);
//al_draw_line(10, 10, 600, 300, al_color_name("white"), 10.0f);
return;

}

void Renderer::draw_individual_rectangle(float x1, float y1, float x2, float y2, std::string text)
{
float h_padding = 8.0f;
float v_padding = 8.0f;
ALLEGRO_COLOR border_color = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);
float border_line_thickness = 2.0f;
ALLEGRO_COLOR color = al_color_name("gray");
al_draw_rectangle(x1, y1, x2, y2, border_color, border_line_thickness);

float font_height = al_get_font_line_height(font);
float text_x = x1 + h_padding;
float text_y = y1 + (y2 - y1) * 0.5 - font_height * 0.5;
al_draw_text(font, color, text_x, text_y, ALLEGRO_ALIGN_LEFT, text.c_str());
return;

}

void Renderer::render()
{
if (!powerbar)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer error:] cannot \"" << __FUNCTION__ << "\" with a nullptr powerbar";
   throw std::runtime_error(error_message.str());
}
if (!font)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer error:] cannot \"" << __FUNCTION__ << "\" with a nullptr font";
   throw std::runtime_error(error_message.str());
}

float height = 30;
float x = al_get_display_width(display) * 0.5;
float y = al_get_display_height(display) - height * 2;
float width = al_get_display_width(display) * 0.75f;
float line_thickness = 3.0f;
//ALLEGRO_COLOR background_color = AllegroFlare::color::color(al_color_name("black"), 0.65f);
ALLEGRO_COLOR background_color = AllegroFlare::color::color(backfill_color, 0.65f);
   //AllegroFlare::color::color(al_color_html("5b5c60"), 0.65f);
ALLEGRO_COLOR color = al_color_name("gray");

std::string left_powerbox_text = "";
std::string center_powerbox_text = "";
std::string right_powerbox_text = "";

left_powerbox_text = powerbar->get_files_are_modified() ? "files modified" : "";
//center_powerbox_text = powerbar->get_files_are_committed() ? "COMMITTED" : "PENDING COMMIT";
//right_powerbox_text = powerbar->get_commits_are_in_sync_with_remote() ? "IN SYNC" : "OUT OF SYNC";

//std::string left_box_text = powerbar->get_files_are_modified();
//std::string center_box_text = powerbar->get_files_are_modified();
//std::string right_box_text = powerbar->get_files_are_modified();

float rectangle_width = width * 0.3333f;
float h_width = rectangle_width * 0.5; //width * 0.3333f;
float h_height = height * 0.5f;

placement3d place(x, y, 0.0);
place.size.x = width;
place.size.y = height;

place.start_transform();

if (draw_state_boxes)
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, background_color);

   draw_individual_rectangle(rectangle_width*0,
                             0,
                             rectangle_width*1,
                             height,
                             left_powerbox_text.c_str());
   draw_individual_rectangle(rectangle_width*1,
                             0,
                             rectangle_width*2,
                             height,
                             center_powerbox_text.c_str());
   draw_individual_rectangle(rectangle_width*2,
                             0,
                             rectangle_width*3,
                             height,
                             right_powerbox_text.c_str());
}

place.restore_transform();

if (draw_focus_timer) draw_focus_timer_bar();

return;

}
} // namespace Powerbar
} // namespace Hexagon


