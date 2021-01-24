

#include <Hexagon/UI/DrawingBox.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace UI
{


ALLEGRO_EVENT DrawingBox::a_default_empty_event = {};


DrawingBox::DrawingBox(AllegroFlare::FontBin* font_bin, int width, int height)
   : StageInterface(DRAWING_BOX)
   , initialized(false)
   , font_bin(font_bin)
   , width(width)
   , height(height)
   , surface(nullptr)
   , stroking(false)
   , pointer_x(0)
   , pointer_y(0)
{
}


DrawingBox::~DrawingBox()
{
}


void DrawingBox::set_stroking(bool stroking)
{
   this->stroking = stroking;
}


void DrawingBox::set_pointer_x(int pointer_x)
{
   this->pointer_x = pointer_x;
}


void DrawingBox::set_pointer_y(int pointer_y)
{
   this->pointer_y = pointer_y;
}


bool DrawingBox::get_initialized()
{
   return initialized;
}


int DrawingBox::get_width()
{
   return width;
}


int DrawingBox::get_height()
{
   return height;
}


bool DrawingBox::get_stroking()
{
   return stroking;
}


ALLEGRO_EVENT &DrawingBox::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void DrawingBox::initialize()
{
if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "DrawingBox" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DrawingBox" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
surface = al_create_bitmap(get_width(), get_height());
ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(surface);
al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
al_restore_state(&previous_render_state);
initialized = true;
return;

}

void DrawingBox::render()
{
if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "DrawingBox" << "::" << "render" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
placement3d &place = get_place();
place.start_transform();

Hexagon::Elements::Window window(get_width(), get_height());
window.set_box_fill_color(ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f});
window.set_box_opacity(0.1);
window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
window.set_outer_line_opacity(0.2);
window.set_outer_line_thickness(2.0);
window.draw();

al_draw_bitmap(surface, 0, 0, 0);

draw_crosshair();

place.restore_transform();

ALLEGRO_FONT *title_font = obtain_eurostile_title_font();
std::string title_text = "DRAWING MODE";
al_draw_text(title_font, al_color_name("white"), 100, 50, ALLEGRO_ALIGN_LEFT, title_text.c_str());

return;

}

void DrawingBox::process_event(ALLEGRO_EVENT& event)
{
switch(event.type)
{
case ALLEGRO_EVENT_KEY_CHAR:
  break;
case ALLEGRO_EVENT_MOUSE_AXES:
  if (get_stroking())
  {
     float mouse_position_x = event.mouse.x;
     float mouse_position_y = event.mouse.y;
     float distance_x = event.mouse.dx;
     float distance_y = event.mouse.dy;


     //ALLEGRO_COLOR stroke_color = al_color_name("aliceblue");
     ALLEGRO_COLOR stroke_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};

     ALLEGRO_STATE previous_render_state;
     al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

     al_set_target_bitmap(surface);
     al_draw_line(pointer_x, pointer_y, mouse_position_x, mouse_position_y, stroke_color, 2.0f);

     al_restore_state(&previous_render_state);
  }

  set_pointer_x(event.mouse.x);
  set_pointer_y(event.mouse.y);
  break;
case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
  set_stroking(true);
  break;
case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
  set_stroking(false);
  break;
}
return;

}

void DrawingBox::process_local_event(std::string event_name, ActionData action_data)
{
return;

}

ALLEGRO_FONT* DrawingBox::obtain_eurostile_title_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "DrawingBox" << "::" << "obtain_eurostile_title_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("EurostileExtendedBlack-aka-ExtendedBold.ttf 42");

}

void DrawingBox::draw_crosshair()
{
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "DrawingBox" << "::" << "draw_crosshair" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
float x = pointer_x;
float y = pointer_y;
float size = 16;
ALLEGRO_COLOR color = al_color_name("red");

float half_size = size * 0.5;
al_draw_line(x, y-half_size, x, y+half_size, color, 3.0);
al_draw_line(x-half_size, y, x+half_size, y, color, 3.0);

}

void DrawingBox::destroy()
{
if (surface) al_destroy_bitmap(surface);

}
} // namespace UI
} // namespace Hexagon


