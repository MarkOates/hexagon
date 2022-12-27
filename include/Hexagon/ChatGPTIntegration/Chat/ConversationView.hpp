#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ChatCPTIntegration/Conversation.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class ConversationView
         {
         private:
            AllegroFlare::FontBin* font_bin;
            Hexagon::ChatCPTIntegration::Conversation* conversation;
            int32_t num_messages_to_show;

         protected:


         public:
            ConversationView(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::ChatCPTIntegration::Conversation* conversation=nullptr, int32_t num_messages_to_show=0);
            ~ConversationView();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_conversation(Hexagon::ChatCPTIntegration::Conversation* conversation);
            void set_num_messages_to_show(int32_t num_messages_to_show);
            AllegroFlare::FontBin* get_font_bin() const;
            Hexagon::ChatCPTIntegration::Conversation* get_conversation() const;
            int32_t get_num_messages_to_show() const;
            void render();
            ALLEGRO_FONT* obtain_log_dump_font();
            ALLEGRO_FONT* obtain_input_box_font();
         };
      }
   }
}



