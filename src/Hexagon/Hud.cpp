

#include <Hexagon/Hud.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <Hexagon/Powerbar/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


AllegroFlare::FontBin Hud::dummy_font_bin = {};


Hud::Hud(ALLEGRO_DISPLAY* display, AllegroFlare::FontBin& fonts, std::string title_text, ALLEGRO_COLOR backfill_color, bool show_disabled_screen, bool draw_powerbar, bool files_are_modified, bool files_are_committed, bool commits_are_in_sync_with_remote, bool show_profiler)
   : initialized(false)
   , screen_sub_bitmap(nullptr)
   , notifications({})
   , notifications2({})
   , powerbar({})
   , display(display)
   , fonts(fonts)
   , title_text(title_text)
   , backfill_color(backfill_color)
   , show_disabled_screen(show_disabled_screen)
   , draw_powerbar(draw_powerbar)
   , files_are_modified(files_are_modified)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
   , show_profiler(show_profiler)
{
}


Hud::~Hud()
{
}


void Hud::set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap)
{
   this->screen_sub_bitmap = screen_sub_bitmap;
}


void Hud::set_notifications(std::vector<std::string> notifications)
{
   this->notifications = notifications;
}


void Hud::set_notifications2(std::vector<std::string> notifications2)
{
   this->notifications2 = notifications2;
}


void Hud::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void Hud::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Hud::set_show_disabled_screen(bool show_disabled_screen)
{
   this->show_disabled_screen = show_disabled_screen;
}


void Hud::set_draw_powerbar(bool draw_powerbar)
{
   this->draw_powerbar = draw_powerbar;
}


void Hud::set_files_are_modified(bool files_are_modified)
{
   this->files_are_modified = files_are_modified;
}


void Hud::set_files_are_committed(bool files_are_committed)
{
   this->files_are_committed = files_are_committed;
}


void Hud::set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote)
{
   this->commits_are_in_sync_with_remote = commits_are_in_sync_with_remote;
}


void Hud::set_show_profiler(bool show_profiler)
{
   this->show_profiler = show_profiler;
}


std::vector<std::string> Hud::get_notifications()
{
   return notifications;
}


std::vector<std::string> Hud::get_notifications2()
{
   return notifications2;
}


std::string Hud::get_title_text()
{
   return title_text;
}


bool Hud::get_show_disabled_screen()
{
   return show_disabled_screen;
}


bool Hud::get_draw_powerbar()
{
   return draw_powerbar;
}


bool Hud::get_show_profiler()
{
   return show_profiler;
}


Hexagon::Powerbar::Powerbar &Hud::get_powerbar_ref()
{
   return powerbar;
}


AllegroFlare::FontBin& Hud::get_dummy_font_bin()
{
return dummy_font_bin;

}

ALLEGRO_FONT* Hud::obtain_text_font()
{
return fonts["Eurostile.ttf -27"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

void Hud::initialize()
{
if (initialized) return;
if (!display)
{
   throw std::runtime_error("[Hud::initialize()] Cannot initialize Hud with a nullptr screen_sub_bitmap");
}

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(
   backbuffer,
   0,
   0,
   al_get_bitmap_width(backbuffer),
   al_get_bitmap_height(backbuffer)
   );
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::reinitialize()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(display))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"display\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(screen_sub_bitmap))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"screen_sub_bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
al_destroy_bitmap(screen_sub_bitmap);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer,
                                                            0,
                                                            0,
                                                            al_get_bitmap_width(backbuffer),
                                                            al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::draw_current_focus_name()
{
ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
ALLEGRO_COLOR color = AllegroFlare::color::mix(epic_green_color, al_color_name("dodgerblue"), 0.5);
float display_center_x = al_get_display_width(display) / 2;
int y_position = 20;

al_draw_text(obtain_text_font(),
             color,
             display_center_x,
             y_position + 20,
             ALLEGRO_ALIGN_CENTER,
             title_text.c_str());
return;

}

void Hud::draw_profile_timer_graph()
{
global::profiler.draw(10, 10, obtain_text_font());
return;

}

void Hud::draw()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "draw" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
int y_cursor = 0;
int frame_width = al_get_bitmap_width(screen_sub_bitmap);
int frame_height = al_get_bitmap_height(screen_sub_bitmap);

ALLEGRO_STATE previous_target_bitmap_state;
al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(screen_sub_bitmap);

draw_current_focus_name();

if (show_profiler) draw_profile_timer_graph();

if (show_disabled_screen)
{
   al_draw_line(0,
                0,
                al_get_display_width(display),
                al_get_display_height(display),
                al_color_name("red"),
                3.0);
}

ALLEGRO_COLOR color = al_color_name("red");
float notification_bottom_padding = al_get_font_line_height(obtain_text_font());
float font_line_height = al_get_font_line_height(obtain_text_font());
y_cursor=0;
for (auto &notification : notifications)
{
  float y_position = y_cursor * notification_bottom_padding;
  al_draw_text(obtain_text_font(), color, 0, y_position, 0, notification.c_str());
  y_cursor++;
}

y_cursor=0;
for (auto &notification2 : notifications2)
{
  float y_position = (y_cursor+1) * font_line_height;
  al_draw_text(obtain_text_font(),
               color,
               frame_width,
               frame_height-y_position,
               ALLEGRO_ALIGN_RIGHT,
               notification2.c_str());
  y_cursor++;
}

if (draw_powerbar)
{
   powerbar.set_files_are_committed(files_are_committed);
   powerbar.set_files_are_modified(files_are_modified);
   powerbar.set_commits_are_in_sync_with_remote(commits_are_in_sync_with_remote);

   Hexagon::Powerbar::Renderer powerbar_renderer(display, &powerbar, obtain_text_font(), backfill_color);
   powerbar_renderer.render();
}

al_restore_state(&previous_target_bitmap_state);
return;

}
} // namespace Hexagon


