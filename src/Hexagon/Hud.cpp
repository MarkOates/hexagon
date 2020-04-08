

#include <Hexagon/Hud.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <Hexagon/Powerbar/Renderer.hpp>


namespace Hexagon
{


AllegroFlare::FontBin Hud::dummy_font_bin = {};


Hud::Hud(ALLEGRO_DISPLAY* display, AllegroFlare::FontBin& fonts, std::string title_text, bool show_disabled_screen, bool show_powerbar, bool files_are_modified, bool files_are_committed, bool commits_are_in_sync_with_remote)
   : initialized(false)
   , display(display)
   , fonts(fonts)
   , title_text(title_text)
   , show_disabled_screen(show_disabled_screen)
   , show_powerbar(show_powerbar)
   , files_are_modified(files_are_modified)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
   , screen_sub_bitmap(nullptr)
   , notifications({})
   , notifications2({})
{
}


Hud::~Hud()
{
}


void Hud::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void Hud::set_show_disabled_screen(bool show_disabled_screen)
{
   this->show_disabled_screen = show_disabled_screen;
}


void Hud::set_show_powerbar(bool show_powerbar)
{
   this->show_powerbar = show_powerbar;
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


std::string Hud::get_title_text()
{
   return title_text;
}


bool Hud::get_show_disabled_screen()
{
   return show_disabled_screen;
}


bool Hud::get_show_powerbar()
{
   return show_powerbar;
}


std::vector<std::string> Hud::get_notifications()
{
   return notifications;
}


std::vector<std::string> Hud::get_notifications2()
{
   return notifications2;
}


AllegroFlare::FontBin& Hud::get_dummy_font_bin()
{
return dummy_font_bin;

}

ALLEGRO_FONT* Hud::obtain_text_font()
{
return fonts["Eurostile.ttf -22"];
}

void Hud::initialize()
{
if (initialized) return;
if (!display)
{
   throw std::runtime_error("[Hud::initialize()] Cannot initialize Hud with a nullptr screen_sub_bitmap");
}

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::reinitialize()
{
if (!initialized)
{
   throw std::runtime_error("[Hud::reinitialize()] Cannot reinitialize until initialize has been called.");
}
if (!display)
{
   throw std::runtime_error("[Hud::reinitialize()] Cannot reinitialize Hud with a nullptr display");
}
if (!screen_sub_bitmap)
{
   throw std::runtime_error("[Hud::reinitialize()] Should not have gotten here; Expecting screen_sub_bitmap");
}

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
al_destroy_bitmap(screen_sub_bitmap);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
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
             y_position,
             ALLEGRO_ALIGN_CENTER,
             title_text.c_str());
return;

}

void Hud::draw()
{
if (!initialized) throw std::runtime_error("[Hud::draw()] Cannot call until Hud has been initialized");

int y_cursor = 0;
int frame_width = al_get_bitmap_width(screen_sub_bitmap);
int frame_height = al_get_bitmap_height(screen_sub_bitmap);

ALLEGRO_STATE previous_target_bitmap_state;
al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(screen_sub_bitmap);

draw_current_focus_name();

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

if (show_powerbar)
{
   Hexagon::Powerbar::Powerbar powerbar(files_are_modified, files_are_committed, commits_are_in_sync_with_remote);
   Hexagon::Powerbar::Renderer powerbar_renderer(display, &powerbar, obtain_text_font());
   powerbar_renderer.render();
}

al_restore_state(&previous_target_bitmap_state);
return;

}
} // namespace Hexagon


