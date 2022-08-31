#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/KeyboardCommandKey.hpp>
#include <Hexagon/MultiplexMenu/MenuItem.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/System.hpp>
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
         Hexagon::System::System* system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design;
         Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
         static ALLEGRO_EVENT a_default_empty_event;
         void send_message_to_stage(std::string message="[message-identifier-set]");
         void notify_system_that_its_time_to_close_this_multiplex_menu();
         bool infer_menu_item_value_is_instruction_to_open_page(std::string menu_item_value="[unset-menu_item_value]");
         std::string extract_menu_item_value_page_name_to_open(std::string menu_item_value="[unset-menu_item_value]");
         Hexagon::MultiplexMenu::MenuItem* find_menu_item_by_keyboard_command_key_on_current_page(Hexagon::KeyboardCommandKey keyboard_command_key={});

      protected:


      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, StageInterface* stage_to_send_messages_to=nullptr, Hexagon::System::System* system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design=nullptr, Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu={});
         virtual ~Stage();

         Hexagon::MultiplexMenu::MultiplexMenu &get_multiplex_menu_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         void open_page(std::string page_name="[unset-page_name]");
      };
   }
}



