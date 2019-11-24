

#include <Hexagon/Hud.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{


Hud::Hud(ALLEGRO_DISPLAY* display)
   : display(display)
   , text_font(nullptr)
   , screen_sub_bitmap(nullptr)
   , notifications({})
{
}


Hud::~Hud()
{
}


void Hud::set_text_font(ALLEGRO_FONT* text_font)
{
   this->text_font = text_font;
}


void Hud::set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap)
{
   this->screen_sub_bitmap = screen_sub_bitmap;
}


void Hud::set_notifications(std::vector<std::string> notifications)
{
   this->notifications = notifications;
}


std::vector<std::string> Hud::get_notifications()
{
   return notifications;
}


void Hud::initialize()
{
ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);
return;

}

void Hud::draw()
{
ALLEGRO_STATE previous_target_bitmap_state;
al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(screen_sub_bitmap);
ALLEGRO_COLOR color = al_color_name("red");
float notification_bottom_padding = al_get_font_ascent(text_font);
int y_cursor=0;
for (auto &notification : notifications)
{
  float y_position = y_cursor * notification_bottom_padding;
  al_draw_text(text_font, color, 0, y_position, 0, notification.c_str());
  y_cursor++;
}
al_restore_state(&previous_target_bitmap_state);
return;

}
} // namespace Hexagon


