

#include <Hexagon/TitleScreen.hpp>
#include <Hexagon/Logo.hpp>
#include <allegro5/allegro_font.h>
#include <Hexagon/Shaders/TiledHexagonMotionEffect.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro.h>
#include <sstream>


namespace Hexagon
{


TitleScreen::TitleScreen(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


TitleScreen::~TitleScreen()
{
}


void TitleScreen::draw_hexagon_logo_and_wait_for_keypress(int display_width, int display_height)
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "TitleScreen" << "::" << "draw_hexagon_logo_and_wait_for_keypress" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
float logo_radius = 64;

std::string logo_font_identifier = "Expansiva_bold.otf 23";
ALLEGRO_FONT *expansiva_font = font_bin->auto_get(logo_font_identifier);

std::string detail_text_font_identifier = "Purista Medium.otf 16";
ALLEGRO_FONT *purista_font = font_bin->auto_get(detail_text_font_identifier);

Hexagon::Logo logo(
  display_width/2,
  display_height/2,
  logo_radius,
  expansiva_font,
  al_color_html("#bc2d48"),
  2.25);
logo.render();

std::string allegro_version_string = build_allegro_version_string();
al_draw_text(purista_font, al_color_html("#bc2d48"),
   display_width/2, display_height/2 + logo_radius * 2.0, ALLEGRO_ALIGN_CENTER,
   allegro_version_string.c_str());

al_flip_display();

// wait for keypress
{
  ALLEGRO_EVENT_QUEUE *wait_for_keypress_event_queue;
  ALLEGRO_EVENT event;

  al_install_keyboard();
  wait_for_keypress_event_queue = al_create_event_queue();
  al_register_event_source(wait_for_keypress_event_queue, al_get_keyboard_event_source());

  do
    al_wait_for_event(wait_for_keypress_event_queue, &event);
  while (event.type != ALLEGRO_EVENT_KEY_DOWN);

  al_destroy_event_queue(wait_for_keypress_event_queue);
}

return;

}

std::string TitleScreen::build_allegro_version_string()
{
uint32_t version = al_get_allegro_version();
int major = version >> 24;
int minor = (version >> 16) & 255;
int revision = (version >> 8) & 255;
int release = version & 255;

std::stringstream result;
result << "Allegro v" << major << "." << minor << "." << revision << " r" << release;
return result.str();

}
} // namespace Hexagon


