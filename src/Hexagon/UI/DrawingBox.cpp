

#include <Hexagon/UI/DrawingBox.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>
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
   : StageInterface(LITTLE_MENU)
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
Hexagon::Elements::Window window(width, height);
window.draw();
al_draw_bitmap(surface, 0, 0, 0);
draw_crosshair();
#include <Hexagon/Elements/Window.hpp>
place.restore_transform();
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
  }
  break;
case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
  set_stroking(true);
  set_pointer_x(event.mouse.x);
  set_pointer_y(event.mouse.y);
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
float size = 10;
ALLEGRO_COLOR color = al_color_name("red");

float half_size = size * 0.5;
al_draw_line(x, y-half_size, x, y+half_size, color, 1.0);
al_draw_line(x-half_size, y, x+half_size, y, color, 1.0);

}

void DrawingBox::destroy()
{
if (surface) al_destroy_bitmap(surface);

}
} // namespace UI
} // namespace Hexagon


