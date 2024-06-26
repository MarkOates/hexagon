

#include <Hexagon/Elements/StageInfoOverlay.hpp>

#include <Hexagon/Elements/Frame.hpp>
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Elements
{


StageInfoOverlay::StageInfoOverlay(AllegroFlare::FontBin* font_bin, ALLEGRO_COLOR* backfill_color, float backfill_opacity, placement3d* place)
   : font_bin(font_bin)
   , backfill_color(backfill_color)
   , backfill_opacity(backfill_opacity)
   , place(place)
   , text("")
   , upcase(true)
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


void StageInfoOverlay::set_upcase(bool upcase)
{
   this->upcase = upcase;
}


ALLEGRO_COLOR* StageInfoOverlay::get_backfill_color() const
{
   return backfill_color;
}


float StageInfoOverlay::get_backfill_opacity() const
{
   return backfill_opacity;
}


placement3d* StageInfoOverlay::get_place() const
{
   return place;
}


std::string StageInfoOverlay::get_text() const
{
   return text;
}


bool StageInfoOverlay::get_upcase() const
{
   return upcase;
}


void StageInfoOverlay::render()
{
   if (!(backfill_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::StageInfoOverlay::render]: error: guard \"backfill_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::StageInfoOverlay::render]: error: guard \"backfill_color\" not met");
   }
   if (!(place))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::StageInfoOverlay::render]: error: guard \"place\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::StageInfoOverlay::render]: error: guard \"place\" not met");
   }
   //if (!title_font) throw std::runtime_error("[StageInfoOverlay::render() error]: title_font can not be a nullptr");
   //if (!place) throw std::runtime_error("[StageInfoOverlay::render() error]: place can not be a nullptr");

   ALLEGRO_FONT *title_font = obtain_title_font();
   ALLEGRO_COLOR color_for_components = al_color_name("dodgerblue");
   ALLEGRO_COLOR primary_color = color_for_components; //al_color_name("orange");

   Hexagon::Elements::Frame outer_frame(place->size.x, place->size.y);
   outer_frame.set_outline_color(primary_color);
   outer_frame.render();

   std::string text_to_render = text;
   if (get_upcase())
   {
      std::transform(text_to_render.begin(), text_to_render.end(), text_to_render.begin(), ::toupper);
   }
   float line_height = al_get_font_line_height(title_font);
   float text_width = al_get_text_width(title_font, text_to_render.c_str());
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
   al_draw_text(title_font, color, place->size.x/2, place->size.y/2+4, ALLEGRO_ALIGN_CENTER, text_to_render.c_str());
   return;
}

ALLEGRO_FONT* StageInfoOverlay::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::StageInfoOverlay::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::StageInfoOverlay::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   // TODO: guard with font_bin->get_initialized()
   //return font_bin->auto_get("Eurostile.ttf 32");
   return font_bin->auto_get("EurostileExtendedBlack-aka-ExtendedBold.ttf 48");
}


} // namespace Elements
} // namespace Hexagon


