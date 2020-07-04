

#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <allegro_flare/color.h>
#include <Hexagon/Elements/Frame.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


StageInfoOverlay::StageInfoOverlay(ALLEGRO_FONT* title_font, ALLEGRO_COLOR* backfill_color, float backfill_opacity, placement3d* place)
   : title_font(title_font)
   , backfill_color(backfill_color)
   , backfill_opacity(backfill_opacity)
   , place(place)
   , text("")
{
}


StageInfoOverlay::~StageInfoOverlay()
{
}


void StageInfoOverlay::set_place(placement3d* place)
{
   this->place = place;
}


void StageInfoOverlay::set_text(std::string text)
{
   this->text = text;
}


ALLEGRO_FONT* StageInfoOverlay::get_title_font()
{
   return title_font;
}


ALLEGRO_COLOR* StageInfoOverlay::get_backfill_color()
{
   return backfill_color;
}


float StageInfoOverlay::get_backfill_opacity()
{
   return backfill_opacity;
}


placement3d* StageInfoOverlay::get_place()
{
   return place;
}


std::string StageInfoOverlay::get_text()
{
   return text;
}


void StageInfoOverlay::render()
{
if (!(backfill_color))
   {
      std::stringstream error_message;
      error_message << "StageInfoOverlay" << "::" << "render" << ": error: " << "guard \"backfill_color\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(title_font))
   {
      std::stringstream error_message;
      error_message << "StageInfoOverlay" << "::" << "render" << ": error: " << "guard \"title_font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(place))
   {
      std::stringstream error_message;
      error_message << "StageInfoOverlay" << "::" << "render" << ": error: " << "guard \"place\" not met";
      throw std::runtime_error(error_message.str());
   }
//if (!title_font) throw std::runtime_error("[StageInfoOverlay::render() error]: title_font can not be a nullptr");
//if (!place) throw std::runtime_error("[StageInfoOverlay::render() error]: place can not be a nullptr");

ALLEGRO_COLOR color_for_components = al_color_name("dodgerblue");
ALLEGRO_COLOR primary_color = color_for_components; //al_color_name("orange");

Hexagon::Elements::Frame outer_frame(place->size.x, place->size.y);
outer_frame.set_outline_color(primary_color);
outer_frame.render();

float line_height = al_get_font_line_height(title_font);
float text_width = al_get_text_width(title_font, text.c_str());
//al_draw_filled_rectangle(0, 0, place->size.x, line_height*2, al_color_name("midnightblue"));
ALLEGRO_COLOR color = primary_color;
//al_draw_text(title_font, color, place->size.x/2, line_height/2, ALLEGRO_ALIGN_CENTER, text.c_str());
float horizontal_padding = 40;
float x1 = place->size.x/2-text_width/2 - horizontal_padding;
float y1 = place->size.y/2-line_height/2;
float x2 = x1 + text_width + horizontal_padding * 2;
float y2 = y1 + line_height * 2;
ALLEGRO_COLOR base_backfill_color = *get_backfill_color();
ALLEGRO_COLOR backfill_color = color::color(base_backfill_color, get_backfill_opacity());
al_draw_filled_rectangle(x1, y1, x2, y2, backfill_color);
al_draw_rectangle(x1, y1, x2, y2, primary_color, 3.0f);
//text_box_frame.set_outline_color(primary_color);
//text_box_frame.render();
al_draw_text(title_font, color, place->size.x/2, place->size.y/2, ALLEGRO_ALIGN_CENTER, text.c_str());
return;

}
} // namespace Elements
} // namespace Hexagon


