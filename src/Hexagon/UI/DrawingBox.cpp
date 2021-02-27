

#include <Hexagon/UI/DrawingBox.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/Elements/Window.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <Blast/StringJoiner.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <allegro_flare/useful.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <TimestampGenerator.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace UI
{


ALLEGRO_EVENT DrawingBox::a_default_empty_event = {};


std::string DrawingBox::SAVE_SURFACE_TO_DESKTOP_WITH_AUTOGENERATED_NAME = "SAVE_SURFACE_TO_DESKTOP_WITH_AUTOGENERATED_NAME";


std::string DrawingBox::SET_DEFAULT_BRUSH = "SET_DEFAULT_BRUSH";


std::string DrawingBox::SET_RED_DRAFT_BRUSH = "SET_RED_DRAFT_BRUSH";


DrawingBox::DrawingBox(AllegroFlare::FontBin* font_bin, int width, int height, std::map<std::string, std::function<bool(Hexagon::UI::DrawingBox&)>> events_dictionary)
   : StageInterface(DRAWING_BOX)
   , initialized(false)
   , font_bin(font_bin)
   , width(width)
   , height(height)
   , surface(nullptr)
   , stroking(false)
   , erasing(false)
   , pointer_x(0)
   , pointer_y(0)
   , pen_opacity(1.0f)
   , pen_max_thickness(3.0f)
   , pen_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f})
   , events_dictionary(events_dictionary)
{
}


DrawingBox::~DrawingBox()
{
}


void DrawingBox::set_stroking(bool stroking)
{
   this->stroking = stroking;
}


void DrawingBox::set_erasing(bool erasing)
{
   this->erasing = erasing;
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


bool DrawingBox::get_erasing()
{
   return erasing;
}


ALLEGRO_EVENT &DrawingBox::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::map<std::string, std::function<bool(Hexagon::UI::DrawingBox&)>> &DrawingBox::get_events_dictionary_ref()
{
   return events_dictionary;
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

   //draw_crosshair();

   place.restore_transform();

   draw_title_text();
   draw_help_text();

   return;
}

void DrawingBox::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_CHAR:
     switch(event.keyboard.keycode)
     {
     case ALLEGRO_KEY_PAD_PLUS:
       process_local_event(SAVE_SURFACE_TO_DESKTOP_WITH_AUTOGENERATED_NAME);
       break;
     case ALLEGRO_KEY_PAD_7:
       process_local_event(SET_RED_DRAFT_BRUSH);
       break;
     case ALLEGRO_KEY_PAD_1:
       process_local_event(SET_DEFAULT_BRUSH);
       break;
     }
     break;
   case ALLEGRO_EVENT_MOUSE_AXES:
     {
        float mouse_position_x = event.mouse.x;
        float mouse_position_y = event.mouse.y;
        float distance_x = event.mouse.dx;
        float distance_y = event.mouse.dy;
        float mouse_pressure = event.mouse.pressure;

        if (get_stroking())
        {
           float thickness = 0.05f + mouse_pressure * pen_max_thickness;
           ALLEGRO_COLOR stroke_color = AllegroFlare::color::color(pen_color, pen_opacity);

           ALLEGRO_STATE previous_render_state;
           al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

           al_set_target_bitmap(surface);
           al_draw_line(pointer_x, pointer_y, mouse_position_x, mouse_position_y, stroke_color, thickness);

           al_restore_state(&previous_render_state);
        }
        if (get_erasing())
        {
           float thickness = 0.05f + mouse_pressure * 12.0f;

           //ALLEGRO_COLOR stroke_color = al_color_name("aliceblue");
           ALLEGRO_COLOR erase_color = ALLEGRO_COLOR{0.1f, 0.1f, 0.1f, 1.0f};

           ALLEGRO_STATE previous_render_state;
           al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

           al_set_target_bitmap(surface);
           al_draw_line(pointer_x, pointer_y, mouse_position_x, mouse_position_y, erase_color, thickness);

           al_restore_state(&previous_render_state);
        }
     }

     set_pointer_x(event.mouse.x);
     set_pointer_y(event.mouse.y);
     break;
   case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
     switch(event.mouse.button)
     {
     case 1:
        set_stroking(true);
        break;
     case 2:
        set_erasing(true);
        break;
     }
     break;
   case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
     switch(event.mouse.button)
     {
     case 1:
        set_stroking(false);
        break;
     case 2:
        set_erasing(false);
        break;
     }
     break;
   }
   return;
}

