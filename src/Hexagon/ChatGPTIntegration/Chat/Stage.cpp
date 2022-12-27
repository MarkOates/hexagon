

#include <Hexagon/ChatGPTIntegration/Chat/Stage.hpp>

#include <Blast/String/Trimmer.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>
#include <Hexagon/ChatGPTIntegration/Chat/ConversationView.hpp>
#include <Hexagon/ChatGPTIntegration/SubmitTTYMessageToChat.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <Hexagon/Elements/Window.hpp>
#include <allegro5/allegro_primitives.h>
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
   , bitmap_bin(nullptr)
   , font_bin(nullptr)
   , log_view()
   , input_box()
   , input_box_placement()
   , log_source_filename("/Users/markoates/Repos/ChatGPT/log.txt")
   , conversation()
   , input_buffer("")
   , view_mode(VIEW_MODE_UNDEFINED)
   , initialized(false)
{
}


Stage::~Stage()
{
}


void Stage::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
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


AllegroFlare::BitmapBin* Stage::get_bitmap_bin() const
{
   return bitmap_bin;
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
   get_place().size = {900, 1200};
   log_view.set_source_filename(log_source_filename);

   input_box_placement.size = { get_place().size.x, 300 };
   input_box_placement.align = { 0, 0 };
   input_box_placement.position = { get_place().size.x + 10, get_place().size.y-input_box_placement.size.y };
   //input_box.insert_lines("");
   input_box.get_text_editor_ref().insert_lines({""}); // need to insert a blank line so that we can add chars to it
   //input_box.insert_string("Hello, this is placholder text for the chat input box.");

   view_mode = VIEW_MODE_CONVERSATION;

   initialized = true;
   return;
}

void Stage::clear_input_text_box()
{
   input_box.clear();
   input_box.get_text_editor_ref().insert_lines({""}); // need to insert a blank line so that we can add chars to it
}

