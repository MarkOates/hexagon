

#include <Hexagon/Powerbar/Renderer.hpp>
#include <Hexagon/shared_globals.hpp>
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


Renderer::Renderer(ALLEGRO_DISPLAY* display, Hexagon::Powerbar::Powerbar* powerbar, ALLEGRO_FONT* font, float width)
   : display(display)
   , powerbar(powerbar)
   , font(font)
   , width(width)
{
}


Renderer::~Renderer()
{
}


void Renderer::draw_individual_rectangle(float x1, float y1, float x2, float y2, std::string text)
{
float line_thickness = 3.0f;
float padding = 8.0f;
ALLEGRO_COLOR color = al_color_name("gray");
al_draw_rectangle(x1, y1, x2, y2, color, line_thickness);

float font_height = al_get_font_line_height(font);
float text_x = x1 + padding;
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

float height = 40;
float x = al_get_display_width(display) * 0.5;
float y = al_get_display_height(display) - height * 2;
float width = al_get_display_width(display) * 0.75f;
float line_thickness = 3.0f;
//ALLEGRO_COLOR background_color = AllegroFlare::color::color(al_color_name("black"), 0.65f);
ALLEGRO_COLOR background_color = AllegroFlare::color::color(hexagon_get_backfill_color(), 0.65f);
   //AllegroFlare::color::color(al_color_html("5b5c60"), 0.65f);
ALLEGRO_COLOR color = al_color_name("gray");

std::string left_powerbox_text = ""; //powerbar->get_files_are_modified() ? "GREEN" : "FILE MODIFIED";
std::string center_powerbox_text = ""; //powerbar->get_files_are_committed() ? "COMMITTED" : "PENDING COMMIT";
std::string right_powerbox_text = ""; //powerbar->get_commits_are_in_sync_with_remote() ? "IN SYNC" : "OUT OF SYNC";

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

place.restore_transform();

}
} // namespace Powerbar
} // namespace Hexagon


