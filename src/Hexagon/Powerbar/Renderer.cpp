

#include <Hexagon/Powerbar/Renderer.hpp>
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


void Renderer::render()
{
float height = 40;
float x = al_get_display_width(display) * 0.5;
float y = al_get_display_height(display) - height * 2;
float width = this->width;
float line_thickness = 3.0f;
ALLEGRO_COLOR color = al_color_name("gray");

float h_width = width * 0.5f;
float h_height = height * 0.5f;

placement3d place(al_get_display_width(display) * 0.5, al_get_display_height(display), 0.0);

place.start_transform();

al_draw_rectangle(-h_width, -h_height, h_width, h_height, color, 3.0f);

place.restore_transform();

}
} // namespace Powerbar
} // namespace Hexagon


