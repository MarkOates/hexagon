#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class Stage : public StageInterface
      {
      private:
         StageInterface* stage;
         std::vector<std::tuple<std::string, std::string, std::string, std::string>> items;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage(StageInterface* stage=nullptr, std::vector<std::tuple<std::string, std::string, std::string, std::string>> items={});
         virtual ~Stage();

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         void send_message_to_stage(std::string message="[message-identifier-set]");
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



