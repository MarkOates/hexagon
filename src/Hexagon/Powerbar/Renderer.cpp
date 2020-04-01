

#include <Hexagon/Powerbar/Renderer.hpp>
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


Renderer::Renderer(ALLEGRO_DISPLAY* display, Hexagon::Powerbar::Powerbar* powerbar, float width)
   : display(display)
   , powerbar(powerbar)
   , width(width)
{
}


Renderer::~Renderer()
{
}


void Renderer::draw_individual_rectangle(float x1, float y1, float x2, float y2)
{
float line_thickness = 3.0f;
ALLEGRO_COLOR color = al_color_name("gray");
al_draw_rectangle(x1, y1, x2, y2, color, line_thickness);
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

float height = 40;
float x = al_get_display_width(display) * 0.5;
float y = al_get_display_height(display) - height * 2;
float width = al_get_display_width(display) * 0.75f;
float line_thickness = 3.0f;
ALLEGRO_COLOR color = al_color_name("gray");

float rectangle_width = width * 0.3333f;
float h_width = rectangle_width * 0.5; //width * 0.3333f;
float h_height = height * 0.5f;

placement3d place(x, y, 0.0);

place.start_transform();

al_draw_rectangle(-h_width + rectangle_width*-1, -h_height, h_width + rectangle_width*-1, h_height, color, 3.0f);
al_draw_rectangle(-h_width + rectangle_width*0, -h_height, h_width + rectangle_width*0, h_height, color, 3.0f);
al_draw_rectangle(-h_width + rectangle_width*1, -h_height, h_width + rectangle_width*1, h_height, color, 3.0f);

place.restore_transform();

}
} // namespace Powerbar
} // namespace Hexagon


