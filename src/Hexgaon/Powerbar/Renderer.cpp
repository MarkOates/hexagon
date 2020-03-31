

#include <Hexgaon/Powerbar/Renderer.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


namespace Hexgaon
{
namespace Powerbar
{


Renderer::Renderer(Hexagon::Powerbar::Powerbar* powerbar, float width)
   : powerbar(powerbar)
   , width(width)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
float width = this->width;
float height = 40;
float line_thickness = 3.0f;
ALLEGRO_COLOR color = al_color_name("gray");

float h_width = width * 0.5f;
float h_height = height * 0.5f;

al_draw_rectangle(-h_width, -h_height, h_width, h_height, color, 3.0f);

}
} // namespace Powerbar
} // namespace Hexgaon


