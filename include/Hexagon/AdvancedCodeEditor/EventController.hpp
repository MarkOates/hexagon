#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class EventController
      {
      private:
         Hexagon::AdvancedCodeEditor::Stage* stage;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         EventController();
         ~EventController();


         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



