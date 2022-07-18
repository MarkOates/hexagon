

#include <Hexagon/Elements/ColorKit.hpp>
#include <AllegroFlare/Color.hpp>


namespace Hexagon
{
namespace Elements
{


ColorKit::ColorKit(ALLEGRO_COLOR backfill_color, ALLEGRO_COLOR base_text_color)
   : backfill_color(backfill_color)
   , base_text_color(base_text_color)
{
}


ColorKit::~ColorKit()
{
}


void ColorKit::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void ColorKit::set_base_text_color(ALLEGRO_COLOR base_text_color)
{
   this->base_text_color = base_text_color;
}


ALLEGRO_COLOR ColorKit::get_backfill_color(float opacity)
{
   return ALLEGRO_COLOR{backfill_color.r*opacity, backfill_color.g*opacity, backfill_color.b*opacity, opacity};
}

ALLEGRO_COLOR ColorKit::get_base_text_color(float opacity)
{
   return ALLEGRO_COLOR{base_text_color.r*opacity, base_text_color.g*opacity, base_text_color.b*opacity, opacity};
}

ALLEGRO_COLOR ColorKit::pure_white_blue()
{
   //ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
   //ALLEGRO_COLOR color = AllegroFlare::color::mix(epic_green_color, al_color_name("dodgerblue"), 0.5);
   //color;
   return al_color_html("5cb7e2");
}

ALLEGRO_COLOR ColorKit::black()
{
   return ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f};
}

ALLEGRO_COLOR ColorKit::white()
{
   return ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f};
}

ALLEGRO_COLOR ColorKit::terminal_warm_orange()
{
   return ALLEGRO_COLOR{0.973, 0.592, 0.078, 1.0};
}

ALLEGRO_COLOR ColorKit::turn_on_all_the_house_lights_white()
{
   return ALLEGRO_COLOR{0.8f, 0.85f, 0.86f, 0.86f};
}

ALLEGRO_COLOR ColorKit::backwall_gray()
{
   return ALLEGRO_COLOR{0.733f, 0.631f, 0.569f, 1.0f}; // bba191
}

ALLEGRO_COLOR ColorKit::inv_base_text_color()
{
   return ALLEGRO_COLOR{1.0f-base_text_color.r, 1.0f-base_text_color.g, 1.0f-base_text_color.b, base_text_color.a};
}

ALLEGRO_COLOR ColorKit::inv_backfill_color()
{
   return ALLEGRO_COLOR{1.0f-backfill_color.r, 1.0f-backfill_color.g, 1.0f-backfill_color.b, backfill_color.a};
}
} // namespace Elements
} // namespace Hexagon


