

#include <Hexagon/TitleScreen.hpp>
#include <AllegroFlare/Profiler.hpp>
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


void TitleScreen::draw_hexagon_logo_and_wait_for_keypress()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TitleScreen" << "::" << "draw_hexagon_logo_and_wait_for_keypress" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "TitleScreen" << "::" << "draw_hexagon_logo_and_wait_for_keypress" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "TitleScreen" << "::" << "draw_hexagon_logo_and_wait_for_keypress" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
      throw std::runtime_error(error_message.str());
   }
AllegroFlare::Profiler profiler;

float logo_radius = 64;
int display_width = al_get_bitmap_width(al_get_target_bitmap());
int display_height = al_get_bitmap_height(al_get_target_bitmap());
ALLEGRO_COLOR hexagon_red = al_color_html("#bc2d48");
Hexagon::Shaders::TiledHexagonMotionEffect shader;
shader.initialize();

std::string logo_font_identifier = "Expansiva_bold.otf 23";
ALLEGRO_FONT *expansiva_font = font_bin->auto_get(logo_font_identifier);

std::string detail_text_font_identifier = "Purista Medium.otf 16";
ALLEGRO_FONT *purista_font = font_bin->auto_get(detail_text_font_identifier);

//shader.activate();
shader.set_texture_width(display_width);
shader.set_texture_height(display_height);
shader.set_time(1000);
//shader.deactivate();

al_install_keyboard();

ALLEGRO_EVENT_QUEUE *primary_event_queue;
primary_event_queue = al_create_event_queue();
al_register_event_source(primary_event_queue, al_get_keyboard_event_source());

ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60);
al_register_event_source(primary_event_queue, al_get_timer_event_source(primary_timer));
al_start_timer(primary_timer);

// wait for keypress
bool abort_program = false;
while (!abort_program)
{
   ALLEGRO_EVENT event;
   al_wait_for_event(primary_event_queue, &event);

   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_DOWN:
      {
        abort_program = true;
      }
      break;
   case ALLEGRO_EVENT_TIMER:
      {
         profiler.emit("primary_timer logic started");
         Hexagon::Logo logo(
           display_width/2,
           display_height/2,
           logo_radius,
           expansiva_font,
           hexagon_red,
           2.25);
         logo.render();

         std::string allegro_version_string = build_allegro_version_string();
         al_draw_text(purista_font, hexagon_red,
            display_width/2, display_height/2 + logo_radius * 2.0, ALLEGRO_ALIGN_CENTER,
            allegro_version_string.c_str());

         profiler.emit("primary_timer logic ended");
         al_flip_display();
         profiler.emit("al_flip_display logic completed");
      }
      break;
   default:
      break;
   }
}

al_stop_timer(primary_timer);
al_destroy_event_queue(primary_event_queue);
al_destroy_timer(primary_timer);

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


