

#include <Hexagon/ChatGPTIntegration/Chat/ConversationView.hpp>

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>
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


int ConversationView::multiline_text_line_number = 0;


ConversationView::ConversationView(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, Hexagon::ChatCPTIntegration::Conversation* conversation, int width)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , conversation(conversation)
   , width(width)
   , last_render_height(0)
   , num_messages_to_show(3)
   , skip_empty_messages(false)
{
}


ConversationView::~ConversationView()
{
}


void ConversationView::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ConversationView::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ConversationView::set_conversation(Hexagon::ChatCPTIntegration::Conversation* conversation)
{
   this->conversation = conversation;
}


void ConversationView::set_width(int width)
{
   this->width = width;
}


void ConversationView::set_last_render_height(int last_render_height)
{
   this->last_render_height = last_render_height;
}


void ConversationView::set_num_messages_to_show(int32_t num_messages_to_show)
{
   this->num_messages_to_show = num_messages_to_show;
}


void ConversationView::set_skip_empty_messages(bool skip_empty_messages)
{
   this->skip_empty_messages = skip_empty_messages;
}


AllegroFlare::BitmapBin* ConversationView::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* ConversationView::get_font_bin() const
{
   return font_bin;
}


Hexagon::ChatCPTIntegration::Conversation* ConversationView::get_conversation() const
{
   return conversation;
}


int ConversationView::get_width() const
{
   return width;
}


int ConversationView::get_last_render_height() const
{
   return last_render_height;
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

float ConversationView::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ChatGPTIntegration::Chat::ConversationView::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ChatGPTIntegration::Chat::ConversationView::render]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ChatGPTIntegration::Chat::ConversationView::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ChatGPTIntegration::Chat::ConversationView::render]: error: guard \"font_bin\" not met");
   }
   ALLEGRO_FONT *log_dump_font = obtain_log_dump_font();
   ALLEGRO_COLOR log_dump_text_color = ALLEGRO_COLOR{0.9, 0.93, 1.0, 1.0};
   float font_line_height = (al_get_font_line_height(log_dump_font) + 1);
   float frame_width = width;
   float text_padding_left = 110;
   float text_padding_right = 40;
   float text_width = frame_width - (text_padding_left + text_padding_right);
   float cursor_y = 0;
   float message_height = 0;
   float vertical_padding = 20;
   int avatar_width_and_height = 48;
   int avatar_padding_right = 30;

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
         if (skip_empty_messages && message_body.empty()) continue;

         Hexagon::ChatGPTIntegration::Author* author = conversation->find_author_by_id(message->get_author_id());
         
         ALLEGRO_COLOR background_color = (author)
                                        ? author->get_display_background_color()
                                        : ALLEGRO_COLOR{0.1, 0.1, 0.12, 0.12};
         ALLEGRO_BITMAP *avatar_bitmap = (author)
                                       ? bitmap_bin->auto_get("avatars/" + author->get_avatar_bitmap_identifier())
                                       : nullptr;

         // count the number of lines that will render, and calculate the message height
         int num_lines_that_will_render = count_num_lines_will_render(log_dump_font, text_width, message_body);
         int message_body_height = num_lines_that_will_render * font_line_height;
         int message_height = std::max(avatar_width_and_height, message_body_height);
         float full_message_card_height = vertical_padding*2 + message_height;

         // draw the backfill
         al_draw_filled_rectangle(0, cursor_y, frame_width, cursor_y+full_message_card_height, background_color);

         // draw the avatar and text (while incrementing the cursor_y variable)
         cursor_y += vertical_padding;
         if (avatar_bitmap)
         {
            // scale the avatar image to fit a fixed width/height
            al_draw_scaled_bitmap(
               avatar_bitmap,
               0,
               0,
               al_get_bitmap_width(avatar_bitmap),
               al_get_bitmap_height(avatar_bitmap),
               text_padding_left - avatar_width_and_height - avatar_padding_right,
               cursor_y,
               avatar_width_and_height,
               avatar_width_and_height,
               0
            );
         }
         al_draw_multiline_text(
            log_dump_font,
            log_dump_text_color,
            text_padding_left,
            cursor_y,
            text_width,
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

      // draw a horizontal dividing line separating the messages
      al_draw_line(0, cursor_y, frame_width, cursor_y, ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1}, 1.0);
   }

   last_render_height = cursor_y;
   return last_render_height;
}

ALLEGRO_FONT* ConversationView::obtain_log_dump_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ChatGPTIntegration::Chat::ConversationView::obtain_log_dump_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ChatGPTIntegration::Chat::ConversationView::obtain_log_dump_font]: error: guard \"font_bin\" not met");
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
      error_message << "[Hexagon::ChatGPTIntegration::Chat::ConversationView::obtain_input_box_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ChatGPTIntegration::Chat::ConversationView::obtain_input_box_font]: error: guard \"font_bin\" not met");
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


