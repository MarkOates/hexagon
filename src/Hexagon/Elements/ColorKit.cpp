

#include <Hexagon/Elements/ColorKit.hpp>



namespace Hexagon
{
namespace Elements
{


ColorKit::ColorKit()
   : backfill_color(ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f})
   , base_text_color(ALLEGRO_COLOR{1.0f,1.0f,1.0f,1.0f})
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


ALLEGRO_COLOR ColorKit::get_backfill_color()
{
   return backfill_color;
}


ALLEGRO_COLOR ColorKit::get_base_text_color()
{
   return base_text_color;
}


ALLEGRO_COLOR ColorKit::black()
{
   return ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f};
}

ALLEGRO_COLOR ColorKit::white()
{
   return ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f};
}

ALLEGRO_COLOR ColorKit::turn_on_all_the_house_lights_white()
{
   return ALLEGRO_COLOR{0.8f, 0.85f, 0.86f, 0.86f};
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


