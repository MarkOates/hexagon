#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/Notifications/Notification.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Notifications
   {
      class Stage : public StageInterface
      {
      private:
         std::string body_text;
         Hexagon::Notifications::Notification component;
         static ALLEGRO_EVENT a_default_empty_event;

      protected:


      public:
         Stage(std::string body_text="");
         virtual ~Stage();

         void set_body_text(std::string body_text);
         std::string get_body_text() const;
         Hexagon::Notifications::Notification &get_component_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



