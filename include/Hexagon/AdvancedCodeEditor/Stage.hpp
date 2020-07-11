#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Stage : public StageInterface
      {
      private:
         placement3d place;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage();
         virtual ~Stage();


         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      virtual void render() override;
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