void DrawingBox::process_local_event(std::string event_name, ActionData action_data)
{
   std::map<std::string, std::function<bool(Hexagon::UI::DrawingBox&)>>::iterator it =
      events_dictionary.find(event_name);
   if (it == events_dictionary.end())
   {
      std::stringstream error_message;
      error_message << "Hexagon::UI::DrawingBox::process_local_event: error: "
                    << "No local event named \"" << event_name << "\" exists.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      std::stringstream log_message;
      log_message << "Hexagon::UI::DrawingBox::" << event_name;
      std::cout << log_message.str() << std::endl;
      events_dictionary[event_name](*this);
   }

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

ALLEGRO_FONT* DrawingBox::obtain_info_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DrawingBox" << "::" << "obtain_info_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf 14");
}

void DrawingBox::draw_help_text()
{
   ALLEGRO_FONT *title_font = obtain_info_font();

   std::vector<std::string> help_texts = {
      "PAD_PLUS: save to desktop",
      "PAD_1: default pen",
      "PAD_7: draft pencil",
   };
   Blast::StringJoiner string_joiner(help_texts, " | ");

   std::string help_text = string_joiner.join();

   float x = get_width() - 50;
   float y = get_height() - 50;
   al_draw_text(title_font, al_color_name("gray"), x, y, ALLEGRO_ALIGN_RIGHT, help_text.c_str());
}

void DrawingBox::draw_title_text()
{
   ALLEGRO_FONT *title_font = obtain_eurostile_title_font();
   std::string title_text = "DRAWING MODE";
   al_draw_text(title_font, al_color_name("white"), 100, 50, ALLEGRO_ALIGN_LEFT, title_text.c_str());
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

std::map<std::string, std::function<bool(Hexagon::UI::DrawingBox&)>> DrawingBox::build_default_function_mapping()
{
   std::map<std::string, std::function<bool(Hexagon::UI::DrawingBox&)>> default_function_mapping = {
      {
         Hexagon::UI::DrawingBox::SAVE_SURFACE_TO_DESKTOP_WITH_AUTOGENERATED_NAME,
         &Hexagon::UI::DrawingBox::save_surface_to_desktop_with_autogenerated_name,
      },
      {
         Hexagon::UI::DrawingBox::SET_DEFAULT_BRUSH,
         &Hexagon::UI::DrawingBox::set_default_brush,
      },
      {
         Hexagon::UI::DrawingBox::SET_RED_DRAFT_BRUSH,
         &Hexagon::UI::DrawingBox::set_red_draft_brush,
      },
   };
   return default_function_mapping;
}

bool DrawingBox::save_surface_to_desktop_with_autogenerated_name()
{
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "DrawingBox" << "::" << "save_surface_to_desktop_with_autogenerated_name" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_image_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DrawingBox" << "::" << "save_surface_to_desktop_with_autogenerated_name" << ": error: " << "guard \"al_is_image_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string filename = "/Users/markoates/Desktop/drawing_box_surface - ";
   filename += TimestampGenerator().get_current_time() + " - " + random_string(16) + ".png";

   std::cout << filename << std::endl;

   al_save_bitmap(filename.c_str(), surface);

   return true;
}

bool DrawingBox::set_default_brush()
{
   pen_max_thickness = 3.0f;
   pen_opacity = 1.0f;
   pen_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
   return true;
}

bool DrawingBox::set_red_draft_brush()
{
   pen_max_thickness = 1.0f;
   pen_opacity = 0.1;
   pen_color = ALLEGRO_COLOR{1.0f, 0.0f, 0.0f, 1.0f};
   return true;
}
} // namespace UI
} // namespace Hexagon

