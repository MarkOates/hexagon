

#include <Hexagon/FullScreenOverlay/Stage.hpp>
#include <stdexcept>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
namespace FullScreenOverlay
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* text_font)
   : StageInterface(StageInterface::FILE_NAVIGATOR)
   , initialized(false)
   , display(display)
   , text_font(text_font)
   , screen_sub_bitmap(nullptr)
{
}


Stage::~Stage()
{
}


void Stage::set_text_font(ALLEGRO_FONT* text_font)
{
   this->text_font = text_font;
}


void Stage::set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap)
{
   this->screen_sub_bitmap = screen_sub_bitmap;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::initialize()
{
if (initialized) return;
if (!display) throw std::runtime_error("[FullScreenOverlay::Stage::initialize()] Cannot initialize FullScreenOverlay::Stage with a nullptr screen_sub_bitmap");

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Stage::draw_design()
{
al_draw_text(text_font, al_color_name("green"), 0, 0, 0, "Hello Overlay");
return;

}

void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
return;

}

void Stage::draw()
{
if (!initialized) throw std::runtime_error("[FullScreenOverlay::Stage::draw()] Cannot call until FullScreenOverlay::Stage has been initialized");
if (!text_font) throw std::runtime_error("[FullScreenOverlay::Stage::draw()] Cannot call with a nullptr text_font");

ALLEGRO_STATE previous_target_bitmap_state;
al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(screen_sub_bitmap);

// draw your stuff here
draw_design();

al_restore_state(&previous_target_bitmap_state);
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
return;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
return;

}
} // namespace FullScreenOverlay
} // namespace Hexagon


