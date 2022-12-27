#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/ChatCPTIntegration/Conversation.hpp>
#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>
#include <Hexagon/ChatGPTIntegration/Chat/InputBox.hpp>
#include <Hexagon/ChatGPTIntegration/Chat/LogView.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class Stage : public StageInterface
         {
         public:
            static constexpr uint32_t VIEW_MODE_UNDEFINED = 0;
            static constexpr uint32_t VIEW_MODE_LOG = 1;
            static constexpr uint32_t VIEW_MODE_CONVERSATION = 2;

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            Hexagon::ChatGPTIntegration::Chat::LogView log_view;
            Hexagon::ChatGPTIntegration::Chat::InputBox input_box;
            AllegroFlare::Placement2D input_box_placement;
            std::string log_source_filename;
            Hexagon::ChatCPTIntegration::Conversation conversation;
            static ALLEGRO_EVENT a_default_empty_event;
            std::string input_buffer;
            uint32_t view_mode;
            bool initialized;

         protected:


         public:
            Stage();
            virtual ~Stage();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_log_source_filename(std::string log_source_filename);
            void set_input_buffer(std::string input_buffer);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_log_source_filename() const;
            std::string get_input_buffer() const;
            static ALLEGRO_EVENT &get_a_default_empty_event_ref();
            std::string &get_input_buffer_ref();
            void initialize();
            void clear_input_text_box();
            void toggle_view_mode();
            virtual void render() override;
            void submit_input_box_and_clear();
            virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
            virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
            Hexagon::ChatCPTIntegration::Messages::Base* get_nth_from_last_message(uint32_t nth_from_last_position=0);
            void copy_message_text_from_message_n_from_the_last_to_clipboard(uint32_t nth_from_last_position=0);
            virtual void destroy() override;
            ALLEGRO_FONT* obtain_log_dump_font();
            ALLEGRO_FONT* obtain_input_box_font();
         };
      }
   }
}



