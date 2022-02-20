#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/ObjectivesLog/ObjectivesLog.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class Stage : public StageInterface
      {
      private:
         static ALLEGRO_EVENT a_default_empty_event;
         Hexagon::ObjectivesLog::ObjectivesLog* objectives_log;
         int cursor_pos;

      public:
         Stage(Hexagon::ObjectivesLog::ObjectivesLog* objectives_log=nullptr);
         virtual ~Stage();

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         Hexagon::ObjectivesLog::ObjectivesLog* &get_objectives_log_ref();
         virtual void render() override;
         void move_cursor_up();
         void move_cursor_down();
         int infer_num_list_items();
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



