#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/ChatGPTIntegration/Chat/LogView.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class Stage : public StageInterface
         {
         private:
            AllegroFlare::FontBin* font_bin;
            Hexagon::ChatGPTIntegration::Chat::LogView log_view;
            std::string log_source_filename;
            static ALLEGRO_EVENT a_default_empty_event;
            bool initialized;

         protected:


         public:
            Stage();
            virtual ~Stage();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_log_source_filename(std::string log_source_filename);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_log_source_filename() const;
            static ALLEGRO_EVENT &get_a_default_empty_event_ref();
            void initialize();
            virtual void render() override;
            virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
            virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
            virtual void destroy() override;
            ALLEGRO_FONT* obtain_dump_font();
         };
      }
   }
}



