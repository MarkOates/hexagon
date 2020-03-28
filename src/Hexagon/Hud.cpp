

#include <Hexagon/Hud.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{


AllegroFlare::FontBin Hud::dummy_font_bin = {};


Hud::Hud(ALLEGRO_DISPLAY* display, AllegroFlare::FontBin& fonts, std::string title_text)
   : initialized(false)
   , display(display)
   , fonts(fonts)
   , title_text(title_text)
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
if (!display) throw std::runtime_error("[Hud::initialize()] Cannot initialize Hud with a nullptr screen_sub_bitmap");

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::draw_current_focus_name()
{
ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
ALLEGRO_COLOR color = epic_green_color;
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
al_restore_state(&previous_target_bitmap_state);
return;

}
} // namespace Hexagon