void Stage::toggle_view_mode()
{
   if (view_mode == VIEW_MODE_LOG) view_mode = VIEW_MODE_CONVERSATION;
   else if (view_mode == VIEW_MODE_CONVERSATION) view_mode = VIEW_MODE_LOG;
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


   // draw the messages

   if (view_mode == VIEW_MODE_LOG)
   {
      // draw the log
      Hexagon::ChatGPTIntegration::Chat::LogView log_view(log_source_filename);
      std::string log_view_text = log_view.get_log_text();
      al_draw_multiline_text(log_dump_font, log_dump_text_color, 0, 0, width, font_line_height, ALLEGRO_ALIGN_LEFT,
         log_view_text.c_str()
      );
   }
   else if (view_mode == VIEW_MODE_CONVERSATION)
   {
      // draw the conversation
      // TODO: convert from raw log to messages
      conversation.load_from_log_text_file(log_source_filename);
      Hexagon::ChatGPTIntegration::Chat::ConversationView conversation_view(
         bitmap_bin,
         font_bin,
         &conversation,
         get_place().size.x, // width
         get_place().size.y  // height
      );
      conversation_view.set_num_messages_to_show(7);
      conversation_view.set_skip_empty_messages(true);
      conversation_view.render();
   }


   // draw the input box

   std::string input_box_text = input_box.get_text();
   Hexagon::AdvancedCodeEditor::Cursor cursor = input_box.get_cursor();
   ALLEGRO_FONT *input_box_font = obtain_input_box_font();
   float input_box_font_line_height = al_get_font_line_height(input_box_font);
   float input_box_x_padding = 100;
   float input_box_width = get_place().size.x - input_box_x_padding * 2;
   float input_box_rectangle_width = get_place().size.x - (input_box_x_padding * 0.5) * 2;
   float input_box_x = input_box_x_padding * 0.5;
   float input_box_height = 200; // TODO: fix this

   input_box_placement.start_transform();
   //Hexagon::Elements::Window window(width, 200);
   //window.draw();

   // draw the fill rounded rectangle

   //float input_box_hx_padding = input_box_x_padding * 0.5;
   //float input_box_rectangle_width = 
   al_draw_filled_rounded_rectangle(
      input_box_x,
      0,
      input_box_x+input_box_width,
      input_box_height,
      5.0,
      5.0,
      ALLEGRO_COLOR{0, 0, 0, 1}
   );

   // draw the text

   al_draw_multiline_text(
      input_box_font,
      log_dump_text_color,
      input_box_x_padding,
      0,
      input_box_width,
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

void Stage::submit_input_box_and_clear()
{
   std::string input_box_text = input_box.get_text();
   std::string filtered_text = Blast::String::Trimmer(input_box_text).trim();
   if (filtered_text.empty())
   {
      std::cout << "Hexagon::ChatGPTIntegration::Chat::Stage Cannot submit input message, box is empty" << std::endl;
      return;
   }

   std::string tty_location = "/dev/ttys001"; // NOTE: this could vary
   std::string message = filtered_text;

   Hexagon::ChatGPTIntegration::SubmitTTYMessageToChat submit_tty_message_to_chat(tty_location, filtered_text);
   submit_tty_message_to_chat.submit();

   clear_input_text_box();

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

         if (event.keyboard.keycode == ALLEGRO_KEY_TAB)
         {
            toggle_view_mode();
            return;
         }

         if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && shift == true)
         {
            submit_input_box_and_clear();
            //input_box.move_cursor_left();
            //input_box.delete_character();
            return;
         }

         if (command == true)
         {
            switch (event.keyboard.keycode)
            {
               case ALLEGRO_KEY_1:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(0);
               break;

               case ALLEGRO_KEY_2:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(1);
               break;

               case ALLEGRO_KEY_3:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(2);
               break;

               case ALLEGRO_KEY_4:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(3);
               break;

               case ALLEGRO_KEY_5:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(4);
               break;

               case ALLEGRO_KEY_6:
                 copy_message_text_from_message_n_from_the_last_to_clipboard(5);
               break;
            }
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

Hexagon::ChatCPTIntegration::Messages::Base* Stage::get_nth_from_last_message(uint32_t nth_from_last_position)
{
   // TODO: move this function into 
   if (nth_from_last_position >= conversation.get_messages().size()) return nullptr;
   return conversation.get_messages()[(conversation.get_messages().size()-1) - nth_from_last_position];
}

void Stage::copy_message_text_from_message_n_from_the_last_to_clipboard(uint32_t nth_from_last_position)
{
   Hexagon::ChatCPTIntegration::Messages::Base* message = get_nth_from_last_message(nth_from_last_position);

   std::string text_to_copy;
   bool is_copyable = false;

   if (!message)
   {
      std::cout << "[Hexagon::ChatGPTIntegration::Chat::Stage]: warning: could not copy from the "
                << nth_from_last_position << "th from last message because it does not exist."
                << std::endl;
   }

   if (message->is_type(Hexagon::ChatCPTIntegration::Messages::Text::TYPE))
   {
      Hexagon::ChatCPTIntegration::Messages::Text* as_text_message = 
         static_cast<Hexagon::ChatCPTIntegration::Messages::Text*>(message);
      text_to_copy = as_text_message->get_body();
      is_copyable = true;
   }
   else
   {
      std::cout << "[Hexagon::ChatGPTIntegration::Chat::Stage]: warning: could not copy text from the "
                << nth_from_last_position << "th from last message."
                << std::endl;
   }

   if (is_copyable)
   {
      ClipboardData clipboard_data; // <-- NOTE: this ClipboardData class should be moved into some kind of namespace
      clipboard_data.store(text_to_copy);
      std::cout << "[Hexagon::ChatGPTIntegration::Chat::Stage]: info: copied text from the "
                << nth_from_last_position << "th from last message."
                << std::endl;
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


