

#include <Hexagon/ChatGPTIntegration/Chat/ConversationView.hpp>

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ChatGPTIntegration
{
namespace Chat
{


int ConversationView::multiline_text_line_number = 0;


ConversationView::ConversationView(AllegroFlare::FontBin* font_bin, Hexagon::ChatCPTIntegration::Conversation* conversation, int32_t num_messages_to_show)
   : font_bin(font_bin)
   , conversation(conversation)
   , num_messages_to_show(num_messages_to_show)
   , skip_empty_messages(false)
{
}


ConversationView::~ConversationView()
{
}


void ConversationView::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ConversationView::set_conversation(Hexagon::ChatCPTIntegration::Conversation* conversation)
{
   this->conversation = conversation;
}


void ConversationView::set_num_messages_to_show(int32_t num_messages_to_show)
{
   this->num_messages_to_show = num_messages_to_show;
}


void ConversationView::set_skip_empty_messages(bool skip_empty_messages)
{
   this->skip_empty_messages = skip_empty_messages;
}


AllegroFlare::FontBin* ConversationView::get_font_bin() const
{
   return font_bin;
}


Hexagon::ChatCPTIntegration::Conversation* ConversationView::get_conversation() const
{
   return conversation;
}


int32_t ConversationView::get_num_messages_to_show() const
{
   return num_messages_to_show;
}


bool ConversationView::get_skip_empty_messages() const
{
   return skip_empty_messages;
}


bool ConversationView::multiline_text_draw_callback(int line_num, const char* line, int size, void* extra)
{
   multiline_text_line_number = line_num;
   return true;
}

int ConversationView::count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text)
{
   if (text.empty()) return 0;

   multiline_text_line_number = 0;
   al_do_multiline_text(font, max_width, text.c_str(), multiline_text_draw_callback, nullptr);

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return multiline_text_line_number + 1;
}

void ConversationView::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ConversationView::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ConversationView::render: error: guard \"font_bin\" not met");
   }
   ALLEGRO_FONT *log_dump_font = obtain_log_dump_font();
   ALLEGRO_COLOR log_dump_text_color = ALLEGRO_COLOR{0.9, 0.93, 1.0, 1.0};
   float font_line_height = al_get_font_line_height(log_dump_font);
   float width = 700;
   float cursor_y = 0;
   float message_height = 0;
   float vertical_padding = 20;

   if (!conversation)
   {
      // TODO: render a no-conversation text
   }
   std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> messages =
      conversation->get_last_n_messages(num_messages_to_show);
   for (auto &message : messages)
   {
      if (message->is_type(Hexagon::ChatCPTIntegration::Messages::Text::TYPE))
      {
         Hexagon::ChatCPTIntegration::Messages::Text* as_text_message = 
            static_cast<Hexagon::ChatCPTIntegration::Messages::Text*>(message);
         std::string message_body = as_text_message->get_body();

         // count the number of lines that will render, and calculate the message height
         int num_lines_that_will_render = count_num_lines_will_render(log_dump_font, width, message_body);
         message_height = num_lines_that_will_render * font_line_height;

         cursor_y += vertical_padding;

         // draw the text
         al_draw_multiline_text(
            log_dump_font,
            log_dump_text_color,
            0,
            cursor_y,
            width,
            font_line_height,
            ALLEGRO_ALIGN_LEFT,
            message_body.c_str()
         );

         cursor_y += message_height;
         cursor_y += vertical_padding;
      }
      else
      {
         // TODO: render an "unknown message type" text
      }
   }
   return;
}

ALLEGRO_FONT* ConversationView::obtain_log_dump_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ConversationView::obtain_log_dump_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ConversationView::obtain_log_dump_font: error: guard \"font_bin\" not met");
   }
   float scale = 1.45;
   int font_size = -12 * scale;
   std::stringstream ident;
   ident << "Inter-Medium.ttf " << (int)(font_size * scale);
   return font_bin->auto_get(ident.str());
}

ALLEGRO_FONT* ConversationView::obtain_input_box_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ConversationView::obtain_input_box_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ConversationView::obtain_input_box_font: error: guard \"font_bin\" not met");
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


