#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ChatCPTIntegration/Conversation.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class ConversationView
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            Hexagon::ChatCPTIntegration::Conversation* conversation;
            int width;
            int height;
            int32_t num_messages_to_show;
            bool skip_empty_messages;
            static int multiline_text_line_number;

         protected:


         public:
            ConversationView(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, Hexagon::ChatCPTIntegration::Conversation* conversation=nullptr, int width=700, int height=900);
            ~ConversationView();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_conversation(Hexagon::ChatCPTIntegration::Conversation* conversation);
            void set_width(int width);
            void set_height(int height);
            void set_num_messages_to_show(int32_t num_messages_to_show);
            void set_skip_empty_messages(bool skip_empty_messages);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            Hexagon::ChatCPTIntegration::Conversation* get_conversation() const;
            int get_width() const;
            int get_height() const;
            int32_t get_num_messages_to_show() const;
            bool get_skip_empty_messages() const;
            static bool multiline_text_draw_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
            int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string text="[unset-text]");
            void render();
            ALLEGRO_FONT* obtain_log_dump_font();
            ALLEGRO_FONT* obtain_input_box_font();
         };
      }
   }
}



