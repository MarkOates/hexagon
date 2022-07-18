#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         StageInterface* stage_to_send_messages_to;
         Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, StageInterface* stage_to_send_messages_to=nullptr, Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu={});
         virtual ~Stage();

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         void send_message_to_stage(std::string message="[message-identifier-set]");
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



