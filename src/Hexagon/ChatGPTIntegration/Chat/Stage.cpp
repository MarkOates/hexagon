

#include <Hexagon/ChatGPTIntegration/Chat/Stage.hpp>

#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/Elements/Window.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ChatGPTIntegration
{
namespace Chat
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::CHAT_GPT_CHAT)
   , font_bin(nullptr)
   , log_view()
   , input_box()
   , input_box_placement()
   , log_source_filename("/Users/markoates/Repos/ChatGPT/log.txt")
   , input_buffer("")
   , initialized(false)
{
}


Stage::~Stage()
{
}


void Stage::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Stage::set_log_source_filename(std::string log_source_filename)
{
   this->log_source_filename = log_source_filename;
}


void Stage::set_input_buffer(std::string input_buffer)
{
   this->input_buffer = input_buffer;
}


AllegroFlare::FontBin* Stage::get_font_bin() const
{
   return font_bin;
}


std::string Stage::get_log_source_filename() const
{
   return log_source_filename;
}


std::string Stage::get_input_buffer() const
{
   return input_buffer;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::string &Stage::get_input_buffer_ref()
{
   return input_buffer;
}


void Stage::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Stage::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::initialize: error: guard \"(!initialized)\" not met");
   }
   get_place().size = {700, 900};
   log_view.set_source_filename(log_source_filename);

   input_box_placement.position = { 0, 400 };
   input_box_placement.size = { get_place().size.x, 300 };
   //input_box.insert_lines("");
   input_box.get_text_editor_ref().insert_lines({""}); // need to insert a blank line so that we can add chars to it
   //input_box.insert_string("Hello, this is placholder text for the chat input box.");

   initialized = true;
   return;
}

void Stage::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::render: error: guard \"initialized\" not met");
   }

   ALLEGRO_FONT *log_dump_font = obtain_log_dump_font();
   float font_line_height = al_get_font_line_height(log_dump_font);
   ALLEGRO_COLOR log_dump_text_color = ALLEGRO_COLOR{0.9, 0.93, 1.0, 1.0};
   float width = 700;

   get_place().start_transform();


   // draw the log
   Hexagon::ChatGPTIntegration::Chat::LogView log_view(log_source_filename);
   std::string log_view_text = log_view.get_log_text();
   al_draw_multiline_text(log_dump_font, log_dump_text_color, 0, 0, width, font_line_height, ALLEGRO_ALIGN_LEFT,
      log_view_text.c_str()
   );

   // draw the input box
   std::string input_box_text = input_box.get_text();
   Hexagon::AdvancedCodeEditor::Cursor cursor = input_box.get_cursor();
   ALLEGRO_FONT *input_box_font = obtain_input_box_font();
   float input_box_font_line_height = al_get_font_line_height(input_box_font);

   input_box_placement.start_transform();
   Hexagon::Elements::Window window(width, 200);
   window.draw();

   al_draw_multiline_text(
      input_box_font,
      log_dump_text_color,
      0,
      0,
      width,
      input_box_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      //"This is placeholder text"
      input_box_text.c_str()
   );
   input_box_placement.restore_transform();

   // TODO:
   // renderer.render();
   get_place().restore_transform();
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   //Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   //event_controller.process_local_event(event_name, action_data);
   return;
    //body_dependency_symbols:
      //- Hexagon::AdvancedCodeEditor::EventController
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
   {
      case ALLEGRO_EVENT_KEY_DOWN:
      break;

      case ALLEGRO_EVENT_KEY_UP:
      break;

      case ALLEGRO_EVENT_KEY_CHAR: {
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         //std::cout << "CHAR EVENT: " << (char)(event.keyboard.unichar) << std::endl;
         //std::cout << "text: " << input_box.get_text() << std::endl;

         if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
         {
            input_box.move_cursor_left();
            input_box.delete_character();
            return;
         }

         if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
         {
            //input_box.move_cursor_left();
            //input_box.delete_character();
            return;
         }

         //std::vector<std::string> mapped_events =
            //keyboard_command_mapping.get_mapping(event.keyboard.keycode, shift, ctrl, alt, command);
         //for (auto &mapped_event : mapped_events) process_local_event(mapped_event);

         bool is_permitted_char_to_append = true;
         //if (stage->is_in_insert_mode())
         //{
            //if (mapped_events.empty()) // TODO: I'm not sure what the purpose of this section is
            if (is_permitted_char_to_append)
            {
               char character = (char)(event.keyboard.unichar);
               input_buffer = " ";
               input_buffer[0] = character;
               //stage->get_input_buffer_ref() = " ";
               //stage->get_input_buffer_ref()[0] = character;
               input_box.insert_string(input_buffer);
               input_box.move_cursor_right();
            }
            return;
         //}
         }
      break;
   }
   return;
}

void Stage::destroy()
{
   //if (surface_render) al_destroy_bitmap(surface_render);
   initialized = false;
   return;
}

ALLEGRO_FONT* Stage::obtain_log_dump_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stage::obtain_log_dump_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::obtain_log_dump_font: error: guard \"font_bin\" not met");
   }
   float scale = 1.45;
   int font_size = -12 * scale;
   std::stringstream ident;
   ident << "Inter-Medium.ttf " << (int)(font_size * scale);
   return font_bin->auto_get(ident.str());
}

ALLEGRO_FONT* Stage::obtain_input_box_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stage::obtain_input_box_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::obtain_input_box_font: error: guard \"font_bin\" not met");
   }
   float scale = 1.45;
   int font_size = -12 * scale;
   std::stringstream ident;
   ident << "consolas.ttf " << (int)(font_size * scale);
   return font_bin->auto_get(ident.str());
}


} // namespace Chat
} // namespace ChatGPTIntegration
} // namespace Hexagon


